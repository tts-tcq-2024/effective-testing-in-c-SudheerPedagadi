#include <stdio.h>
#include <assert.h>

int alertFailureCount = 0;

int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    if (celcius > 250) {
        return 500;
    }
    // Return 200 for ok
    // Return 500 for not-ok
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
    
    // Test cases
    alertInCelcius(200); 
    printf("AlertFailureCount = %d\n", alertFailureCount);
    assert(alertFailureCount == 0);  // Temperature in Celsius is not above 250, so no failure

    alertInCelcius(300); 
    printf("AlertFailureCount = %d\n", alertFailureCount);
    assert(alertFailureCount == 1);  // Temperature in Celsius is above 250, so failure count increments

    alertInCelcius(150);   
    printf("AlertFailureCount = %d\n", alertFailureCount);
    assert(alertFailureCount == 1);  // Temperature in Celsius is not above 250, no change in failure count

    printf("All tests passed successfully!\n");
}

int main() {    
    testAlertFailureCount();

    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
