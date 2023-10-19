#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char buffer[]) {
    char keywords[32][10] = {"main", "auto", "break", "case", "char", "const", "continue", "default",
                             "do", "double", "else", "enum", "extern", "float", "for", "goto",
                             "if", "int", "long", "register", "return", "short", "signed",
                             "sizeof", "static", "struct", "switch", "typedef",
                             "unsigned", "void", "printf", "while"};
    int i, flag = 0;
    for (i = 0; i < 32; ++i) {
        if (strcmp(keywords[i], buffer) == 0) {
            flag = 1;
            break;
        }
    }
    return flag;
}

void skipWhiteSpaceAndComments(FILE *fp) {
    char ch, prev = ' ';
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == ' ' || ch == '\t' || ch == '\n') {
            if (prev != '/')
                continue; // Skip redundant spaces, tabs, and newlines
            else {
                // Handle comments
                while ((ch = fgetc(fp)) != '\n') {
                    if (ch == EOF)
                        return; // End of file
                }
            }
        } else {
            ungetc(ch, fp); // Put back the non-space, non-tab, non-newline character
            return;
        }
        prev = ch;
    }
}

int main() {
    char ch, buffer[15], operators[] = "+-*/%=";
    FILE *fp;
    int i, j = 0;
    fp = fopen("flex_input.txt", "r");
    if (fp == NULL) {
        printf("Error while opening the file\n");
        exit(0);
    }
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '/' && (ch = fgetc(fp)) == '*') {
            // Skip multi-line comments
            while (1) {
                char prev = ch;
                ch = fgetc(fp);
                if (ch == EOF) {
                    printf("Error: Unclosed comment\n");
                    break;
                }
                if (prev == '*' && ch == '/') {
                    break;
                }
            }
        } else {
            ungetc(ch, fp);
            skipWhiteSpaceAndComments(fp);

            for (i = 0; i < 6; ++i) {
                if (ch == operators[i])
                    printf("%c is an operator\n", ch);
            }

            if (isalnum(ch)) {
                buffer[j++] = ch;
            } else if ((ch == ' ' || ch == '\n') && (j != 0)) {
                buffer[j] = '\0';
                j = 0;

                if (isKeyword(buffer) == 1)
                    printf("%s is a keyword\n", buffer);
                else
                    printf("%s is an identifier\n", buffer);
            }
        }
    }
    fclose(fp);
    return 0;
}

