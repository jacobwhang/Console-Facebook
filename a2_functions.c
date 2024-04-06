

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "a2_nodes.h"
#include "a2_functions.h"
#include <assert.h>


/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, const char *username, const char *password)
{
   user_t *user = malloc(sizeof(user_t));
   assert(user != NULL);
   strcpy(user->username, username);
   strcpy(user->password, password);
   user->friends = NULL;
   user->posts = NULL;

   user_t *temp = users;
   // base case: if the list is empty or data in new node is less than the head node data
   if (users == NULL || strcmp(user->username, users->username) < 0)
   {
      user->next = users;
      return user;
   }
   // loop through nodes to find the location where new node can placed
   while (temp->next != NULL && strcmp(user->username, temp->next->username) > 0)
   {
      temp = temp->next;
   }
   user->next = temp->next;
   temp->next = user;
   return users;
}
/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, const char *username)
{
   assert(users != NULL);
   while (users != NULL)
   {
      if (strcmp(users->username, username) == 0)
      {
         return users;
      }
      users = users->next;
   }
   return NULL;
}
/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(const char *username)
{
   friend_t *friend = malloc(sizeof(friend_t));
   assert(friend != NULL);
   strcpy(friend->username, username);
   return friend;
}



/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend( user_t *user, const char *friend)
{

   friend_t *new_friend = create_friend(friend);
   

   // base case: if the list is empty or new node data is smaller than the head node data
   if (user->friends == NULL || strcmp(friend, user->friends->username) < 0)
   {
      new_friend->next = user->friends;
      user->friends = new_friend;
   }
   else
   {
      friend_t *current = user->friends;
      while (current->next != NULL && strcmp(new_friend->username, current->next->username) > 0)
      {
         current = current->next;
      }
      new_friend->next = current->next;
      current->next = new_friend;
   }
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
   friend_t *current = user->friends;
   friend_t *previous = NULL;

   // find the location of the current node where username matches friends name
   while (current != NULL && strcmp(current->username, friend_name) != 0)
   {
      previous = current;
      current = current->next;
   }
   // Base Case: check if the current node is not empty
   if (current != NULL)
   {
      if (previous != NULL)
      {
         previous->next = current->next;
      }
      else
      {
         // if the username is found at the first node
         user->friends = current->next;
      }
      // free the memory where the node is to be deleted
      free(current);
      return 1;
   }
   else
   {
      printf("Invalid friend's name.\n");
      return 0;
   }
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
   post_t *post = malloc(sizeof(post_t));
   assert(post != NULL);
   strcpy(post->content, text);
   post->next = NULL;
   return post;
}

/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t *user, const char *text)
{
   post_t *new_post = create_post(text);
   new_post->next = user->posts;
   user->posts = new_post;
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user, int number)
{
   post_t *post = user->posts;
   int count = 0;
   // base case: If the node to be deleted at the head
   if (number - 1 == 0)
   {
      user->posts = post->next;
      free(post);
      printf("\nPost %d deleted successfully!", number);
      return 1;
   }
   while (post != NULL && count < number - 2)
   {
      post = post->next;
      count++;
   }
   // base case: if the position is valid
   if (post == NULL || post->next == NULL)
   {
      printf("\nInvalid post's number");
      return 0;
   }
   post_t *temp = post->next->next;

   free(post->next);
   post->next = temp;
   printf("\nPost %d deleted successfully!", number);

   return 1;
}

/*
   Function that  displays a specific user's posts
*/
void display_user_posts(user_t *user)
{
   int counter = 1;
   post_t *post = user->posts;
   // base case: if the list is empty
   if (post == NULL)
   {
      printf("No posts available for %s.\n", user->username);
   }
   while (post != NULL)
   {

      printf("%d- %s: %s\n", counter, user->username, post->content);
      post = post->next;
      counter++;
   }
}

/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t *user)
{

   printf("\nList of %s's friends: \n", user->username);
   int counter = 1;
   friend_t *friend = user->friends;
   // base case: if the list if empty
   if (friend == NULL)
   {
      printf("No friends available for %s.\n", user->username);
   }
   while (friend != NULL)
   {
      printf("%d- %s\n", counter, friend->username);
      friend = friend->next;
      counter++;
   }
}
/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_all_posts(user_t *users)
{
   char choice;
   int counter = 0;
   user_t *user = users;
   while (user != NULL)
   {
      if (counter < 2)
      {
         display_user_posts(user);
         user = user->next;
         counter++;
      }
      else
      {
         printf("\nDo you want to display next 2 users posts: ");
         scanf(" %c", &choice);
         if (choice == 'y' || choice == 'Y')
         {
            counter = 0;
         }
         else if (choice == 'n' || choice == 'N')
         {
            return;
         }
         else
         {
            printf("Invalid input!\n");
         }
      }
   }
}

