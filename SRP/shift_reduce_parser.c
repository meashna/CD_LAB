#include <stdio.h>
#include <string.h>

// Global variables
int k = 0, z = 0, i = 0, j = 0, c = 0; // Various counters and indices
char a[16], ac[20], stk[15], act[10];  // Arrays to hold input, action messages, stack contents, and current action

// Function prototypes
void check(); // Function to check and apply reductions based on the grammar rules

// Main function
void main() {
    puts("GRAMMAR is E->E+E \n E->E*E \n E->(E) \n E->id");
    puts("Enter input string: ");
    gets(a); // Read the input string (e.g., "id+id*id")
    c = strlen(a); // Find the length of the input string
    strcpy(act, "SHIFT->"); // Initialize the action message with "SHIFT->"
    puts("stack \t input \t action"); // Print table header

    // Loop through the input string
    for (k = 0, i = 0, j = 0; j < c; k++, i++, j++) {
        // If the next two characters are "id", treat them as a single unit
        if (a[j] == 'i' && a[j + 1] == 'd') {
            stk[i] = a[j];       // Push 'i' onto the stack
            stk[i + 1] = a[j + 1]; // Push 'd' onto the stack
            stk[i + 2] = '\0';   // Null-terminate the stack
            a[j] = ' ';          // Remove 'i' from the input
            a[j + 1] = ' ';      // Remove 'd' from the input
            printf("\n$%s\t%s$\t%sid", stk, a, act); // Display the current stack, remaining input, and action
            check();             // Call the check function to try reducing the stack
        } else { // If it's any other character (operators or parentheses)
            stk[i] = a[j];       // Push the character onto the stack
            stk[i + 1] = '\0';   // Null-terminate the stack
            a[j] = ' ';          // Remove the character from the input
            printf("\n$%s\t%s$\t%ssymbols", stk, a, act); // Display current stack, remaining input, and action
            check();             // Call the check function to try reducing the stack
        }
    }

    // Check if the parsing was successful based on stack state
    if (j == c && i == 1 && stk[i] == '\0') {
        printf("\nAccept\n"); // The input string is valid according to the grammar
    } else {
        printf("\nReject\n"); // The input string is not valid according to the grammar
    }
}

// Function to check and reduce the stack based on the grammar rules
void check() {
    strcpy(ac, "REDUCE TO E"); // Action message when a reduction occurs

    // Loop through the stack to check for reducible patterns
    for (z = 0; z < c; z++) {
        // Rule: E -> id
        if (stk[z] == 'i' && stk[z + 1] == 'd') {
            stk[z] = 'E'; // Replace "id" with "E" in the stack
            stk[z + 1] = '\0'; // Null-terminate the stack
            printf("\n$%s\t%s$\t%s", stk, a, ac); // Display the stack, input, and action message
            j++; // Increment j to skip over the "d" part of "id"
        }
    }

    // Rule: E -> E + E
    for (z = 0; z < c; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '+' && stk[z + 2] == 'E') {
            stk[z] = 'E';   // Reduce "E + E" to "E"
            stk[z + 1] = '\0'; // Null-terminate the stack after the first "E"
            stk[z + 2] = '\0'; // Remove the second "E"
            printf("\n$%s\t%s$\t%s", stk, a, ac); // Display the stack, input, and action message
            i = i - 2; // Adjust 'i' to reflect the reduced stack size
        }
    }

    // Rule: E -> E * E
    for (z = 0; z < c; z++) {
        if (stk[z] == 'E' && stk[z + 1] == '*' && stk[z + 2] == 'E') {
            stk[z] = 'E';   // Reduce "E * E" to "E"
            stk[z + 1] = '\0'; // Null-terminate the stack after the first "E"
            stk[z + 2] = '\0'; // Remove the second "E"
            printf("\n$%s\t%s$\t%s", stk, a, ac); // Display the stack, input, and action message
            i = i - 2; // Adjust 'i' to reflect the reduced stack size
        }
    }

    // Rule: E -> (E)
    for (z = 0; z < c; z++) {
        if (stk[z] == '(' && stk[z + 1] == 'E' && stk[z + 2] == ')') {
            stk[z] = 'E';   // Reduce "(E)" to "E"
            stk[z + 1] = '\0'; // Null-terminate the stack after the first "E"
            stk[z + 2] = '\0'; // Remove the closing parenthesis
            printf("\n$%s\t%s$\t%s", stk, a, ac); // Display the stack, input, and action message
            i = i - 2; // Adjust 'i' to reflect the reduced stack size
        }
    }
}

