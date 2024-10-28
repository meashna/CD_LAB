#include <stdio.h>
#include <string.h>

// Global variables
char result[20][20];  // Array to store the epsilon closure states for each state
char copy[3];         // Temporary storage to hold a state for display
char states[20][3];   // Array to store the list of states from user input

// Function to add a state to the epsilon closure result
void add_state(char a[3], int *i) {
    strcpy(result[*i], a); // Copy the state to the result array
    (*i)++;                // Increment the index counter
}

// Function to display the epsilon closure of a given state
void display(int n) {
    int k = 0;
    printf("Epsilon closure of %s = { ", copy); // Display the original state for which the closure is calculated
    for (k = 0; k < n; k++) {
        printf(" %s", result[k]); // Display each state in the epsilon closure
    }
    printf(" }\n");
}

int main() {
    FILE *INPUT; // File pointer to read from the input file
    INPUT = fopen("input.dat", "r"); // Open the input file containing transitions
    if (INPUT == NULL) { // Check if the file opened successfully
        perror("Error opening file");
        return 1; // Return with an error code if file opening fails
    }

    char state[3]; // Temporary storage for the current state being processed
    int i, n, k;   // Variables for counting and indexing

    // Ask the user for the number of states in the automaton
    printf("Enter the number of states: ");
    scanf("%d", &n); // Read the number of states

    // Read each state from user input and store it in the states array
    printf("Enter the states:\n");
    for (k = 0; k < n; k++) {
        scanf("%s", states[k]);
    }

    // Loop through each state to calculate its epsilon closure
    for (k = 0; k < n; k++) {
        i = 0; // Reset the counter for the epsilon closure result
        strcpy(state, states[k]); // Copy the current state to the state variable
        strcpy(copy, state); // Copy the state for display purposes
        add_state(state, &i); // Add the state itself to its epsilon closure

        // Read transitions from the file and build the epsilon closure
        while (1) {
            char state1[3], input[3], state2[3]; // Temporary variables to hold transition data
            int end = fscanf(INPUT, "%s %s %s", state1, input, state2); // Read a transition from the file

            if (end == EOF) { // If the end of the file is reached, break out of the loop
                break;
            }

            // Check if the transition is an epsilon transition for the current state
            if (strcmp(state, state1) == 0 && strcmp(input, "e") == 0) {
                add_state(state2, &i); // Add the destination state to the epsilon closure
                strcpy(state, state2); // Update the current state to the new state for further exploration
            }
        }

        display(i); // Display the epsilon closure of the current state
        rewind(INPUT); // Reset the file pointer to the beginning for the next state
    }

    fclose(INPUT); // Close the input file
    return 0; // Exit the program
}

