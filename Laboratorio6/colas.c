#include <stdio.h>
#include <stdlib.h>


// Qeue list where the head node has the least priority and the last node the highest
// Node
typedef struct node
{
    // Node's data
    int data;
    // Node's priority
    int priority;
    // Pointer to next node
    struct node *next; 
} NODO;

// Functions
// d stands for data and pr for priority
NODO *new_node(int d, int pr);
void insert(NODO **head, int d, int pr);
void getHighestPriority(NODO **head);
void deleteHighestPriority(NODO **head);
void printList(NODO *head);
void deleteList(NODO *head);

int main()
{
    // Create a node (head)
    NODO *head = NULL;
    head = new_node(4, 1);

    insert(&head, 9, 2);
    insert(&head, 8, 3);
    insert(&head, 10, 4);

    printList(head);

    getHighestPriority(&head);
    deleteHighestPriority(&head);

    printList(head);
    deleteList(head);
    return 0;
}

// Function new node
NODO *new_node(int d, int pr)
{
    // Creating a node and allocating the memory for it
    NODO* new = NULL;
    new = (NODO*)malloc(sizeof(NODO));
    // Check if it was created
    if(new != NULL)
    {
        // Assign values
        new->data = d;
        new->priority = pr;
        new->next = NULL;
    }
    return new;
}

// Insert new node
void insert(NODO **head, int d, int pr)
{
    // Creating a new node with last function
    NODO* new = NULL;
    new = new_node(d, pr);
    // Node to travel the list (head node)
    NODO* temp = NULL;
    temp = (*head);
    // Check if it was created
    if(new != NULL)
    {
        // Check if the priority of the new node is less than the head one
        if(temp->priority > pr)
        {
            // New node will be added before the temp node
            new->next = temp;
            (*head) = new;
        }
        else
        {
            // Travel the list, checking if it's the end and priority of each node
            while(temp->next != NULL && temp->next->priority < pr)
            {
                temp = temp->next;
            }
            // Temp will have the value of the node with bigger priority than the new one, so we need to add the new one before it
            new->next = temp->next;
            temp->next = new;
        }
    }
}

// Print value with highest priority
void getHighestPriority(NODO **head)
{
    if((*head) == NULL)
    {
        printf("List is empty. Exiting program.\n");
        exit(0);
    }
    else
    {
        // Save the values of the head node
        int maxVal = (*head)->data, pr = (*head)->priority;
        // Node to travel the list
        NODO* temp = NULL;
        temp = (*head)->next;
        // Travel the list
        while(temp != NULL)
        {
            // Check if the priority of a new node is bigger
            if(temp->priority > pr)
            {
                // Change values
                maxVal = temp->data;
                pr = temp->priority;
            }
            // Travel the lsit
            temp = temp->next;
        }
        printf("The data with highest priority is: %d and it's priority is: %d\n", maxVal, pr);
    }
}

// Delete value with highest priority
void deleteHighestPriority(NODO **head)
{
    if((*head) == NULL)
    {
        printf("List is empty. Exiting program.\n");
        exit(0);
    }
    else
    {
        // Node to travel the list (head node)
        NODO* temp = NULL;
        temp = (*head);
        // Save data and priority value
        int d, pr;
        // Travel the list until the last node (highest priority)
        while(temp->next->next != NULL)
        {
            temp = temp->next;
        }
        // Save values on the variables
        d = temp->next->data;
        pr = temp->next->priority;
        printf("%d was deleted from the queue list and it's priority was %d\n", d, pr);
        // Delete last node
        NODO* lastNode = NULL;
        lastNode = temp->next;
        temp->next = NULL;
        // Free the node's memory
        free(lastNode);
    }
}

// Print queue list
void printList(NODO *head)
{
    // Temporary node
    NODO *temp = head;
    // Travel the list
    while(temp != NULL)
    {
        //Print data value
        printf("%d\n", temp->data);
        // Change pointer
        temp = temp->next;
    }
}

// Delete list
void deleteList(NODO *head)
{
    NODO *temp;
    // Travel until the end
    while(head != NULL)
    {
        temp = head;
        head = head->next;
        // Delete node and free it's memory
        free(temp);
    }
}