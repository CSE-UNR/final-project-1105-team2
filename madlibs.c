// Jaydon Wilson, Sebastian Diaz, Raul Delgado
// Final Group Project
// 12/02

#include <stdio.h>

#define FILE_NAME "madlib2.txt"
#define MAX_LINES 100
#define MAX_LINE_LENGTH 100
#define MAX_INPUTS 50

int loadMadlib(const char *fileName, char madlib[MAX_LINES][MAX_LINE_LENGTH], int *lineCount);
void getUserInputs(const char madlib[MAX_LINES][MAX_LINE_LENGTH], int *lineCount, char inputs[MAX_INPUTS][MAX_LINE_LENGTH]);
void replacePlaceholders(char madlib[MAX_LINES][MAX_LINE_LENGTH], int *lineCount, const char inputs[MAX_INPUTS][MAX_LINE_LENGTH]);
void printMadlib(const char madlib[MAX_LINES][MAX_LINE_LENGTH], int *lineCount);
void myStrcpy(char *dest, const char *src);

int main() {
    char madlib[MAX_LINES][MAX_LINE_LENGTH];
    char inputs[MAX_INPUTS][MAX_LINE_LENGTH];
    int lineCountValue;
    int *lineCount = &lineCountValue;

    *lineCount = loadMadlib(FILE_NAME, madlib, lineCount);

    if (*lineCount == -1) {
        printf("Error reading the file.\n");
        return 0;
    }

    getUserInputs(madlib, lineCount, inputs);

    replacePlaceholders(madlib, lineCount, inputs);

    printMadlib(madlib, lineCount);

    return 0;
}

// Loads madlib from file
int loadMadlib(const char *fileName, char madlib[MAX_LINES][MAX_LINE_LENGTH], int *lineCount) {
    FILE *file = fopen(fileName, "r");
    if (!file) return -1;

    *lineCount = 0;
    while (fgets(madlib[*lineCount], MAX_LINE_LENGTH, file) && *lineCount < MAX_LINES) {
        for (int i = 0; madlib[*lineCount][i] != '\0'; i++) {
            if (madlib[*lineCount][i] == '\n') {
                madlib[*lineCount][i] = '\0';
                break;
            }
        }
        (*lineCount)++;
    }

    fclose(file);
    return *lineCount;
}

// Get user inputs
void getUserInputs(const char madlib[MAX_LINES][MAX_LINE_LENGTH], int *lineCount, char inputs[MAX_INPUTS][MAX_LINE_LENGTH]) {
    int inputIndex = 0;

    for (int i = 0; i < *lineCount; i++) {
        if (madlib[i][0] == 'A') {
            printf("Enter an adjective: ");
        } else if (madlib[i][0] == 'N') {
            printf("Enter a noun: ");
        } else if (madlib[i][0] == 'V') {
            printf("Enter a verb: ");
        } else {
            continue;
        }

        fgets(inputs[inputIndex], MAX_LINE_LENGTH, stdin);

        for (int j = 0; inputs[inputIndex][j] != '\0'; j++) {
            if (inputs[inputIndex][j] == '\n') {
                inputs[inputIndex][j] = '\0';
                break;
            }
        }
        inputIndex++;
    }
}

// Replace placeholders with user inputs
void replacePlaceholders(char madlib[MAX_LINES][MAX_LINE_LENGTH], int *lineCount, const char inputs[MAX_INPUTS][MAX_LINE_LENGTH]) {
    int inputIndex = 0;

    for (int i = 0; i < *lineCount; i++) {
        if (madlib[i][0] == 'A' || madlib[i][0] == 'N' || madlib[i][0] == 'V') {
            myStrcpy(madlib[i], inputs[inputIndex]);
            inputIndex++;
        }
    }
}

// Print completed madlib
void printMadlib(const char madlib[MAX_LINES][MAX_LINE_LENGTH], int *lineCount) {
    for (int i = 0; i < *lineCount; i++) {
        printf("%s", madlib[i]);
        if (i < *lineCount - 1) {
            printf(" "); // Add space
        }
    }
    printf("\n");
}

// String copy function
void myStrcpy(char *dest, const char *src) {
    while (*src) {
        *dest++ = *src++;
    }
    *dest = '\0';
}

