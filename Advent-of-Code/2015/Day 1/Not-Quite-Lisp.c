#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    // Initialize variables
    FILE *fptr = fopen("input.txt", "r"); // Open input file
    int input_size = 10000; // Max number of characters for input
    char *input = malloc(sizeof(char) * input_size); // Allocate memory for the input
    fgets(input, input_size, fptr); // Read puzzle input into string

    int floor = 0; // Santa's current floor
    int basement_position = 0;

    for (int i = 0; i < input_size; i++) // Iterate over the input
    {
        if (input[i] == '(') // Santa goes up a floor if he encounters (
        {
            floor += 1;
        }
        if (input[i] == ')') // He goes down a floor if he encounters )
        {
            floor -= 1;
        }
        if (basement_position == 0) // Only check if the basement has not already been found
        {
            if (floor == -1) // If Santa has reached the basement, record the character position
            {
                basement_position = i + 1;
            }
        }
    }

    printf("Final floor: %d\n", floor); // Print results
    printf("Basement location: %d\n", basement_position);
    
    free(input); 
    return 0;
}