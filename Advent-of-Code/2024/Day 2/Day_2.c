#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node *next;
};

struct node *append_node(struct node **head_reference, int num);
struct node *print_list(struct node *head);
struct node *delete_list(struct node **head_reference);
struct node *list_copy(struct node *head);
void remove_node(struct node **head_reference, int i);
int list_len(struct node *head);

int check_list_change(struct node *head);
int space_counter(char *str);
int inclusive_check(struct node *head);
int is_safe(struct node *head);

int main(void)
{
    // Initialize variables
    FILE *fptr = fopen("input.txt", "r"); // Open input file
    int input_size = 10000; // Max number of characters for input
    int num_lines = 1000;
    char *input = calloc(input_size, sizeof(char)); // Allocate memory for the input
    int num_safe = 0;

    while (fgets(input, input_size, fptr))
    {
        // We need to call this function before strtok because strtok changes the input string
        int space_count = space_counter(input);
        struct node *list = NULL;
        append_node(&list, atoi(strtok(input, " ")));
        
        // We will call strtok one time for each int in input
        // Even though the number of ints is 1 greater than the number of spaces (the last int doesn't have a space after it)
        // We only iterate the number of spaces because we need to iterate one less than the number of ints since we already called strtok on the first int
        for (int i = 0; i < space_count; i++)
        {
            append_node(&list, atoi(strtok(NULL, " ")));
        }

        // Add to the safe report counter iff diff_check and inc_dec_check both pass
        if (is_safe(list))
        {
            num_safe += 1;
        }
        else
        {
            int list_length = list_len(list);
            for (int i = 0; i < list_length; i++)
            {
                struct node *copy = list_copy(list);
                remove_node(&copy, i);
                if (is_safe(copy))
                {
                    num_safe += 1;
                    break;
                }
            }
        }
    }

    printf("[*] Safe Reports: %d\n", num_safe);
    free(input);
}

// Function for appending an int to a linked list
struct node *append_node(struct node **head_reference, int num)
{
    struct node *current = *head_reference;
    struct node *new_node;

    new_node = malloc(sizeof(struct node));
    new_node -> data = num;
    new_node -> next = NULL;

    if (current == NULL)
    {
        *head_reference = new_node;
    }
    else
    {
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_node;
    }
}

// Function for printing an entire linked list
struct node *print_list(struct node *head)
{
    printf("Linked list: ");
    while (head->next != NULL)
    {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("%d\n", head->data);
}

// Function to delete a linked list
struct node *delete_list(struct node **head_reference)
{
    struct node *temp = *head_reference;
    struct node *next;
    while(temp != NULL)
    {
        next = temp->next;
        free(temp);
        temp = next;
    }
    *head_reference = NULL;
}

// Function that returns 1 if the difference between any 2 nodes is between 1 and 3 (inclusive), 0 otherwise
int inclusive_check(struct node *head)
{
    struct node *next_node = head->next;
    while (head->next != NULL)
    {
        int abs_diff = abs(head->data - next_node->data);
        if (!(abs_diff >= 1 && abs_diff <= 3))
        {
            return 0;
        }
        head = head->next;
        next_node = head->next;
    }
    return 1;
}

// Function that checks whether a linked list always increases, decreases, or both
// Returns 1 if increasing, -1 if decreasing, and 0 if both
int check_list_change(struct node *head)
{
    int increase = 0;
    int decrease = 0;
    struct node *next_node = head->next;
    while (next_node != NULL)
    {
        if (next_node->data > head->data)
        {
            increase = 1;
        }
        if (next_node->data < head->data)
        {
            decrease = -1;
        }
        head = head->next;
        next_node = head->next;
    }
    return increase + decrease; // We return the sum because it reflects the conditions described above
}

// Function to return the number of spaces in a string
// We will use this to count the number of ints in our input from fgets
int space_counter(char *str)
{
    int count = 0;
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == ' ')
        {
            count += 1;
        }
    }
    return count;
}

// Function to check whether a report is safe
int is_safe(struct node *head)
{
    // Check to make sure that the difference between two node is between 1 and 3 (inclusive)
    int diff_check = inclusive_check(head);

    // Check to make sure that the list always increases or decreases
    int inc_dec_check = 0;
    if (check_list_change(head) != 0)
    {
        inc_dec_check = 1;
    }  

    // Return 1 if report passes both checks, otherwise return 0
    return diff_check && inc_dec_check;
}

// Function to return the length of a linked list
int list_len(struct node *head)
{
    int counter = 1;
    while (head->next != NULL)
    {
        counter += 1;
        head = head->next;
    }
    return counter;
}

// Function to remove a node from a linked list at position i
void remove_node(struct node **head_reference, int pos)
{
    struct node *temp = *head_reference;
    struct node *prev;

    if (pos == 0)
    {
        *head_reference = temp->next;
        return;
    }

    for (int i = 0; i < pos && temp != NULL; i++)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL)
    {
        prev->next = temp->next;
        free(temp);
    }
}

// Function to copy linked lists
struct node *list_copy(struct node *head)
{
    if (head == NULL)
    {
        return NULL;
    }
    else
    {
    struct node *new_node = malloc(sizeof(struct node));

    new_node->data = head->data;

    new_node->next = list_copy(head->next);

    return new_node;
    }
}