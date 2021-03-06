#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"utility.h"
#include"book_management.h"
#include"User_management.h"
#include"borrow_management.h"
#include"search.h"

#include"User.h"


int initial_user_borrow(User *user, BookList *ubh, char *username, char *bookfile){
	ubh->list->next=NULL;
	ubh->list->id=0;
	char temp[50];
	char temp2[10];
	strcpy(temp,"./Userdata/");
	strcpy(temp2,"/");
	strcat(temp,bookfile);
	strcat(temp,temp2);
    strcpy(temp2,".txt");
    strcat(temp,username);
    strcat(temp,temp2);
	
	FILE *fr=fopen(temp,"r");
	ubh->length=load_books(ubh->list, fr, bookfile);
	switch(ubh->length){
		case -1:printf("\n!!!Didn't find the user's borrow history!!!\n\n");return -1;
		case 0:printf("\n!!!You didn't borrow any book'!!!\n");return 0;
		default:break;
	}
	fclose(fr);
	printf("\n***User borrowed books insert sucessfully!***\n");
	return 1;
}

int _borrow_book(Book *bh, BookList *ubh, Book *abh, char *username, char *bookfile){
	Book choosen_book;
	char *str=(char*)malloc(100*sizeof(char));
	while(1){
		if(list_books(abh, -1)==-1){
                        printf(("\n!!!No book can be borrowed!!!\n"));
                        return -1;
                }
		printf("\nPlease choose an book ID:");
		fgets(str,91,stdin);
		clear_n(str);
		fflush(stdin);
		if(strcmp(str, "q")==0){
			return -1;
		}
		else if(isnum(str)==0){
			printf("_____Please just enter integer number, you can try again or enter 'q' to go back._____\n");
		}
		else if(strlen(str)==0){
			printf("_____You did not enter anything yet, please try again or enter 'q' to go back._____\n");
		}
		else{
			choosen_book.id = atoi(str);
			if(choosen_book.id<=0){
				printf("\n!!!Invalid number!!!\n");
				printf("!!!ID must be positive.!!!\n\n");
			}
			else if(find_book_by_id(ubh->list, choosen_book.id)==1){
				printf("_____You have already borrowed this book yet._____\n");
			}
			else if(find_book_by_id(bh, choosen_book.id)==2){
				printf("_____This book does not left any more.._____\n");
			}
			else if(add_borrow_book(bh, choosen_book, ubh)==-1){
				printf("_____Didn't find the book, please check the ID_____\n");
			}
			break;
		}
	}
    store_user_borrow(ubh, username, bookfile);
}

int borrow_book(User *user, Book *bh, BookList *ubh, char *username, char *bookfile){
	
	char *str=(char*)malloc(100*sizeof(char));
	Book *abh=(Book *)malloc(sizeof(Book));
	while(1){
        printf("\n***********************************************************************\n");
		printf("\nPlease choose an option\n");
		printf("1)Show the available booklist\n");
		printf("2)Search book\n");
		printf("3)Borrow book(Just accept ID)\n");
		printf("4)quit\n");
        printf("***********************************************************************\n");
		printf("choice:");
		fgets(str,91,stdin);
		clear_n(str);
		fflush(stdin);
		if(strlen(str)==0){
			printf("\n_____You has not choose yet, please try again._____\n");
		}
		else if(strlen(str)>1){
			printf("\n_____Your choice is too long, please try again._____\n");
		}
		else{
			choose_available_book(abh, bh, ubh);
			if(strcmp(str,"1")==0){
				if(list_books(abh, -1)==-1)
					printf("\n\n***No book can be borrowed.***\n\n");
			}
			else if(strcmp(str,"2")==0){
                                if(search_book(bh)==-1)
                                        printf("\n\n!!!The library is empty.!!!\n\n");
			}
			else if(strcmp(str,"3")==0){
				_borrow_book(bh, ubh, abh, username, bookfile);
			}
			else if(strcmp(str,"4")==0){
				return 0;
			}
			else{
				printf("!!!Invalid choice.!!!\n");
			}
			FILE *fr=fopen(bookfile, "w");
			store_books(bh, fr);
			fclose(fr);
		}
		
	}
}



