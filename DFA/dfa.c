#include<stdio.h>

void main(){
    // Arrays to store states, input symbols, and input string
    int state[10]; // Holds all states of the DFA
    int input[10]; // Holds all input symbols (e.g., 0, 1)
    int str[10];   // Holds the input string to be tested against the DFA
    int x[20];     // Stores the transition table values (state transitions)

    // Variables for state count, input symbol count, and loop control
    int s, n, k = 0, j, a, i, l, t, q = 0, fs, b, nxt, z;

    // Get the number of states in the DFA
    printf("Enter the number of states:\n");
    scanf("%d", &s);

    // Get the number of input symbols (e.g., 2 for binary input: 0 and 1)
    printf("Enter the number of input symbols:\n");
    scanf("%d", &n);

    // Loop through each state to get details about the state and whether it's a final state
    for(i = 0; i < s; i++){
        // Prompt the user to enter state number
        printf("Enter state %d:\n", i);
        scanf("%d", &state[i]);
        
        // Ask if this state is a final state (accepting state)
        printf("Is it a final state? (1 for yes, 0 for no):\n");
        scanf("%d", &a);
        if(a == 1){
            fs = state[i]; // Store this state as the final state if user indicates so
        }
    }

    // Input the symbols allowed by the DFA (e.g., binary inputs: 0 and 1)
    printf("Enter the input symbols:\n");
    for(i = 0; i < n; i++){
        scanf("%d", &input[i]); // Read each symbol and store it in the 'input' array
    }

    // Get the transition function details for each state and input symbol
    printf("Enter the transition function:\n");
    for(i = 0; i < s; i++){
        for(j = 0; j < n; j++){
            // Prompt to enter the state transition for each (state, symbol) pair
            printf("(q%d, %d) = q", state[i], input[j]);
            scanf("%d", &b);
            x[k] = b; // Store the next state based on the transition function
            k++; // Increment index to store the next value in transition table
        }
    }

    // Loop to process and check multiple input strings as per user's choice
    do{
        // Get the length of the input string to be tested
        printf("Enter the length of the string:\n");
        scanf("%d", &l);

        // Get the input string from the user (array of symbols)
        printf("Enter the input string:\n");
        for(i = 0; i < l; i++){
            scanf("%d", &str[i]); // Store each character of the input string in 'str'
        }

        q = 0; // Reset the current state to the start state (assumed as state 0)

        // Iterate through each symbol of the input string to simulate DFA transitions
        for(i = 0; i < l; i++){
            t = 0; // Reset the input symbol index for each character in the string

            // Find the input symbol in the input array to determine its index
            while(t < n){
                if(str[i] == input[t]){
                    // Calculate the next state using the transition table
                    // 'q' is the current state, 't' is the index of the current symbol
                    nxt = x[n * q + t];

                    // Find which state corresponds to this 'next' state value
                    for(j = 0; j < s; j++){
                        if(nxt == state[j]){
                            q = j; // Update current state to the matched state index
                            break; // Exit loop as state has been found
                        }
                    }
                    break; // Exit the loop as input symbol match is found
                }
                t++; // Move to the next symbol in the input array
            }
        }

        // Check if the final state after processing the string matches the DFA's final state
        if(state[q] == fs){
            printf("String is accepted\n"); // If so, the string is accepted by the DFA
        }
        else{
            printf("String is not accepted\n"); // Otherwise, the string is rejected
        }

        // Ask user if they want to test another string (continue or not)
        printf("Do you want to continue? (1 for yes, 2 for no):\n");
        scanf("%d", &z);
    } while(z == 1); // Loop continues if user chooses '1' for yes
}

