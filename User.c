#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"utility.h"
#include"book_management.h"
#include"User_management.h"
#include"librarian.h"
#include"User.h"

int userCLI(){
	char *str=(char*)malloc(100*sizeof(char));
	char *str2=(char*)malloc(100*sizeof(char));
	while(1){
		printf("\nPlease choose an option:\n");
		printf("1)Show the booklist\n");
		
		printf("2)Search book\n");
		printf("3)Borrow book\n");
		printf("4)Return book\n");
		printf("5)quit\n");
		printf("choice:");
		fgets(str,91,stdin);
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
				list_books(bh, -1);
			}
			else if(strcmp(str,"2")==0){
				search_book(bh);
			}
			else if(strcmp(str,"3")==0){
				
			}
			else if(strcmp(str,"4")==0){
				
			}
			else if(strcmp(str,"5")==0){
				return 0;
			}
			else{
				printf("Invalid choice.\n");
			}
		}
	}
}
