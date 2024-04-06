

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "a2_nodes.h"
#include "a2_functions.h"

int main()
{
    /* THIS CODE WILL LOAD THE DATABASE OF USERS FROM THE FILE
       AND GENERATE THE STARTING LINKED LIST.
    */
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);

    printf("\n*****************************************************");
    printf("\n          Welcome to the text-based Facebook         ");
    printf("\n*****************************************************");
    int choice;
    user_t *new_user = NULL;
    char name[30];
    char pwd[15];

    while (choice != 3)
    {
        print_menu();
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        if (choice > 0 && choice <= 3)
        {
            switch (choice)
            {
            case 1:
                printf("Enter a username:");
                scanf("%29s", name);
                user_t *check = find_user(users, name);
                if (check != NULL)
                {
                    printf("\n--------------------------------------------------\n"
                           "\tUsername already exist in the databse!\n"
                           "--------------------------------------------------\n");
                }
                else
                {
                    printf("Enter an upto 15 characters password: ");
                    scanf("%14s", pwd);
                    users = add_user(users, name, pwd);
                    printf("\n**** User added! ****\n");
                }
                break;

            case 2:
                printf("Enter a username:");
                scanf("%29s", name);
                printf("Enter an upto 15 characters password: ");
                scanf("%14s", pwd);
                user_t *temp;
                temp = find_user(users, name);
                if (temp != NULL && strcmp(temp->username, name) == 0)
                {
                    if (strcmp(temp->password, pwd) == 0)
                    {
                        user_menu(temp);
                    }
                    else
                    {
                        printf("Password is incorrect, Try again!\n");
                    }
                }
                else
                {
                    printf("--------------------------------------------------\n");
                    printf("\t\tUser does not exist\n");
                    printf("--------------------------------------------------\n");
                }
                break;
            case 3:
                teardown(users);
                // teardown(users->friends);
                // teardown(users->posts);
                printf("*****************************************************\n");
                printf("  Thank you for chosing the text based Facebook    \n");
                printf("\t\tGoodBye!\n");
                printf("*****************************************************\n");
                break;

            default:
                break;
            }
        }
        else
        {
            printf("Invalid Choice, Please try agian");
        }
    }
}
