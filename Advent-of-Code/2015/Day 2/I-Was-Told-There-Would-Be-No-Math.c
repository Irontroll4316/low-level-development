#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "M:/Coding Stuff/C Functions/ironlib/ironlib.h"

int min(int val1, int val2);
int surface_area_with_slack(int length, int width, int height);
int ribbon_length(int length, int width, int height);

int main(void) 
{
    // Initialization
    FILE *fptr = fopen("input.txt", "r"); // Open input file
    int input_size = 10000; // Max number of characters for input
    char *input = malloc(sizeof(char) * input_size); // Allocate memory for the input
    
    int total_paper_area = 0;
    int total_ribbon_length = 0;

    while(fgets(input, input_size, fptr)) // Loop over the file to get each entry
    {
        // Delimit length, width, and height
        int length = atoi(strtok(input, "x"));
        int width = atoi(strtok(NULL, "x"));
        int height = atoi(strtok(NULL, "x"));

        total_paper_area += surface_area_with_slack(length, width, height);
        total_ribbon_length += ribbon_length(length, width, height);
    }

    printf("Total Paper Area: %i sq. feet\n", total_paper_area);
    printf("Total Ribbon Length: %i feet\n", total_ribbon_length);
}

// Function that returns the total surface area of a box including extra slack that equals the area of the smallest side
int surface_area_with_slack(int length, int width, int height)
{
        // Find the area of each side of the box
        int area_front = width * height;
        int area_side = length * height;
        int area_top = width * length;

        // Find the smallest area. This is the additional slack that must be added to the total
        int slack_area = min(min(area_front, area_side), area_top);

        // Add up the surface area of the current box including extra slack area and add it to the total
        return 2 * (area_front + area_side + area_top) + slack_area;
}

// Function that calculates the amount of ribbon needed for the present
int ribbon_length(int length, int width, int height)
{
    // Find the perimeter of each face
    int peri_front = 2 * (width + height);
    int peri_side = 2 * (length + height);
    int peri_top = 2 * (width + length);

    // Find the lowest perimeter. This is how much ribbon is takes to wrap the present
    int ribbon_to_wrap = min(min(peri_front, peri_side), peri_top);

    // Find the volume of the box. This is how much ribbon it takes to make a bow
    int ribbon_for_bow = length * width * height;

    // Return the total amount of ribbon required
    return ribbon_to_wrap + ribbon_for_bow;
}