#include "functions.h"

song* load_songs_lib()
{
    printf("Loading Library....\n");
    FILE* fptr;
    fptr = fopen("Library.txt","r"); char line[300];
    song* buffer = (song*)malloc(sizeof(song)); song* temp = buffer;
    while(fgets(line,300,fptr))
    {
        song* newSong = (song*)malloc(sizeof(song));

        
        sscanf(line,"Song Name = %[^.]. | Artists = %[^.]. | Duration(in seconds) = %d |",newSong->song_name,newSong->singers,&newSong->time);
        
        temp->next = newSong;
        temp = newSong;
        temp->next = NULL;
    }
    printf("Loading successfull!\n");
    return buffer->next;
}

Account* load_accounts()
{
    printf("Loading All Accounts....\n");
    FILE* fp;
    fp = fopen("Accounts.txt","r");
    char line[300];

    Account* buffer_acc = (Account*)malloc(sizeof(Account));
    Account* temp_acc = buffer_acc;
    buffer_acc->next = NULL;

    while(fgets(line,300,fp))
    {   
        Account* newAcc = (Account*)malloc(sizeof(Account));
        newAcc->albumCount=0;
        newAcc->album = NULL;
        newAcc->commands = NULL;
        newAcc->commands_count = 0;
        newAcc->next = NULL;
    
        sscanf(line,"Name = %[^.]. | Password = %[^.]. | Albums = %d",newAcc->name,newAcc->password,&newAcc->albumCount);

        if(newAcc->albumCount==0)
        {
            newAcc->album = NULL;
        }
        else
        {
            album* buffer_album = (album*)malloc(sizeof(album));
            album* temp_album = buffer_album;
            buffer_album->next = NULL;
            for(int i=0;i<newAcc->albumCount;i++)
            {
                album* newAlbum = (album*)malloc(sizeof(album));

                fgets(line,300,fp); 
                sscanf(line,"%[^[][%d]",newAlbum->name,&newAlbum->count);

                song* buffer = (song*)malloc(sizeof(song));
                song* temp_song = buffer;
                buffer->next = NULL;

                for(int j=0;j<newAlbum->count;j++)
                {
                    song* newSong = (song*)malloc(sizeof(song));
                    fgets(line,300,fp);
                    sscanf(line,"Song Name = %[^.]. | Artists = %[^.]. | Duration(in seconds) = %d |",newSong->song_name,newSong->singers,&newSong->time);
                    temp_song->next = newSong;
                    temp_song = newSong;
                    newSong->next = NULL;
                }
                newAlbum->songs = buffer->next;
                free(buffer);

                temp_album->next = newAlbum;
                temp_album = newAlbum;
                newAlbum->next = NULL;
            }
            newAcc->album = buffer_album->next;
            free(buffer_album);
        }

        commands* buffer_command = (commands*)malloc(sizeof(commands));
        commands* temp_comm = buffer_command;
        buffer_command->next = NULL;

        fgets(line,300,fp);
        sscanf(line,"Commands[%d]",&newAcc->commands_count);

        for(int i=0;i<newAcc->commands_count;i++)
        {
            commands* newcommand = (commands*)malloc(sizeof(commands));
            fgets(line,300,fp);line[strlen(line)-1] = '\0';
            strcpy(newcommand->command,line);
            temp_comm->next = newcommand;
            temp_comm = newcommand;
            newcommand->next=NULL;
        }
        newAcc->commands = buffer_command->next;
        free(buffer_command);
        fgets(line,300,fp);

        temp_acc->next = newAcc;
        temp_acc = newAcc;  
        newAcc->next = NULL; 
    }

    Account* t = buffer_acc->next;
    Account* temp = buffer_acc->next;
    while(temp!=NULL)
    {
        // printf("HELLO\n");
        temp = temp->next;
    }
    free(buffer_acc);
    fclose(fp);
    printf("Loading Successful!\n");
    return t;
}

void unload_accounts(Account** head)
{
    printf("\nUnLoading All Accounts.\n");
    if(*head==NULL)
    {
        return;
    }

    FILE* fp;
    fp = fopen("Accounts.txt","w");
    Account* temp =  *head;
    
    while(temp!=NULL)
    {
        // printf("HELLO\n");
        fprintf(fp,"Name = %s. | Password = %s. | Albums = %d\n",temp->name,temp->password,temp->albumCount);

        album* temp_album = temp->album;
        if(temp_album!=NULL)
        {
            for(int i=0;i<temp->albumCount;i++)
            {
                fprintf(fp,"%s[%d]\n",temp_album->name,temp_album->count);
                song* temp_song = temp_album->songs;
                for(int j=0;j<temp_album->count;j++)
                {
                    fprintf(fp,"Song Name = %s. | Artists = %s. | Duration(in seconds) = %d |\n",temp_song->song_name,temp_song->singers,temp_song->time);
                    temp_song = temp_song->next;
                }
                temp_album = temp_album->next;
            }
        }
        
        fprintf(fp,"Commands[%d]\n",temp->commands_count);
        commands* temp_com = temp->commands;
        if(temp_com!=NULL)
        {
            for(int i=0;i<temp->commands_count;i++)
            {
                fprintf(fp,"%s\n",temp_com->command);
                temp_com = temp_com->next;
            }
        }
        fputs("------------\n",fp);
        temp = temp->next;
    }
    printf("Unloading Successfull\n");
    fclose(fp);
}

void free_songs_of_lib(song* head)
{
    song* temp = head;
    while(head!=NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}   

void free_accounts(Account* head)
{
    Account* temp_acc = head;
    while(head!=NULL)
    {
        album* head_album = temp_acc->album;
        album* temp_album = head_album;
        for(int i=0;i<temp_acc->albumCount;i++)
        {
            song* head_song = temp_album->songs;
            song* temp_song = head_song;
            for(int j=0;j<temp_album->count;j++)
            {
                temp_song = head_song;
                head_song = head_song->next;
                free(temp_song);
            }

            temp_album = head_album;
            head_album = head_album->next;
            free(temp_album);
        }

        commands* head_com = temp_acc->commands;
        commands* temp_com = head_com;

        for(int i=0;i<temp_acc->commands_count;i++)
        {
            temp_com = head_com;
            head_com = head_com->next;
            free(temp_com);
        }

        temp_acc = head;
        head = head->next;
        free(temp_acc);
    }

    return;
}