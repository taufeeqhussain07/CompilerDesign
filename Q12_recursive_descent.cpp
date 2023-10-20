#include <stdio.h>
#include <conio.h>
#include <string.h>

char input[100];
int i = 0; // Initialize 'i' to 0
int l;

int E();  // Function prototypes
int EP();
int T();
int TP();
int F();

int main() {
    // clrscr(); // This function is not standard, so it's commented out
    printf("\nRecursive descent parsing for the following grammar\n");
    printf("\nE->TE'\nE'->+TE'/@\nT->FT'\nT'->*FT'/@\nF->(E)/ID\n");
    printf("\nEnter the string to be checked:");
    gets(input);

    if (E() && input[i] == '\0') {
        printf("\nString is accepted");
    } else {
        printf("\nString is not accepted");
    }
    
    getch();
    return 0;
}

int E() {
    if (T()) {
        if (EP()) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

int EP() {
    if (input[i] == '+') {
        i++;
        if (T()) {
            if (EP()) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    } else {
        return 1;  // Updated to return 1 for the empty string case
    }
}

int T() {
    if (F()) {
        if (TP()) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}

int TP() {
    if (input[i] == '*') {
        i++;
        if (F()) {
            if (TP()) {
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    } else {
        return 1;  // Updated to return 1 for the empty string case
    }
}

int F() {
    if (input[i] == '(') {
        i++;
        if (E()) {
            if (input[i] == ')') {
                i++;
                return 1;
            } else {
                return 0;
            }
        } else {
            return 0;
        }
    } else if ((input[i] >= 'a' && input[i] <= 'z') || (input[i] >= 'A' && input[i] <= 'Z')) {
        i++;
        return 1;
    } else {
        return 0;
    }
}


