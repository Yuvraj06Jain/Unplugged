#include "functions.h"

int new_account(Account** current_account,Account** accounts_head)
{
    char username[100]; printf("Username\n"); input(username);
    char password[100]; printf("Password\n"); input(password);
        
    *current_account = add_account(accounts_head,username,password);
    if(*current_account==NULL)
    {
        printf("Sorry, Username already Exists.Please Try Again\n\n");
        return 0;
    }
    printf("Account Creation Successsfull!\n\n");
    return 1;
}

Account* find_account(Account** head,char name[],char password[])
{
    Account* temp = *head;
    while(temp!=NULL)
    {
        if((!strcmp(temp->name,name)&&(!strcmp(temp->password,password))))
        {
            return temp;
        }

        temp = temp->next;
    }

    return NULL;
}

Account* open_account(Account* current_account,Account** accounts_head)
{
    char username[100]; printf("Username\n"); input(username);
    char password[100]; printf("Password\n"); input(password);
        
    current_account = find_account(accounts_head,username,password);
    if(current_account==NULL)
    {
        printf("Username or Password is wrong.Try again\n");
        return NULL;
    }
    printf("Successfully Logged in the account\n\n");
    return current_account;
}


Account* add_account(Account** head,char name[],char password[])
{
    Account* newAcc = (Account*)malloc(sizeof(Account));
    strcpy(newAcc->name,name);
    strcpy(newAcc->password,password);
    newAcc->albumCount = 0;
    newAcc->commands_count = 0;
    newAcc->album = NULL;
    newAcc->commands = NULL;
    newAcc->next = NULL;

    if(*head==NULL)
    {
        *head = newAcc;
        return *head;
    }
    Account* temp = *head;
    while(temp!=NULL)
    {
        if(!strcmp(temp->name,name))
        {
            free(newAcc);
            return NULL;
        }
        if(temp->next==NULL)
        break;

        temp = temp->next;
    }

    temp->next = newAcc;
    
    return newAcc;
}

Account* remove_account(Account** head,char name[],char password[])
{
    Account* temp = *head; Account* prev = temp;
    while(temp->next!=NULL)
    {
        prev = temp;
        if(!strcmp(temp->name,name))
        {
            if(!strcmp(temp->password,password))
            {
                if(prev==NULL)
                *head = temp->next;
                else
                prev->next = temp->next;

                free(temp);
                return *head;
            }
            else
            {
                return NULL;
            }
        }
        prev = temp;
        temp = temp->next;
    }

    return *head;
}


int password_reset(Account** head,char name[],char old[],char new[])
{
    Account* temp = *head;
    while(temp!=NULL)
    {
        if(!strcmp(temp->name,name))
        {
            if(!strcmp(temp->password,old))
            {
                strcpy(temp->password,new);
                return 2;
            }
            else
            {
                return 1;
            }
        }
        temp = temp->next;
    }
    return 0;
}

