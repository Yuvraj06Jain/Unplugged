Name = Yuvraj Jain
Roll No. = 2025101140
Section = B
Group = G7

Welcome to C Unplugged, A music playing platform where Users can create individual accounts and albums and play songs.

For running starting the application, the user has to follow the following steps:-
1) Unzip the file and store it on your PC.
2) Copy the newly created file's path.
3) Open the terminal the type the following command
	cd <file path>
4) On Successful execution of the command, Type the following next command on the terminal
	gcc CLI.c loadUnload.c CLI_func.c accounts.c albums.c playlist.c -o UNPLUGGED
5) On Successful execution of the command, you will see a new .exe file created inside the folder.
6) Double click the UNPLUGGED.exe file and will program will start running.

Note:-
1) Before the user starts giving commands, a command menu will be shown, the user has to type the exact same command for that particular function to work. Failure to do so will show invalid command message. 

2) To EXIT the program, the user can type the EXIT command but it would work only if the menu that appeared on the screen had that command.

3) To check the commands given by the user, open the Accounts.txt file in the folder and the details of each user will be shown.
4) To update the Library, open the Library.txt file in the folder and start writing the details of the song in the next line and strictly in the given format. Failure to write in the given              format will cause the program to crash or work unexpectedly

	Format = 	Song Name = <Song_name> | Artists = <Artists name separated by commas> | Duration(in seconds) = <Duration of song in seconds> |

5) We would recommend not to change anything in the accounts.txt and library.txt file as it can make the program work unexpectedly.
