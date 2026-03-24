#include "functions.h"

int main()
{
    song* libsongs_head = load_songs_lib(); // Loading the songs from the Library into a Linked list.
    Account* accounts_head = load_accounts(); // Loading all the accounts into a Linked list.
    Account* current_account = NULL;
    playlist* playlist_head = NULL;
    playlist* current_song = NULL;
    char command[100];

    printf("\t\t\t\t\t\t\t\t\t ||UNPLUGGED||\n");

    while(1)
    {
        accounts_CLI();
        input(command);

        if (check(command)) // Taking the input from the user.
        {
            unload_accounts(&accounts_head);
            free_songs_of_lib(libsongs_head);
            free_accounts(accounts_head);
            return 0;
        }

        if(!strcmp(command,"Create a New Account")) // Creating New Account
        {
            int k = new_account(&current_account,&accounts_head);
            if(k==0)
            continue;
            else if(k==1)
            break;
        }
        else if(!strcmp(command,"Log in to an Existing Account")) // Logging in to an existing Account
        {
            current_account = open_account(current_account,&accounts_head);
            if(current_account==NULL)
            continue;
            else
            break;
        }
        else
        printf("Invalid Command. Please Try Again\n"); // If Invalid Command is Entered.
    }

    show_library(&libsongs_head);

    while(1)
    {
        main_CLI();
        input(command);
        command_entry(command,&current_account);
        if(check(command))
        {
            unload_accounts(&accounts_head);
            free_songs_of_lib(libsongs_head);
            free_accounts(accounts_head);
            return 0;
        }

        if(!strcmp(command,"Show Library")) 
        {
            show_library(&libsongs_head);
            continue;
        }
        else if(!strcmp(command,"Show All Albums"))
        {
            if(current_account->albumCount==0)
            printf("No Albums.\n");
            else
            {
                show_albums(&current_account);
            }
            continue;
        }
        else if(!strcmp(command,"Open Album"))
        {
            if(current_account->albumCount==0)
            printf("No Albums currently.\n");
            else 
            open_album(&current_account);

            continue;
        }
        else if(!strcmp(command,"Remove an Album"))
        {
            if(current_account->albumCount==0)
            {
                printf("No Albums in your Account.\n");
                continue;
            }
            printf("Choose Which Album to Remove:-\n");

            int k = remove_album(&(current_account->album),&current_account);
            if(k==0)
            printf("Album Not Found\n");
            else if(k==1)
            printf("Album Deletion Sucussfull\n");

            continue;
        }
        else if(!strcmp(command,"Create a New Album"))
        {
            int k = new_album(&current_account);
            if(k==0)
            printf("Same name Album already exists. Please try again\n");
            else if(k==1)
            printf("Album creation successfull!\n");

            continue;
        }
        else if(!strcmp(command,"Add a Song to an Album"))
        {
            int k = add_song_to_album(&current_account,&libsongs_head);
            if(k==3)
            printf("Song Addition Sucessfull.\n");
            else if(k==2)
            printf("Song Already exists.\n");
            else if(k==1)
            printf("Song Addtion Unsuccessfull. Reason = Album Not Found.\n");
            else if(k==0)
            printf("Song Additon Unsuccessfull. Reason = Song Not Found.\n");

            continue;
        }
        else if(!strcmp(command,"Remove a Song from an Album"))
        {
            int k = remove_song_from_album(&current_account);
            if(k==2)
            printf("Song Deletion Successfull.\n");
            else if(k==1)
            printf("Song Deletion Unsuccessfull. Reason = Song not in the Album.\n");
            else if(k==0)
            printf("Song Deletion Unsuccessfull. Reason = Album not fount.\n");
            continue;
        }
        else if(!strcmp(command,"Add a Song to the Playlist"))
        {
            show_library(&libsongs_head);
            char name[100]; printf("Enter Song Name\n"); input(name);command_entry(name,&current_account);
            int k = add_song_to_playlist(name,&libsongs_head,&playlist_head);
            if(k==0)
            printf("Song Addition Unsucessfull. Reason = Song Not Found.\n");
            else if(k==1)
            printf("Song Already exists in the playlist.\n");
            else if(k==2)
            printf("Song Addition Sucessfull.\n");

            continue;
        }
        else if(!strcmp(command,"Remove a Song from the Playlist"))
        {
            show_playlist(&playlist_head);
            char name[100]; printf("Enter Song Name\n"); input(name);command_entry(name,&current_account);
            int k = remove_song_from_playlist(name,&playlist_head);
            if(k==0)
            printf("Song Deletion Unsucessfull. Reason = Song Not Found\n");
            else if(k==1)
            printf("Song Deletion Sucessfull.\n");

            continue;
        }
        else if(!strcmp(command,"Play a Song"))
        {
            current_song = play_song(&playlist_head,&libsongs_head,&current_account);
            if(current_song==NULL)
            printf("Song Not Found\n");
            
            continue;
        }
        else if(!strcmp(command,"Play Previous Song"))
        {
            if(playlist_head==NULL)
            printf("Action Unsucessfull.\n");
            else
            current_song = previous_song(&current_song);

            continue;
        }
        else if(!strcmp(command,"Play Next Song"))
        {
            if(playlist_head==NULL)
            printf("Action Unsucessfull. Reason = Playlist is Empty.\n");
            else
            current_song = next_song(&current_song);

            continue;
        }
        else if(!strcmp(command,"Play an Album"))
        {
            if(current_account->albumCount==0)
            printf("No Albums in the Account to Play\n");
            else
            {
                playlist* temp = play_album(&current_account,&libsongs_head,&playlist_head);

                if(temp==NULL)
                printf("No such Album");
                else
                current_song = temp;
            }
            
            continue;
        }
        else if(!strcmp(command,"Clear Playlist"))
        {
            free_playlist(&playlist_head);
            
            continue;
        }
        else if(!strcmp(command,"Show Playlist"))
        {
            if(playlist_head==NULL)
            printf("No Songs in the Playlist\n");
            else
            show_playlist(&playlist_head);

            continue;
        }
        else if(!strcmp(command,"Change Password"))
        {
            char name[100]; printf("Enter Username\n"); input(name);command_entry(name,&current_account);
            char old_password[100]; printf("Enter Old Password\n"); input(old_password);command_entry(name,&current_account);
            char new_password[100]; printf("Enter New Password\n"); input(new_password);command_entry(name,&current_account);
            int k = password_reset(&accounts_head,name,old_password,new_password);
            if(k==0)
            printf("Account Not Found\n");
            else if(k==1)
            printf("Access Denied. Password Wrong\n");
            else if(k==2)
            printf("Access Granted. Password changed\n");

            continue;
        }
        else
        {
            printf("Invalid Argument\n\n");
        }
    }
    return 0;
}