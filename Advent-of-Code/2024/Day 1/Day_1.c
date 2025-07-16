#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void *b);
int exact_search(int *arr, int arr_size, int obj);
int main(void)
{
    // Initialize variables
    FILE *fptr = fopen("input.txt", "r"); // Open input file
    int input_size = 10000; // Max number of characters for input
    int num_lines = 1000;
    char *input = calloc(input_size, sizeof(char)); // Allocate memory for the input
    
    // Create 2 arrays to store the different lists
    int *lft_arr = calloc(num_lines, sizeof(int));
    int *rt_arr = calloc(num_lines, sizeof(int));
    int i = 0;
    while(fgets(input, input_size, fptr))
    {
        lft_arr[i] = atoi(strtok(input, "   "));
        rt_arr[i] = atoi(strtok(NULL, "   "));     
        i++;
    }
    


    // // TOTAL DISTANCE CALCULATION
    // // Sort the arrays to easily find the distances between each pairing
    // qsort(lft_arr, num_lines, sizeof(int), compare);
    // qsort(rt_arr, num_lines, sizeof(int), compare);

    // // Compare the distance between each pair and keep a total
    // int dist_total = 0;
    // for (int i = 0; i < num_lines; i++)
    // {
    //     dist_total += abs(lft_arr[i] - rt_arr[i]);
    // }

    // printf("Total: %d\n", dist_total);



    // // SIMILARITY SCORE CALCULATION
    // // We iterate over each elements in lft_arr and calculate the similarity score by multiplying it by the number of times the element appears in rt_arr
    // int similarity_total = 0;
    // for (int i = 0; i < num_lines; i++)
    // {
    //     similarity_total += lft_arr[i] * exact_search(rt_arr, num_lines, lft_arr[i]);
    // } 

    // printf("Total: %d\n", similarity_total);

    free(input);
    free(lft_arr);
    free(rt_arr);
}

// Compare function for qsort
int compare(const void* a, const void *b)
{
    return (*(int*)a - *(int*)b);
}

// Function that returns the number of times obj appears in arr
int exact_search(int *arr, int arr_size, int obj)
{
    int total = 0;
    for (int i = 0; i < arr_size; i++)
    {
        if (arr[i] == obj)
        {
            total += 1;
        }
    }
    return total;
}