/*
   Fucntion that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
   user_t *delete_user;
   while (users != NULL)
   {
      delete_user = users;
      users = users->next;
      free(delete_user);
   }
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{
   printf("\n\n*****************************************************\n"
          "                      Main Menu                      \n"
          "*****************************************************\n");
   printf("1. Register new User\n"
          "2. Login with existing users's information\n"
          "3. Exit");
}
void user_menu(user_t *user)
{
   _Bool post_choice;
   _Bool friend_choice;
   int choice;
   while (choice != 5)
   {
      printf("\n\n*****************************************************\n"
             "                   Welcome %s:                     \n"
             "*****************************************************\n",
             user->username);
      printf("1. Manage a user's profile (change password)\n"
             "2. Manage a user's post (display/add/remove)\n"
             "3. Manage a user's friend (display/add/remove)\n"
             "4. Display all posts\n"
             "5. Logout\n");
      printf("\nYour Choice: ");
      scanf("%d", &choice);
      if (choice > 0 && choice < 6)
      {

         switch (choice)
         {
         case 1:
            printf("Enter a new password that is upto 15 characters: ");
            scanf("%14s", user->password);
            printf("\n**** Password Changed! ****\n");
            break;

         case 2:
            post_choice = 1;

            while (post_choice)
            {
               printf("\n-----------------------------------------------------\n");
               printf("\t\t %s's posts \n", user->username);
               display_user_posts(user);
               printf("-----------------------------------------------------\n");
               post_choice = post_menu(user);
            }

            break;
         case 3:
            friend_choice = 1;
            user_t *current_friends = user;
            if (current_friends != NULL)
            {
               while (friend_choice)
               {
                  printf("\n-----------------------------------------------------\n");
                  printf("\t\t %s's friends\n", current_friends->username);
                  printf("-----------------------------------------------------\n");
                  friend_choice = friend_menu(current_friends);
               }
            }
            else
            {
               printf("-----------------------------------------------------\n");
               printf("\t\tUser Not found\n");
               printf("-----------------------------------------------------\n");
            }
            break;
         case 4:
            display_all_posts(user);
            break;

         default:
            printf("-----------------------------------------------------\n");
            printf("\t\tLogged out!\n");
            printf("-----------------------------------------------------\n");
      
            break;
         }
      }
      else
      {
         printf("Invalid Choice, Please try agian\n");
      }
   }
}


_Bool post_menu(user_t *user)
{
   int choice;
   printf("1. Add a new user post.\n"
          "2. Remove a users post.\n"
          "3. Return to main menu.\n");
   printf("\nYour Choice: ");
   scanf("%d", &choice);
   int number;
   char new_post_content[250];

   // base case: check if user input correct value.
   if (choice >= 1 && choice <= 3)
   {
      switch (choice)
      {
      case 1:
         printf("\nEnter your post content: ");
         scanf(" %[^\n]s", new_post_content);
         add_post(user, new_post_content);
         printf("Post added to your profile.\n");
         return 1;
         break;
      case 2:
         printf("\nWhich post you want me to delete : ");
         scanf("%d", &number);
         delete_post(user, number);
         return 1;
         break;
      case 3:
         return 0;
         break;
      }
   }
   else
   {
      printf("Invalid Choice. Please try again.");
      return 1;
   }

   return 0;
}

_Bool friend_menu(user_t *user)
{
   int choice;
   printf("\n1. Display all user's friends."
          "\n2. Add a new friend."
          "\n3. Delete a friend."
          "\n4. Return to main menu.");
   printf("\n\nYour Choice: ");
   scanf("%d", &choice);
   char friend_name[30];
   _Bool friend_deleted = 0;
   if (choice >= 1 && choice <= 4)
   {
      switch (choice)
      {
      case 1:
         display_user_friends(user);
         return 1;
         break;
      case 2:
         printf("Enter a new friend's name: ");
         scanf("%29s", friend_name);
         add_friend(user, friend_name);
         printf("Friend added to the list.\n");
         return 1;
         break;
      case 3:
         display_user_friends(user);
         printf("\nEnter a friend's name to delete: ");
         scanf("%29s", friend_name);
         friend_deleted = delete_friend(user, friend_name) ? 1 : 0;
         display_user_friends(user);
         return 1;
         break;
      case 4:
         return 0;
      }
   }
   else
   {
      printf("Invalid Choice. Please try again.");
      return 1;
   }

   return 0;
}


user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
   user_t *users = NULL;
   char buffer[500];
   fgets(buffer, sizeof(buffer), file); // Read and discard the header line
   int count = 0;

   for (int i = 0; i < num_users; i++)
   {
      fgets(buffer, sizeof(buffer), file);

      buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

      char *token = strtok(buffer, ",");
      char *token2 = strtok(NULL, ",");

      users = add_user(users, token, token2);

      char *username = token;

      token = strtok(NULL, ",");

      user_t *current_user = users;

      for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
         ;

      while (token != NULL && strcmp(token, ",") != 0 && count < 3)
      {

         if (strcmp(token, " ") != 0)
         {
            add_friend(current_user, token);
         }
         token = strtok(NULL, ",");
         count++;
      }
      count = 0;

      while (token != NULL && strcmp(token, ",") != 0)
      {
         add_post(current_user, token);
         token = strtok(NULL, ",");
      }
   }
   return users;
}
