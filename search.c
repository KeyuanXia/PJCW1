#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"utility.h"
#include"book_management.h"
#include"search.h"


int find_author(Book *bh){
	char *str=(char*)malloc(100*sizeof(char));
	BookList *bl;
	while(1){
		printf("Author:");
		fgets(str,91,stdin);
		clear_n(str);
		fflush(stdin);
		if(strlen(str)==0){
			printf("\n_____You did not enter anything yet, please try again._____\n");
		}
		else if(strlen(str)>=90){
			printf("\n_____Your author name is too long, please try again or enter 'q' to go back._____\n");
		}
		else if(strcmp(str, "q")==0){
			return -1;
		}
		else{
			bl=find_book_by_author(bh, str);
			if(bl->length!=0){
				list_books(bl->list, bl->length);
                free(str);
				return 1;
			}
			else{
				return 0;
			}
		}
	}
}

int find_title(Book *bh){

	char *str=(char *)malloc(30*sizeof(char));
	BookList *bl;
	while(1){
		printf("book title:");

		fgets(str,30,stdin);

		clear_n(str);
		fflush(stdin);

		if(strlen(str)==0){
			printf("\n_____You did not enter anything yet, please try again._____\n");
		}
		else if(strlen(str)>=24){
			printf("\n_____Your book name is too long, please try again or enter 'q' to go back._____\n");
		}
		else if(strcmp(str, "q")==0){
			return -1;
		}
		else{

			bl=find_book_by_title(bh, str);

			if(bl->length==0)
				printf("\n>>>>>Didn't find book with title: '%s'\n", str);
			if(bl->length!=0){
				
				list_books(bl->list, bl->length);
                free(str);
				return 1;
			}
			else{
                free(str);
				return 0;
			}
		}
	}
}

int find_year(Book *bh){
	char str[6];
	BookList *bl;
    Book *q;
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
			printf("\n_____Please just enter integer number, you can try again or enter 'q' to go back._____\n");
		}
		else if(strlen(str)==0){
			printf("\n_____You did not enter anything yet, please try again or enter 'q' to go back._____\n");
		}
		else if(strlen(str)>=5){
			printf("\nThe year is impossible to exist...\n");
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
		}
	}
}

int search_book(Book *bh){
	char str[10];
	while(1){
		if(bh->next==NULL){
			return -1;
		}
        printf("\n***********************************************************************\n");
		printf("Please choose an option:\n");
		printf("1)Search book by title\n");
		printf("2)Search book by author\n");
		printf("3)Search book by year\n");
		printf("4)quit\n");
        printf("***********************************************************************\n");
		printf("choice:");
		fgets(str,9,stdin);
		clear_n(str);
		fflush(stdin);
        printf("\n");
		if(strlen(str)==0){
			printf("\n_____You has not choose yet, please try again._____\n");
		}
		else if(strlen(str)>1){
			printf("\n_____Your choice is too long, please try again._____\n");
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
				printf("\n!!!Invalid choice.!!!\n");
			}
		}
	}
}
