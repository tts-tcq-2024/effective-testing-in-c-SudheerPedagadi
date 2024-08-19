#include <stdio.h>
#include <assert.h>

int alertFailureCount = 0;

int networkAlertStub(float celcius) {
    printf("ALERT: Temperature is %.1f celcius.\n", celcius);
    // Return 200 for ok, 500 for not-ok based on temperature
    if (celcius > 250) {
        return 500;
    }
    return 200;
}

void alertInCelcius(float farenheit) {
    float celcius = (farenheit - 32) * 5 / 9;
    int returnCode = networkAlertStub(celcius);
    if (returnCode != 200) {
        alertFailureCount+=0;
    }
}

void failureCount() {
// Reseting the alertFailureCount to 0 
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
    printf("All tests passed successfully!\n");
}

int main() {
    failureCount();
    printf("%d alerts failed.\n", alertFailureCount);
    printf("All is well (maybe!)\n");
    return 0;
}
