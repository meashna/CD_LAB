#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

// Global variables
int n, m = 0, p, i = 0, j = 0;
char a[10][10], f[10]; // a stores the productions; f is used to temporarily store FIRST and FOLLOW sets

// Function prototypes
void first(char c);  // Function to calculate the FIRST set of a non-terminal
void follow(char c); // Function to calculate the FOLLOW set of a non-terminal

int main() {
    int i, z; // i: loop index, z: flag to determine whether the user wants to continue
    char c, ch; // c: character for which FIRST and FOLLOW are calculated; ch: used for input handling
    
    printf("Enter the number of productions:\n");
    scanf("%d", &n); // Read the number of productions from user input
    
    printf("Enter the productions:\n");
    // Read the grammar productions from the user
    for (i = 0; i < n; i++)
        scanf("%s%c", a[i], &ch); // Read each production into 'a'; ch captures newline characters
    
    do {
        m = 0; // Reset 'm' before each calculation to store the new FIRST or FOLLOW set
        printf("Enter the element whose FIRST & FOLLOW is to be found: ");
        scanf(" %c", &c); // Read the non-terminal for which the FIRST and FOLLOW sets are to be found
        
        first(c); // Calculate the FIRST set for the non-terminal
        
        // Print the calculated FIRST set
        printf("First(%c) = {", c);
        for (i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");
        
        strcpy(f, " "); // Reset 'f' to prepare it for storing the FOLLOW set
        m = 0; // Reset 'm' again for the FOLLOW calculation
        
        follow(c); // Calculate the FOLLOW set for the non-terminal
        
        // Print the calculated FOLLOW set
        printf("Follow(%c) = {", c);
        for (i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");
        
        printf("Continue (0/1)? "); // Ask if the user wants to continue or exit
        scanf("%d%c", &z, &ch); // Read user's choice (0 to exit, 1 to continue); ch absorbs newline
    } while (z == 1); // Loop until user chooses to exit
    
    return 0; // End the program
}

// Function to compute the FIRST set of a given non-terminal 'c'
void first(char c) {
    int k; // Loop index
    
    // If 'c' is a terminal (not uppercase), add it directly to the FIRST set
    if (!isupper(c)) { // 'isupper' checks if 'c' is an uppercase letter (non-terminal)
        f[m++] = c;    // Add the terminal to the FIRST set and increment 'm'
        return;        // Return as terminals do not require further processing
    }
    
    // Iterate through each production in 'a'
    for (k = 0; k < n; k++) {
        // Check if the production's left-hand side matches 'c'
        if (a[k][0] == c) {
            // Case 1: Production is in the form A -> epsilon (represented as '$')
            if (a[k][2] == '$') {
                follow(a[k][0]); // Add FOLLOW(A) to FIRST(A) since epsilon is in the FIRST set
            }
            // Case 2: Production right-hand side starts with a terminal (lowercase character)
            else if (islower(a[k][2])) {
                f[m++] = a[k][2]; // Add this terminal directly to the FIRST set
            }
            // Case 3: Production right-hand side starts with a non-terminal (uppercase character)
            else {
                first(a[k][2]); // Recursively find the FIRST set of this non-terminal
            }
        }
    }
}

// Function to compute the FOLLOW set of a given non-terminal 'c'
void follow(char c) {
    // If 'c' is the start symbol (the left-hand side of the first production), add '$' to FOLLOW set
    if (a[0][0] == c)
        f[m++] = '$';
    
    // Iterate through each production in 'a' to find occurrences of 'c'
    for (i = 0; i < n; i++) {
        for (j = 2; j < strlen(a[i]); j++) { // Start from index 2 (after '->') to scan the right-hand side
            if (a[i][j] == c) { // Check if 'c' is found in the production's right-hand side
                // Case 1: If there's a symbol after 'c' in the production
                if (a[i][j + 1] != '\0') {
                    first(a[i][j + 1]); // Compute FIRST of the next symbol and add to FOLLOW(c)
                }
                // Case 2: If 'c' is at the end of the production (no symbol after it)
                // and it's not the same as the left-hand side non-terminal
                if (a[i][j + 1] == '\0' && c != a[i][0]) {
                    follow(a[i][0]); // Add FOLLOW of the left-hand side to FOLLOW(c)
                }
            }
        }
    }
}

