#include "functions.h"

char* input(char command[100])
{
    char ch; int idx = 0;
    while(1)
    {
        scanf("%c",&ch);
        if(ch=='\n')
        {
            break;
        }
        command[idx++] = ch;
    }

    command[idx] = '\0';
    return command;
}

bool check(char command[])
{
    if(!strcmp(command,"EXIT"))
    {
        printf("THANK YOU!\n");
        return true;
    }

    return false;
}

void accounts_CLI()
{
    printf("1) Create a New Account\n");
    printf("2) Log in to an Existing Account\n");
    printf("3) EXIT\n\n");
}

void main_CLI()
{
    printf("\n");
    printf("1) Show Library\n");
    printf("2) Show All Albums\n");
    printf("3) Open Album\n");
    printf("4) Create a New Album\n");
    printf("5) Remove an Album\n");
    printf("6) Add a Song to an Album\n");
    printf("7) Remove a Song from an Album\n");
    printf("8) Add a Song to the Playlist\n");
    printf("9) Remove a Song from the Playlist\n");
    printf("10) Play a Song\n");
    printf("11) Play Previous Song\n");
    printf("12) Play Next Song\n");
    printf("13) Play an Album\n");
    printf("14) Show Playlist\n");
    printf("15) Clear Playlist\n");
    printf("16) Change Password\n");
    printf("17) EXIT\n\n");
}

void show_library(song** head)
{
    song* temp = *head;
    printf("Library:-\n");
    while(temp!=NULL)
    {
        printf("Song Name = %s | Artists = %s | Duration(in seconds) = %d|\n",temp->song_name,temp->singers,temp->time);
        temp = temp->next;
    }

    printf("\n");
}

void show_playlist(playlist** playlist_head)
{
    printf("Song Name = %s | Artists = %s | Duration(in seconds) = %d |\n",(*playlist_head)->songs->song_name,(*playlist_head)->songs->singers,(*playlist_head)->songs->time);
    playlist* temp = (*playlist_head)->next;
    while(temp!=*playlist_head)
    {
        printf("Song Name = %s | Artists = %s | Duration(in seconds) = %d |\n",temp->songs->song_name,temp->songs->singers,temp->songs->time);
        temp = temp->next;
    }
}

void command_entry(char command[],Account** curr)
{
    commands* temp = (*curr)->commands;
    commands* newcomm = (commands*)malloc(sizeof(commands));
    strcpy(newcomm->command,command);
    if(temp==NULL)
    {
        (*curr)->commands = newcomm;
        newcomm->next = NULL;
    }
    else
    {
        while(temp->next!=NULL)
        {
            temp = temp->next;
        }
        temp->next = newcomm;
    }
    newcomm->next = NULL;

    (*curr)->commands_count++;
}