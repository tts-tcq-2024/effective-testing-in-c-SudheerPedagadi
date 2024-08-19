#include <stdio.h>
#include <assert.h>

int alertFailureCount = 0;

int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    if (celcius > 250) {
        return 500;
    }
    return 200;
}
void alertInCelcius(float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlertStub(celcius);
    if (returnCode != 200) {
        // non-ok response is not an error! Issues happen in life!
        // let us keep a count of failures to report
        // However, this code doesn't count failures!
        // Add a test below to catch this bug. Alter the stub above, if needed.
        alertFailureCount += 0;
    }
}
void testAlertFailureCount() {
    // Reset alertFailureCount to 0 before running tests
    alertFailureCount = 0;
    alertInCelcius(200); 
    printf("AlertFailureCount = %d\n", alertFailureCount);
    assert(alertFailureCount == 0);  
    alertInCelcius(300); 
    printf("AlertFailureCount = %d\n", alertFailureCount);
    assert(alertFailureCount == 1);  
    alertInCelcius(150);   
    printf("AlertFailureCount = %d\n", alertFailureCount);
    assert(alertFailureCount == 1);  
    printf("All tests are passed successfully!\n");
}

int main() {    
    testAlertFailureCount();
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
