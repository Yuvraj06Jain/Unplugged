#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Album
{
    char name[100];
    int count;
    int album_index;
    struct Album* next;
    struct song* songs;
}album;

typedef struct Commands
{
    char command[100];
    struct Commands* next;
}commands;

typedef struct Account
{
    char name[100];
    char password[100];
    int albumCount;
    int commands_count;
    album* album;
    commands* commands;
    struct Account* next;
}Account;

typedef struct playlist
{
    struct song* songs;
    struct playlist* next;
    struct playlist* prev;
}playlist;

typedef struct song
{
    char song_name[100];
    char singers[100];
    int song_index;
    int time;
    struct song* next;
}song;

char* input(char command[100]);
bool check(char command[]);
void accounts_CLI();
int new_account(Account** current_account,Account** accounts_head);
Account* open_account(Account* current_account,Account** accounts_head);
Account* find_account(Account** head,char name[],char password[]);
void main_CLI();
void show_library(song** head);
void show_albums(Account** curr);
void open_album(Account** curr);
int remove_album(album** album_head,Account** curr);
int new_album(Account** curr);
int add_song_to_album(Account** curr, song** head);
int remove_song_from_album(Account** curr);
playlist* play_song(playlist** head,song** head_song,Account** curr);
playlist* previous_song(playlist** current_song);
playlist* next_song(playlist** current_song);
playlist* play_album(Account** curr, song** head_song,playlist** playlist_head);
void show_playlist(playlist** playlist_head);
void free_playlist(playlist** playlist_head);
void command_entry(char command[],Account** curr);
Account* add_account(Account** head,char name[],char password[]);
Account* remove_account(Account** head,char name[],char password[]);
int password_reset(Account** head,char name[],char old[],char new[]);
song* find_song(char name[],song** head);
int add_song_to_playlist(char name[],song** head,playlist** head_playlist);
int remove_song_from_playlist(char name[],playlist** head_playlist);
song* load_songs_lib();
Account* load_accounts();
void unload_accounts(Account** head);
void free_songs_of_lib(song* head);
void free_accounts(Account* head);
