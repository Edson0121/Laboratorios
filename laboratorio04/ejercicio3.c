#include <stdio.h>
#include <stdlib.h>
#include <string.h> // To use strndup function

int * getUserTime(FILE* fpointer);
char** getUserName(FILE* fpointer, int *length);
void userName(char** arrayName, int sizeArray);
void userCondition(char** arrayName, int *timeArray, int sizeArray);
void sortUsers(char** arrayName, int *timeArray, int sizeArray);
void updateUserData(FILE* fpointer);

int main(int argc, char* argv[])
{
    // Print menu 
    printf("\t\t***********************************\n"); 
    printf("\t\t********** WORKING MENU ***********\n"); 
    printf("\t\t***********************************\n"); 
    printf("\t\t1-Print the user list.\n"); 
    printf("\t\t2-Print the list of users and their\n");
    printf("\t\tstatus.\n");
    printf("\t\t3-Sort users by last access time.\n"); 
    printf("\t\t4-Update a user's data.\n");  
    printf("\t\tPlease enter the number of the option\n");
    printf("\t\tyoull like to execute.\n\n"); 
    printf("\t\t***********************************\n\n\n"); 
    int optionChosed;
    printf("Please enter your option: ");
    scanf("%d", &optionChosed);
    // File pointer
    FILE *fpointer;
    // Open the file
    fpointer = fopen("user_list.txt", "r+");
    if(fpointer == NULL)
    {                                                       
        printf("\nError opening file.\nExiting program.\n");                              
        exit(1);
    }
    // Lenght of array
    int length;
    // Get Arrays
    char** userNameArray = getUserName(fpointer, &length);
    int *userTimeArray = getUserTime(fpointer);
    // Choose option
    if(optionChosed == 1)
    {
        userName(userNameArray, length);
    }
    else if(optionChosed == 2)
    {
        userCondition(userNameArray, userTimeArray, length);
    }
    else if(optionChosed == 3)
    {
        sortUsers(userNameArray, userTimeArray, length);
    }
    else if(optionChosed == 4)
    {
        updateUserData(fpointer);
    }
    else
    {
        printf("\nOption entered not valid.\nExiting program.\n");
        exit(1);
    }
    // Close the file and free memory
    fclose(fpointer);
    free(userTimeArray);
    free(userNameArray);
    return 0;
}

void userName(char** arrayName, int sizeArray)
{
    // Counter for array
    int i;
    // Print each element in the array
    for(i = 0; i < sizeArray - 1; i++)
    {
        printf("User #%d name: %s", i ,arrayName[i]);
    }
}

void userCondition(char** arrayName, int *timeArray, int sizeArray)
{
    // Counter of the array
    int i;
    // Check last time access
    for(i = 0; i < sizeArray - 1; i++)
    {
        if(timeArray[i] == 0)
        {
            printf("User %scondition: %d (active)\n\n", arrayName[i], 0);
        }
        else if(timeArray[i] > 0 && timeArray[i] <= 3)
        {
            printf("User %scondition: %d (recent)\n\n", arrayName[i], 1);
        }
        else
        {
            printf("User %scondition: %d (inactive)\n\n", arrayName[i], 2);
        }
    }
}

void sortUsers(char** arrayName, int *timeArray, int sizeArray)
{
    // Temporary variable to sort timeArray
    int temp = 0;
    // Temporary variable to sort arrayName
    char name[50];
    // Variables for loop
    int i, j;
    // Sort array in asceding order
    printf("\nUsers ordered by last time access: \n\n");
    for(i = 0; i < sizeArray - 1; i++)
    {
        for(j = i + 1; j < sizeArray - 1 - i; j++)
        {
            if(timeArray[j] > timeArray[j+1])
            {
                temp = timeArray[i];
                strcpy(name, arrayName[i]);
                timeArray[i] = timeArray[j];
                arrayName[i] = arrayName[j];
                timeArray[j] = temp;
                arrayName[j] = name;
            }
        }
        printf("User %slast time connected: %d days ago.\n\n", arrayName[i], timeArray[i]);
    }
}

