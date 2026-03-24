#include "functions.h"

song* find_song(char name[],song** head)
{
    song* temp = *head;
    while(temp!=NULL)
    {
        if(!strcmp(temp->song_name,name))
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

int add_song_to_playlist(char name[],song** head,playlist** head_playlist)
{
    song* songk = find_song(name,head);
    if(songk==NULL)
    {
        return 0;
    }
    
    playlist* newSong =  (playlist*)malloc(sizeof(playlist));
    newSong->songs = (song*)malloc(sizeof(song));
    strcpy(newSong->songs->song_name,songk->song_name);
    strcpy(newSong->songs->singers,songk->singers);
    newSong->songs->time = songk->time;
    newSong->songs->next = NULL;

    if(*head_playlist==NULL)
    {
        (*head_playlist) = newSong;
        (*head_playlist)->prev = (*head_playlist);
        (*head_playlist)->next = (*head_playlist);
        return 2;
    }

    playlist* temp = (*head_playlist);
    do
    {
        if(!strcmp(temp->songs->song_name,songk->song_name))
        {
            return 1;    
        }
        
        temp = temp->next;
    }
    while(temp!=*head_playlist);

    playlist* tail = (*head_playlist)->prev;
    tail->next = newSong;
    newSong->prev = tail;
    newSong->next = *head_playlist;
    (*head_playlist)->prev = newSong;
    return 2;
}

int remove_song_from_playlist(char name[],playlist** head_playlist)
{
    if(*head_playlist==NULL)
    {
        return 0;
    }

    playlist* temp = *head_playlist;
    do
    {
        if(!strcmp(temp->songs->song_name,name))
        {
            if(temp->next==temp&&temp->prev==temp)
            {
                free(temp->songs);
                free(temp);
                *head_playlist = NULL;
                return 1;
            }

            if(temp == *head_playlist)
            {
                *head_playlist = temp->next;
            }

            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
            free(temp->songs);
            free(temp);
            return 1;
        }
        temp = temp->next;
    }
    while(temp!=*head_playlist);

    return 0;
}

playlist* play_song(playlist** head,song** head_song,Account** curr)
{
    char name[100]; printf("Enter Song Name\n"); input(name); command_entry(name,curr);
    int k = add_song_to_playlist(name,head_song,head);
    if(k==0)
    return NULL;
    
    playlist* temp = *head;
    while(temp!=NULL)
    {
        if(!strcmp(temp->songs->song_name,name))
        break;

        temp = temp->next;
    }
    
    if(temp==NULL)
    return NULL;

    printf("\nPlaying %s....\n",temp->songs->song_name);
    printf("Artists = %s | Duration(in seconds) = %d |\n",temp->songs->singers,temp->songs->time);

    return temp;   
}

playlist* previous_song(playlist** current_song)
{
    playlist* curr = (*current_song)->prev;
    printf("\nPlaying %s....\n",curr->songs->song_name);
    printf("Artists = %s | Duration(in seconds) = %d |\n",curr->songs->singers,curr->songs->time);

    return curr;
}

playlist* next_song(playlist** current_song)
{
    playlist* curr = (*current_song)->next;
    printf("\nPlaying %s....\n",curr->songs->song_name);
    printf("Artists = %s | Duration(in seconds) = %d |\n",curr->songs->singers,curr->songs->time);

    return curr;
}

void free_playlist(playlist** head_playlist)
{
    if (*head_playlist == NULL)
    {
        return;
    }

    playlist* temp = *head_playlist;
    playlist* nextNode;

    do 
    {
        nextNode = temp->next;
        free(temp->songs);
        free(temp);
        temp = nextNode;
    } 
    while (temp != *head_playlist);

    *head_playlist = NULL;
}
