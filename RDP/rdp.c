#include<stdio.h>
#include<string.h>
#include<ctype.h>

// Global variables
char input[10];  // Array to store the input expression
int i = 0, error = 0;  // i: index to track position in the input string, error: flag to detect syntax errors

// Function prototypes for the recursive parser
void E();       // Function for non-terminal E
void T();       // Function for non-terminal T
void Eprime();  // Function for non-terminal E'
void Tprime();  // Function for non-terminal T'
void F();       // Function for non-terminal F

void main() {
    printf("Enter an arithmetic expression:\n");
    gets(input); // Read the input expression (use fgets for safer input handling)

    E(); // Start parsing from the non-terminal E

    // If the input is fully consumed and no errors are detected, the expression is accepted
    if (strlen(input) == i && error == 0)
        printf("\nAccepted..!!!");
    else
        printf("\nRejected..!!!");
}

// Function for the non-terminal E
// E -> T E'
void E() {
    T();     // Parse T
    Eprime(); // Parse E'
}

// Function for the non-terminal E'
// E' -> + T E' | ε (epsilon, meaning "nothing")
void Eprime() {
    // If the current symbol is '+', consume it and recursively parse T and E'
    if (input[i] == '+') {
        i++;      // Move to the next character
        T();      // Parse T
        Eprime(); // Parse E' recursively
    }
    // If there's no '+', E' transitions to ε (nothing), so do nothing
}

// Function for the non-terminal T
// T -> F T'
void T() {
    F();       // Parse F
    Tprime();  // Parse T'
}

// Function for the non-terminal T'
// T' -> * F T' | ε
void Tprime() {
    // If the current symbol is '*', consume it and recursively parse F and T'
    if (input[i] == '*') {
        i++;       // Move to the next character
        F();       // Parse F
        Tprime();  // Parse T' recursively
    }
    // If there's no '*', T' transitions to ε, so do nothing
}

// Function for the non-terminal F
// F -> (E) | id
void F() {
    // Case 1: If the current symbol is '(', parse it as an expression inside parentheses
    if (input[i] == '(') {
        i++;       // Consume '('
        E();       // Parse the expression inside the parentheses
        if (input[i] == ')') {
            i++;   // Consume ')'
        } else {
            error = 1; // If ')' is not found, set an error
        }
    }
    // Case 2: If the current symbol is an alphabetic character, treat it as an identifier (id)
    else if (isalpha(input[i])) {
        i++; // Consume the alphabetic character
        // Consume the rest of the identifier if it contains alphanumeric characters or underscores
        while (isalnum(input[i]) || input[i] == '_') {
            i++;
        }
    }
    // Case 3: If none of the above, it's an error
    else {
        error = 1; // Set an error flag if the input doesn't match the expected pattern
    }
}

