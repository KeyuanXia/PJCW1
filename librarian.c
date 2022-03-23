#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"librarian.h"
#include"book_management.h"
#include"User_management.h"
#include"utility.h"

int librarianCLI(User *user, Book *bh){
	char *str=(char*)malloc(100*sizeof(char));
	
	printf("\nWelcome, %s\n", user->username);
	printf("1)Import booklist\n");
	printf("6)Create a new booklist\n");
	
	
	printf("2)Show the booklist\n");
	printf("3)Show the userlist\n");
	printf("4)Search book\n");
	printf("5)Search user\n");
	
	printf("7)Add book\n");
	printf("8)Delete book\n");
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
			
		}
		else if(strcmp(str,"2")==0){

		}
		else if(strcmp(str,"3")==0){

		}
		else if(strcmp(str,"4")==0){

		}
		else{

		}
	}
}

int Create_booklist(char *fileName){
    FILE *fileP;
    fileP = fopen(fileName, "r");
    if (fileP == NULL){
        fileP = fopen(fileName, "w");
    }
    //¹Ø±ÕÎÄ¼þ
    fclose(fileP);
}
