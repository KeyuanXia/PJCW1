#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"utility.h"
#include"book_management.h"
#include"search.h"


int find_author(Book *bh){
	char str[91];
	BookList *bl;
	while(1){
		printf("Author:");
		fgets(str,91,stdin);
		clear_n(str);
		fflush(stdin);
		if(strlen(str)==0){
			printf("You did not enter anything yet, please try again.\n");
		}
		else if(strlen(str)>=90){
			printf("Your author name is too long, please try again or enter 'q' to go back.\n");
		}
		else if(strcmp(str, "q")==0){
			return -1;
		}
		else{
			bl=find_book_by_author(bh, str);
			if(bl->length!=0){
				list_books(bl->list, bl->length);
				return 1;
			}
			else{
				return 0;
			}
			break;
		}
	}
}

int find_title(Book *bh){
	char str[30];
	BookList *bl;
	while(1){
		printf("booktitle:");
		fgets(str,30,stdin);
		clear_n(str);
		fflush(stdin);
		if(strlen(str)==0){
			printf("\nYou did not enter anything yet, please try again.\n");
		}
		else if(strlen(str)>=24){
			printf("\nYour book name is too long, please try again or enter 'q' to go back.\n");
		}
		else if(strcmp(str, "q")==0){
			return -1;
		}
		else{
			
			bl=find_book_by_title(bh, str);
			if(bl->length==0)
				printf("Didn't find book with title: '%s'", str);
			if(bl->length!=0){
				
				list_books(bl->list, bl->length);
				
				return 1;
			}
			else{
				return 0;
			}
			break;
		}
	}
}

int find_year(Book *bh){
	char str[6];
	BookList *bl;
	int year;
	while(1){
		printf("Publish year:");
		fgets(str,6,stdin);
		clear_n(str);
		fflush(stdin);
		if(strcmp(str, "q")==0){
			return -1;
		}
		else if(isnum(str)==0){
			printf("Please just enter integer number, you can try again or enter 'q' to go back.\n");
		}
		else if(strlen(str)==0){
			printf("You did not enter anything yet, please try again or enter 'q' to go back.\n");
		}
		else if(strlen(str)>=5){
			printf("The year is impossible to exist...\n");
		}
		else{
			year = atoi(str);
			bl=find_book_by_year(bh, year);
			
			
			
			if(bl->length!=0){
				list_books(bl->list, bl->length);
				return 1;
			}
			else{
				
				return 0;
			}
			break;
		}
	}
}

int search_book(Book *bh){
	char str[10];
	while(1){
		if(bh->next==NULL){
			return -1;
		}
		printf("\nPlease choose an option:\n");
		printf("1)Search book by title\n");
		printf("2)Search book by author\n");
		printf("3)Search book by year\n");
		printf("4)quit\n");
		printf("choice:");
		fgets(str,9,stdin);
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
				find_title(bh);
			}
			else if(strcmp(str,"2")==0){
				find_author(bh);
			}
			else if(strcmp(str,"3")==0){
				find_year(bh);
			}
			else if(strcmp(str,"4")==0){
				return 0;
			}
			else{
				printf("Invalid choice.\n");
			}
		}
	}
}
