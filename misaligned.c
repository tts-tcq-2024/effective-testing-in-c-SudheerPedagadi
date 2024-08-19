#include <stdio.h>
#include <assert.h>
#include <string.h>

int printColorMap() {
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    int i = 0, j = 0;
    for(i = 0; i < 5; i++) {
        for(j = 0; j < 5; j++) {
            printf("%d | %s | %s\n", i * 5 + j, majorColor[i], minorColor[i]);
        }
    }
    return i * j;
}

void testColorPairs() {
    // Buffer to capture the output of printColorMap
    char buffer[1024];
    buffer[0] = '\0'; // Initialize the buffer with an empty string
    
    // Redirect stdout to the buffer
    FILE* output = fmemopen(buffer, sizeof(buffer), "w");
    assert(output != NULL); // Ensure the stream is opened successfully
    
    // Save the original stdout and redirect stdout to the memory stream
    FILE* original_stdout = stdout;
    stdout = output;
    
    // Generate the color map output
    printColorMap();
    
    // Restore stdout and close the memory stream
    stdout = original_stdout;
    fclose(output);
    
    // Define expected major and minor colors
    const char* majorColor[] = {"White", "Red", "Black", "Yellow", "Violet"};
    const char* minorColor[] = {"Blue", "Orange", "Green", "Brown", "Slate"};
    
    // Split the captured output into lines and verify each one
    char* line = strtok(buffer, "\n");
    int lineCount = 0;

    while (line != NULL) {
        char expectedOutput[100];
        snprintf(expectedOutput, sizeof(expectedOutput), "%d | %s | %s",
                 lineCount, majorColor[lineCount / 5], minorColor[lineCount % 5]);

        // Compare the captured line with the expected output
        if (strcmp(line, expectedOutput) != 0) {
            printf("Test failed at index: %d\nActual: %s\nExpected: %s\n",
                   lineCount, line, expectedOutput);
            assert(0 && "Mismatch in color pair output");
        }

        lineCount++;
        line = strtok(NULL, "\n");
    }
}
int main() {
    int result = printColorMap();
    testColorPairs();
    assert(result == 25);
    printf("All is well (maybe!)\n");
    return 0;
}
