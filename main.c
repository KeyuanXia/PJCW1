#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"book_management.h"
#include"User_management.h" 
#include"librarian.h"
#include"User.h"
#include"utility.h"

int main(int argc, char **argv){
	int check;
	User *user;
	char *filename=(char *)malloc(100*sizeof(char));
	char *str=(char *)malloc(100*sizeof(char));
	User *uh=(User *)malloc(sizeof(User));
	Book *bh=(Book *)malloc(sizeof(Book));
	bh->next=NULL;
	bh->id=0;
	if(argc!=2){
		printf("\nexpect one book list name entered.\n\nProgram end.\n");
		return 0;
	}
    else if(strlen(argv[1])>=100){
        printf("\nThe book list name is too long, please choose one shorter than 99.\n\nProgram end.\n");
    }
	strcpy(filename, argv[1]);
	while(1){

		check=initial_booklist(bh, filename);
		
		while(1){
			if(check==-1){
				printf("Do you wanna create a new book list?\n");
				printf("1)Create a new book list with entered name: %s\n", filename);
				printf("2)Quit\n");
				printf("choice:");
				fgets(str,10,stdin);
				clear_n(str);
				fflush(stdin);
				if(strlen(str)==0){
					printf("You has not choose yet, please try again.\n");
				}
				else if(strlen(str)>1){
					printf("Your choice is too long, please try again.\n");
				}
				else{
					if(strcmp(str,"1")==0){
						create_booklist_file(filename);
						break;
					}
					else if(strcmp(str,"2")==0){
						return 0;
					}
					else{
						printf("Invalid choice.\n");
					}
				}
			}
			else{
				break;
			}
		}
		user=login_or_register(uh,filename);
		if(user->type==1){
			check=librarianCLI(user, bh, uh, filename);
		}
		else if(user->type==2){
			
			check=userCLI(user, bh, user->username, filename);
		}
		else if(user->type==-1){
			printf("\nQuit the library system.\n");
			return 0;
		}
		if(check==-1){
			return 0;
		}
	}
}
