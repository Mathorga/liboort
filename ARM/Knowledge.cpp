#include "Knowledge.h"

void Knowledge::readFile(char *fileName) {
    FILE *knowledgeFile;
    char ch;

    knowledgeFile = fopen(fileName, "r");
    if (knowledgeFile != NULL) {
        // Read file content.
        while ((ch = fgetc(knowledgeFile)) != EOF) {
            if (ch == '\n') {
                printf("\n<newline>\n");
            }
            printf("%c", ch);
        }
        fclose(knowledgeFile);
    }
}
