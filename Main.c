#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

/*
-------------------------------------
Functions That I Used

-function that counts number of character in the array
-function that copies strings
-Creating a new node
-organizing the nodes in alphabetical list of the lastname
-function that searches for lastName and if found, outputs the name, lastName, and telNo
-function that checks if the lastname that user wants the input or delete is in the list
-Deleting all the nodes in the linked list
-function that prints everything in the node one at a time
-function that reads the inputted characters from u
-printf functions that helps the int main look clean
------------------------------------


*/


typedef struct node {
    char *name;
    char *lastName;
    int *telNo;
    struct node *link;
} Node;

int stringLength(char s[]) //function that counts number of character in the array
{
    int i = 0;
    while (s[i] != '\0') {
        i = i + 1;
    }
    return i;
}

void stringCopy(char *destination, char *source) { //function that copies strings
    while (*source != '\0') {
        *destination = *source;
        destination++;
        source++;
    }
    *destination = '\0';
}

//Creating a new node

Node *newNode(char *name, char *lastName, int *telNo, Node *link) {
    Node *t = (Node *) malloc(sizeof (Node)); //dynamic allocating memory for this node
    if (t != NULL) { //if there is enough memory
        t->name = malloc(sizeof (char)*stringLength(name)); //dynamically allocating memory for each of the 3 strings
        stringCopy(t->name, name); //copying the variable into the allocated memory
        t->lastName = malloc(sizeof (char)*stringLength(lastName));
        stringCopy(t->lastName, lastName);
        t->telNo = malloc(sizeof (int)*stringLength(telNo));
        stringCopy(t->telNo, telNo);
        t->link = link;
    }
    return t;
}


int countNodesInList(Node *head)
{
int count = 1;
Node *temp1 = head;
while(temp1->link!=NULL)
{
    count++;
    temp1 = temp1->link;
}
return count;
}


//organizes the nodes in alphabetical list of the lastname

Node *insertIntoOrderedList(Node *head, char *name, char *lastName, int *telNo) {

    //if the value that user entered is smaller than the first node, or smaller than the head node
    if (head == NULL || (strcmp(lastName, head->lastName)) < 0) {
        return newNode(name, lastName, telNo, head); //a new head of the list
    }
    Node *current = head;
    //if the value that user entered is bigger than the head
    while (current->link != NULL && (strcmp(lastName, current->link->lastName)) > 0) {
        current = current ->link;
    }
    current -> link = newNode(name, lastName, telNo, current ->link);
    return head;
}

bool searchForLastName(Node *head, char *lastName) //function that searches for lastName and if found, outputs the name, lastName, and telNo
{
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current ->lastName, lastName) == 0) {
            printf("\nThe lastname '%s' was found in the library.\n", lastName);
            printf("\n%s\n%s\n%s\n", current ->name, current->lastName, current->telNo);
            return true;
        }
        current = current ->link;
    }
    return false;
}
//function that checks if the lastname that user wants the input or delete is in the list

bool searchLastNameToBeInsertedOrDeleted(Node *head, char *lastName) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current ->lastName, lastName) == 0) {
            return true;
        }
        current = current ->link;
    }
    return false;
}
//Deleting all the nodes in the linked list

Node *deleteAllNodes(Node *head) {
    while (head != NULL) {
        printf("\nDeleting a lastname '%s' from the library.\n", head->lastName);
        Node *firstNode = head;
        head = head->link; //head points to the next node
        free(firstNode); //free the allocated memory
        return head;
    }
    return NULL;
}

void printList(Node *head) { //function that prints everything in the node one at a time
    Node *current = head;
    while (current != NULL) {
        printf("\n%s\n", current ->name);
        printf("%s\n", current->lastName);
        printf("%s\n", current ->telNo);
        current = current ->link;
    }
}

void getStringFromUserInput(char s[], int arraySize) { //function that reads the inputted characters from u
    char c;
    int i = 0;
    while (i < arraySize && (c = getchar()) != '\n') {
        s[i++] = c;
    }

    s[i] = '\0';
}

void lastNameDuplicate(char lastName[]) {
    printf("\nThis lastname '%s' is already in the library.\nNo new lastname entered.\n", lastName);
}

void lastNameFound(char lastName[]) {
    printf("\nThe lastname '%s' was found in the library.\n", lastName);
}

void lastNameNotFound(char lastName[]) {
    printf("\nThe lastname '%s' was not found in the music library.\n", lastName);
}


void printLibraryEmpty(void) //function to call when printing an empty phone book
{
    printf("\nThe library is empty.\n");
}

void printLibraryTitle(void) {
    printf("\nMy Personal Phone Book: \n");
}
const int MAX_LENGTH = 1024;

int main(int argc, char** argv) {
    int z = 0;
    Node *head = NULL; //initializing head
    printf("%s", "Personal Phone Book.\n\n");
    printf("Commands are:\n I (insert)\n P (print)\n Q (quit).\n");
    printf("Please make sure all the lastnames are the same type.(uppercase or lowercase)\n");

    //declaring variables
    char response;
    bool duplicate;
    char input[MAX_LENGTH + 1];
    char inputName[MAX_LENGTH + 1]; //array for the name
    char inputLastName[MAX_LENGTH + 1]; //array for the lastname
    char inputTelNo [MAX_LENGTH + 1]; //array for the telno
    do {
        printf("\nCommand?: "); //prompt the user to enter a command
        getStringFromUserInput(input, MAX_LENGTH); //reads user input
        response = toupper(input[0]); //convert to upper case to simplify comparison

        if (response == 'I') { //inserting phone book order by lastname
                printf("\n");
            printf(" %d. person:\n ",z+1);
            printf("Enter name: "); //prompting for data
            getStringFromUserInput(inputName, MAX_LENGTH);
            printf(" Enter lastname: ");
            getStringFromUserInput(inputLastName, MAX_LENGTH);
            printf(" Enter the telephone number: ");
            getStringFromUserInput(inputTelNo, MAX_LENGTH);
            duplicate = searchLastNameToBeInsertedOrDeleted(head, inputLastName); // check if the lastname that user inputs already exists in the link
            z++;
            if (duplicate == true) //check for duplicates
            {
                lastNameDuplicate(inputLastName);
            }
            else {
                head = insertIntoOrderedList(head, inputName, inputLastName, inputTelNo);

            }
        } 
        else if (response == 'P') //prints out everything in the list
        {
            if (head == NULL) {
                printLibraryEmpty();
            }
            else {
                printf("-----------------------------------");
                printf("\n%d person has been recorded.\n",countNodesInList(head));
                printLibraryTitle();
                printList(head);
                printf("-----------------------------------");
            }
        }
        
        else if (response == 'Q') {
            //Do nothing
        }
        else {
            //when no command matched
            printf("\nInvalid command.\n");
        }
        
    } while (response != 'Q');
    while (head != NULL && head != NULL) //prints out delete statement one by one till the link is empty
    {
        head = deleteAllNodes(head);
    }
    if (head == NULL) {
        printLibraryEmpty();
    }
    return (EXIT_SUCCESS);
}