int _return_book(Book *bh, BookList *ubh, char *filename){
	Book choosen_book;
	char *temp=(char *)malloc(100*sizeof(char));
	char *temp_2=(char *)malloc(100*sizeof(char));
	char *str=(char*)malloc(100*sizeof(char));
	while(1){
		list_books(ubh->list, -1);
		printf("\nPlease choose an book ID:");
		fgets(str,91,stdin);
		clear_n(str);
		fflush(stdin);
		if(strcmp(str, "q")==0){
			return -1;
		}
		else if(isnum(str)==0){
			printf("\n_____Please just enter integer number, you can try again or enter 'q' to go back._____\n");
		}
		else if(strlen(str)==0){
			printf("_____You did not enter anything yet, please try again or enter 'q' to go back._____\n");
		}
		else{
			choosen_book.id = atoi(str);
			if(choosen_book.id<=0){
				printf("\n!!!Invalid number!!!\n");
				printf("!!!ID must be positive.!!!\n\n");
			}
			if(remove_chosen_book(bh, choosen_book, ubh)==-1){
				printf("!!!Didn't find the book, please check the ID!!!\n");
			}
			break;
		}
	}
	strcpy(temp,"./Userdata/");
	strcpy(temp_2,".txt");
	strcat(temp,filename);
	strcat(temp,temp_2);
	FILE *fr=fopen(temp, "w");
	store_books(ubh->list, fr);
	fclose(fr);
}

int return_book(User *user, Book *bh, BookList *ubh, char *filename, char *bookfile){
	char *str=(char*)malloc(100*sizeof(char));
	while(1){
		if(ubh->list->next==NULL){
			printf("\n\n!!!You have not borrow any book yet.!!!\n\n");
			return 0;
		}
        printf("\n***********************************************************************\n");
		printf("Please choose an option\n");
		printf("1)Show the borrowed booklist\n");
		printf("2)Search book\n");
		printf("3)return book(Just accept ID)\n");
		printf("4)quit\n");
        printf("***********************************************************************\n");
		printf("choice:");
		fgets(str,91,stdin);
		clear_n(str);
		fflush(stdin);
		if(strlen(str)==0){
			printf("_____You has not choose yet, please try again._____\n");
		}
		else if(strlen(str)>1){
			printf("_____Your choice is too long, please try again._____\n");
		}
		else{
			if(strcmp(str,"1")==0){
				list_books(ubh->list, -1);
			}
			else if(strcmp(str,"2")==0){
				search_book(ubh->list);
			}
			else if(strcmp(str,"3")==0){
				_return_book(bh, ubh, filename);
			}
			else if(strcmp(str,"4")==0){
				return 0;
			}
			else{
				printf("\n!!!Invalid choice.!!!\n");
			}
		}
		FILE *fr=fopen(bookfile, "w");
		store_books(bh, fr);
		fclose(fr);
	}
}

int userCLI(User *user, Book *bh, char *username, char *bookfile){
	char str[3];
	BookList *ubh=(BookList *)malloc(sizeof(BookList));
	ubh->list=(Book *)malloc(sizeof(Book));
	initial_user_borrow(user, ubh, username, bookfile);
	while(1){
        printf("\n***********************************************************************\n");
		printf("\nPlease choose an option:\n");
		printf("1)Show the booklist\n");
		printf("2)Show the borrowed book\n");
		printf("3)Search book in library\n");
		printf("4)Search book in your borrowed\n");
		printf("5)Borrow book\n");
		printf("6)Return book\n");
		printf("7)quit\n");
        printf("***********************************************************************\n");
		printf("choice:");
		fgets(str,3,stdin);
		clear_n(str);
		fflush(stdin);
		if(strlen(str)==0){
			printf("_____You has not choose yet, please try again._____\n");
		}
		else if(strlen(str)>1){
			printf("_____Your choice is too long, please try again._____\n");
		}
		else{
			if(strcmp(str,"1")==0){
				if(list_books(bh, -1)){
                    printf("\n!!!The library has not book yet, please let librarian add book first!!!\n\n");
                }
			}
			else if(strcmp(str,"2")==0){
				if(list_books(ubh->list, -1)==-1)
					printf("\n!!!You have not borrow any book yet.!!!\n\n");
			}
			else if(strcmp(str,"3")==0){
				if(search_book(bh)==-1)
					printf("\n\n!!!The library is empty.!!!\n\n");
			}
			else if(strcmp(str,"4")==0){
				if(search_book(ubh->list)==-1)
					printf("\n\n!!!You have not borrowed any book yet.!!!\n\n");
			}
			else if(strcmp(str,"5")==0){
				borrow_book(user, bh, ubh, username, bookfile);
			}
			else if(strcmp(str,"6")==0){
				return_book(user, bh, ubh, username, bookfile);
			}
			else if(strcmp(str,"7")==0){
				
				return 0;
			}
			else{
				printf("\n!!!Invalid choice.!!!\n");
			}
		}
	}
}