void updateUserData(FILE* fpointer)
{
    // Variable for option
    int option;
    printf("Do you want to update a user information (1) or add a new user (2)?\n");
    scanf("%d", &option);
    if(option == 1)
    {
        // Variables for new line
        int bufferSize = 50;
        size_t maxSz = 50;
        int count = 0;
        char *newLine;
        newLine = (char *)malloc(maxSz);
        char singleLine[bufferSize];
        // Pointer to temporary file
        FILE * tempPtr;
        // Print each line in the original file
        while (!feof(fpointer))
        {
            count++;
            fgets(singleLine, bufferSize, fpointer);
            printf("Line #%d: %s", count, singleLine);
        }
        // Set fpointer back to beginning
        fseek(fpointer, 0, SEEK_SET);
        // Line to replace
        int line;
        printf("Enter line number to replace, remember it starts in 1: ");
        scanf("%d", &line);
        getchar();
        // Remove extra new line character from stdin
        // fflush(stdin);
        // Get new line
        int bytes_read;
        printf("Replace line '%d' with: ", line);
        bytes_read = getline(&newLine, &maxSz, stdin);
        if(bytes_read == -1)
        {
            perror(NULL);
            exit(1);
        }
        // Pointer to temporary file
        tempPtr = fopen("replace.tmp", "w");
        // Check if pointer is NULL
        if(tempPtr == NULL)
        {
            printf("\nError opening file.\nExiting program.\n");                              
            exit(1);
        }
        // Read each line from source file and write it in destination file
        count = 0;
        while (!feof(fpointer))
        {
            // Get each line
            fgets(singleLine, bufferSize, fpointer);
            count++;
            // If current line is the one to replace
            if(count == line)
            {
                fputs(newLine, tempPtr);
            }
            else
            {
                fputs(singleLine, tempPtr);
            }
        }

        // Close file
        fclose(tempPtr);
        free(newLine);
        // Delete old file
        remove("user_list.txt");
        // Rename temporary file
        rename("replace.tmp", "user_list.txt");
        printf("Succesfully updated the information in the file.\n");
    }
    else if(option == 2)
    {

        // Move pointer to end of file
        fseek(fpointer, 0, SEEK_END);
        // Variables for inputs
        char name[50];
        char id[8];
        char days[10];
        // Ask name
        printf("You chose to add a new user. Please enter the new information.\n");
        printf("Enter your name: ");
        scanf("%s", name);
        // Write name on file
        fprintf(fpointer, "%s\n", name);
        // Ask ID
        printf("\nEnter your ID (8 digits): ");
        scanf("%s", id);
        // Write ID on file
        fprintf(fpointer, "%s\n", id);
        // Ask last date accessed
        printf("\nLast day accessed: ");
        scanf("%s", days);
        // Write date on file
        fprintf(fpointer, "%s\n", days);
        printf("Succesfully added a new user.\n");
    }
    else
    {
        printf("\nOption entered not valid.\nExiting program.\n");
        exit(1);
    }
}


char** getUserName(FILE* fpointer, int *length)
{
    // Array with user's names
    char ** userNameArray = malloc(20 * sizeof(char*));
    // Store the content of each line in the text file
    char singleLine[50];
    // Counter for lines in text and for the array
    int counter = 0, i = 0;
    // Loop until the end of the file
    while(!feof(fpointer))
    {
        // Get each line in the file and store it
        fgets(singleLine, 50, fpointer);
        // Only check user's name
        if(counter%3 == 0)
        {
            // Save space for string
            userNameArray[i] = malloc(50 * sizeof(char));
            // Save string in array
            userNameArray[i] = strndup(singleLine, 50);
            i++;
        }
        counter++;
    }
    fseek(fpointer, 0, SEEK_SET);
    *length = i;
    return userNameArray;
}

int * getUserTime(FILE* fpointer)
{
    // Array with last time access
    int* userTimeArray = malloc(21 * sizeof(int));
    // Store the content of each line in the text file
    char singleLine[50];
    // Counter for lines in text and for the array
    int counter = 1, i = 0;
    // Loop until the end of the file
    while(!feof(fpointer))
    {
        // Get each line in the file and store it
        fgets(singleLine, 20, fpointer);
        // Only check for user's time
        if(counter%3 == 0)
        {
            // Save time in array as int
            userTimeArray[i] = atoi(singleLine);
            i++;
        }
        counter++;
    }
    fseek(fpointer, 0, SEEK_SET);
    return userTimeArray;
}