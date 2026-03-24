#include "functions.h"

void show_albums(Account** curr)
{
    album* temp = (*curr)->album;
    printf("Albums:-\n");
    while(temp!=NULL)
    {
        printf("%s\n",temp->name);
        temp = temp->next;
    }

    printf("\n");
}

void open_album(Account** curr)
{
    printf("\n");
    show_albums(curr);
    char name[100]; printf("Enter name of the Album\n"); input(name); command_entry(name,curr);
    
    album* temp = (*curr)->album;
    
    while(temp!=NULL)
    {
        if(!strcmp(temp->name,name))
        {
            break;
        }

        temp = temp->next;
    }

    if(temp==NULL)
    {
        printf("No such Album.\n");
        return;
    }
    
    if(temp->count==0)
    {
        printf("No Songs in the Album.\n");
        return;
    }

    song* temp1 = temp->songs;
    while(temp1!=NULL)
    {
        printf("Song Name = %s | Artists = %s | Duration(in seconds) = %d|\n",temp1->song_name,temp1->singers,temp1->time);
        temp1 = temp1->next;
    }

    return;
}

int remove_album(album** album_head,Account** curr)
{
    printf("\n");
    show_albums(curr);
    char name[100]; printf("Enter the Name of the Album\n"); input(name); command_entry(name,curr);

    album* temp = *album_head;album* prev1 = NULL;
    while(temp!=NULL)
    {
        if(!strcmp(temp->name,name))
        {
            break;
        }
        prev1 = temp;
        temp = temp->next;
    }

    if(temp==NULL)
    return 0;
    else
    (*curr)->albumCount--;
    
    song* temp1 = temp->songs; song* prev = NULL;
    if(temp1!=NULL)
    {
        while(temp1!=NULL)
        {
            prev = temp1;
            temp1 = temp1->next;
            free(prev);
        }
    }
    if(prev1==NULL)
    {
        (*curr)->album = temp->next;
    }
    else
    {
        prev1->next = temp->next;
    }

    free(temp);

    return 1;
}

int new_album(Account** curr)
{
    char name[100]; printf("Enter Name of the Album\n"); input(name); command_entry(name,curr);
    
    album* newAlbum = (album*)malloc(sizeof(album));
    strcpy(newAlbum->name,name);
    newAlbum->count = 0;
    newAlbum->songs = NULL;
    newAlbum->next = NULL;
    (*curr)->albumCount++;

    if((*curr)->album==NULL)
    {
        (*curr)->album = newAlbum;
        return 1;
    }
    
    album* temp = (*curr)->album; album* prev = NULL;

    while(temp!=NULL)
    {
        if(!strcmp(temp->name,name))
        {
            (*curr)->albumCount--;
            return 0;
        }
        prev = temp;
        temp = temp->next;
    }
        
    prev->next = newAlbum;
    return 1;
}

int add_song_to_album(Account** curr, song** head)
{
    show_albums(curr);
    char album_name[100]; printf("Enter Album Name\n"); input(album_name); command_entry(album_name,curr);

    album* temp1 = (*curr)->album;
    while(temp1!=NULL)
    {
        if(!strcmp(temp1->name,album_name))
        {
            break;
        }
        temp1 = temp1->next;
    }

    if(temp1==NULL)
    return 1;

    char song_name[100]; printf("Enter Song Name\n"); input(song_name); command_entry(song_name,curr);
    
    song* temp = *head;
    while(temp!=NULL)
    {
        if(!strcmp(temp->song_name,song_name))
        {
            break;
        }

        temp = temp->next;
    }

    if(temp==NULL)
    return 0;

    song* newSong = (song*)malloc(sizeof(song));
    strcpy(newSong->song_name,temp->song_name);
    strcpy(newSong->singers,temp->singers);
    newSong->time = temp->time;
    newSong->next = NULL;
    temp1->count++;

    song* temp2 = temp1->songs;
    if(temp2==NULL)
    {
        temp1->songs = newSong; 
        return 3;
    }
    else
    {
        song* prev = NULL;
        while(temp2!=NULL)
        {
            if(!strcmp(temp2->song_name,song_name))
            {
                return 2;
            }
            prev = temp2;
            temp2 = temp2->next;
        }

        prev->next = newSong;
        return 3;
    }
}

int remove_song_from_album(Account** curr)
{
    show_albums(curr);
    char album_name[100]; printf("Select Album\n"); input(album_name); command_entry(album_name,curr);

    album* temp1 = (*curr)->album;
    while(temp1!=NULL)
    {
        if(!strcmp(temp1->name,album_name))
        {
            break;
        }

        temp1 = temp1->next;
    }

    if(temp1==NULL)
    return 0;
    
    if(temp1->count==0)
    {
        printf("No Songs in the Album.\n");
        return 3;
    }

    song* temp5 = temp1->songs;
    while(temp5!=NULL)
    {
        printf("Song Name = %s | Artists = %s | Duration(in seconds) = %d|\n",temp5->song_name,temp5->singers,temp5->time);
        temp5 = temp5->next;
    }
    
    char song_name[100]; printf("Select Song\n"); input(song_name); command_entry(song_name,curr);

    song* temp2 = temp1->songs; song* prev = NULL;
    while(temp2!=NULL)
    {
        if(!strcmp(temp2->song_name,song_name))
        {
            break;
        }
        prev = temp2;
        temp2 = temp2->next;
    }

    if(temp2==NULL)
    return 1;

    temp1->count--;
    if(prev==NULL)
    {
        temp1->songs = temp2->next;
        free(temp2);
    }
    else if(temp2->next==NULL)
    {
        prev->next = NULL;
        free(temp2);
    }
    else
    {
        prev->next = temp2->next;
        free(temp2);
    }

    return 2;
}

playlist* play_album(Account** curr, song** head_song,playlist** playlist_head)
{
    show_albums(curr);
    char name[100]; printf("Enter Album Name.\n"); input(name); command_entry(name,curr);
    
    album* temp = (*curr)->album;
    
    while(temp!=NULL)
    {
        if(!strcmp(temp->name,name))
        {
            break;
        }

        temp = temp->next;
    }

    if(temp==NULL)
    {
        printf("No such Album.\n");
        return NULL;
    }
    
    if(temp->count==0)
    {
        printf("No Songs in the Album.\n");
        return NULL;
    }
    // free_playlist(playlist_head);
    song* temp1 = temp->songs;
    while(temp1!=NULL)
    {
        add_song_to_playlist(temp1->song_name,head_song,playlist_head);
        temp1 = temp1->next;
    }

    printf("\nPlaying %s....\n",temp->songs->song_name);
    printf("Artists = %s | Duration(in seconds) = %d |\n",temp->songs->singers,temp->songs->time);

    playlist* temp3 = *playlist_head;
    do
    {
        if(!strcmp(temp3->songs->song_name,temp->songs->song_name))
        break;

        temp3 = temp3->next;
    }
    while(temp3 != (*playlist_head));

    return temp3;
}