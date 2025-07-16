#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000000;

int count_digits(int num);
int min(int num1, int num2);

int main(void)
{
    // Initialize variables
    FILE *fptr = fopen("input.txt", "r"); // Open input file
    int input_size = 10000; // Max number of characters for input
    char *input = calloc(input_size, sizeof(char)); // Allocate memory for the input
    int total = 0;
    int active = 1; // This tells us whether to apply the mul based upon do()/don't()

    while (fgets(input, input_size, fptr))
    {
        // Iterate over each instance of mul(
        char *mul_check = input;
        char *do_check = input;
        char *dont_check = input;

        // Loop only while we are still finding mul(
        while (mul_check = strstr(mul_check, "mul("))
        {
            int do_diff;
            int dont_diff;
            int mul_diff = mul_check - input;
            // Run through all three checks and find the lowest one and apply its corresponding case
            // If strstr cannot find the substring, it will return null. When this happens, we want to disable the diff (since there are no more do/dont statements) by setting the diff to MAX
            if (strstr(do_check, "do()"))
            {
                do_check = strstr(do_check, "do()"); 
                do_diff = do_check - input;
            }
            else
            {
                do_diff = MAX;
            }

            if (strstr(dont_check, "don't()"))
            {
                dont_check = strstr(dont_check, "don't()"); 
                dont_diff = dont_check - input;
            }
            else
            {
                dont_diff = MAX;
            }

            int minimum = min(mul_diff, min(do_diff, dont_diff));

            if (minimum == mul_diff)
            {
                int num1 = 0;
                int num2 = 0;
                // Skip past the mul(
                mul_check += 4;

                // Check for the first number after mul(
                if (atoi(mul_check) != 0)
                {
                    num1 = atoi(mul_check);                    }

                // Skip past num1
                mul_check += count_digits(num1);

                // Check for the , after num1, then check for num2
                if (mul_check[0] == ',')
                {
                    mul_check++;
                    if (atoi(mul_check) != 0)
                    {
                        num2 = atoi(mul_check);
                    }
                }

                // Skip past num2
                mul_check += count_digits(num2);

                // Only add product to total if mul( ends with a closing ) and mul is active
                if (mul_check[0] == ')' && active == 1)
                {
                    total += num1 * num2;
                }
            }

            // If we hit do() set active high and skip over it
            if (minimum == do_diff)
            {
                active = 1;
                do_check += 4;
            }

            // If we hit dont() set active low and skip over it
            if (minimum == dont_diff)
            {
                active = 0;
                dont_check += 7;
            }
        }
    }
    printf("[*] Total: %d\n", total);
}

// Function that returns the number of digits in num
int count_digits(int num)
{
    int count = 1;
    while (num > 9)
    {
        num /= 10;
        count++;
    }
    return count;
}

// Function to return the minimum of three ints
int min(int num1, int num2)
{
    if (num1 < num2)
    {
        return num1;
    }
    else
    {
        return num2;
    }
}