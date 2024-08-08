#include <stdio.h>
#include <assert.h>

char size(int cms) {
    char sizeName = '\0';
    if(cms < 38) {
        sizeName = 'S';
    } else if(cms >= 38 && cms <= 42) { // Corrected the boundary condition
        sizeName = 'M';
    } else if(cms > 42) {
        sizeName = 'L';
    }
    return sizeName;
}

int main() {
    assert(size(37) == 'S');
    assert(size(40) == 'M');
    assert(size(43) == 'L');
    // Introduce a failing test case
    assert(size(10) == 'M'); // This should fail as 10 is 'S'
    assert(size(38) == 'L'); // This should fail as 38 is 'M'
    assert(size(45) == 'S'); // This should fail as 38 is 'L'
    printf("All is well (maybe!)\n");
    return 0;
}
