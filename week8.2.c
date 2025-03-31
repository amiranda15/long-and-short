#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <source_file> <destination_file_1> <destination_file_2>\n", argv[0]);
        return 1;
    }

    FILE *sourceFile, *shortFile, *longFile;
    char line[1024];
    int shortLineCount = 0, longLineCount = 0;

    sourceFile = fopen(argv[1], "r");
    if (sourceFile == NULL) {
        perror("Error opening source file");
        return 1;
    }

    shortFile = fopen(argv[2], "w");
    if (shortFile == NULL) {
        perror("Error opening short file");
        fclose(sourceFile);
        return 1;
    }

    longFile = fopen(argv[3], "w");
    if (longFile == NULL) {
        perror("Error opening long file");
        fclose(sourceFile);
        fclose(shortFile);
        return 1;
    }

    while (fgets(line, sizeof(line), sourceFile) != NULL) {
        int len = strlen(line);
        if (line[len - 1] == '\n') {
            line[len - 1] = '\0'; 
            len--;
        }

        if (len < 20) {
            for (int i = 0; i < len; i++) {
                line[i] = toupper((unsigned char)line[i]);
            }
            fprintf(shortFile, "%s\n", line);
            shortLineCount++;
        } else {
            for (int i = 0; i < len; i++) {
                line[i] = tolower((unsigned char)line[i]);
            }
            fprintf(longFile, "%s\n", line);
            longLineCount++;
        }
    }

    fclose(sourceFile);
    fclose(shortFile);
    fclose(longFile);

    printf("%d lines written to %s\n", shortLineCount, argv[2]);
    printf("%d lines written to %s\n", longLineCount, argv[3]);

    return 0;
}