#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"utility.h"
#include"book_management.h"
#include"User_management.h"
#include"search.h"
#include"librarian.h"

int booklist_add(Book *bh, char *bookfile){
	char *str=(char*)malloc(100*sizeof(char));
	Book new_Book;
	while(1){
		while(1){
			printf("\nbook title:");
			fgets(str,91,stdin);
			clear_n(str);
			fflush(stdin);
			if(strlen(str)==0){
				printf("You did not enter anything yet, please try again.\n");
			}
			else if(strlen(str)>=24){
				printf("Your book name is too long, please try again or enter 'q' to go back.\n");
			}
			else if(strcmp(str, "q")==0){
				return -1;
			}
			else{
				if(find_book_by_title(bh, str)->length>=1){
					printf("\nThis book is already exist, please change one or enter 'q' to go back.\n");
				}
				else{
					new_Book.title=strdpp(str);
					break;
				}
			}
		}
		while(1){
			printf("Copies:");
			fgets(str,91,stdin);
			clear_n(str);
			fflush(stdin);
			if(strcmp(str, "q")==0){
				return -1;
			}
			else if(isnum(str)==0){
				printf("_____Please just enter integer number._____\n");
			}
			else if(strlen(str)==0){
				printf("_____You did not enter anything yet, please try again or enter 'q' to go back._____\n");
			}
			else if(strlen(str)>=8){
				printf("_____The copies are too much._____\n");
			}
			else{
				new_Book.copies=atoi(str);
				new_Book.totalcopies=new_Book.copies;
				break;
			}
		}
		while(1){
			printf("Publish year:");
			fgets(str,91,stdin);
			clear_n(str);
			fflush(stdin);
			if(strcmp(str, "q")==0){
				return -1;
			}
			else if(isnum(str)==0){
				printf("_____Please just enter integer number._____\n");
			}
			else if(strlen(str)==0){
				printf("_____You did not enter anything yet, please try again or enter 'q' to go back._____\n");
			}
			else if(strlen(str)>=5){
				printf("The year is impossible to exist...\n");
			}
			else{
				new_Book.year=atoi(str);
				
				break;
			}
		}
		while(1){
			printf("Authors(with comma separated):");
			fgets(str,91,stdin);
			clear_n(str);
			fflush(stdin);
			if(strlen(str)==0){
				printf("\n_____You did not enter anything yet, please try again._____\n");
			}
			else if(strlen(str)>=90){
				printf("\n_____Your author list is too long, please try again or enter 'q' to go back._____\n");
			}
			else if(strcmp(str, "q")==0){
				return -1;
			}
			else{
				new_Book.authors=strdpp(str);
                new_Book.bookfile=strdpp(bookfile);
				add_book(bh, new_Book);
				break;
			}
		}
		while(1){
            printf("\n***********************************************************************\n");
			printf("1) Continue to add book\n");
			printf("2) Show the book list\n");
			printf("3) Quit\n");
            printf("***********************************************************************\n");
			printf("choice:");
			fgets(str,10,stdin);
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
					break;
				}
				else if(strcmp(str,"2")==0){
					list_books(bh, -1);
				}
				else if(strcmp(str,"3")==0){	///Quit
					printf("\n>>>>>book file=%s\n",bookfile);
					FILE *fr=fopen(bookfile, "w");
					store_books(bh, fr);
					fclose(fr);
					return -1;
				}
				else{
					printf("\n!!!Invalid choose.!!!\n");
				}
			}
		}
	}
}

int create_booklist_file(char *fileName){
    FILE *fileP;
    fileP = fopen(fileName, "r");
    if (fileP == NULL){
        fileP = fopen(fileName, "w");
    }
    fclose(fileP);
}

int book_remove(Book *bh, char *filename){
	Book chosen_book;
	char *str=(char*)malloc(100*sizeof(char));
	while(1){
		if(bh->next==NULL){
			printf("\n\n!!!The booklist is empty now, please add books at first!!!\n\n");
		}
		list_books(bh, -1);
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
			printf("\n_____You did not enter anything yet, please try again or enter 'q' to go back._____\n");
		}
		else if(strlen(str)>=5){
			printf("The year is impossible to exist...\n");
			printf("_____You can enter 'q' to go back._____\n");
		}
		else{
			chosen_book.id = atoi(str);
			if(chosen_book.id<=0){
				printf("\n!!!Invalid number!!!\n");
				printf("\n!!!ID must be positive.!!!\n");
			}
			if(remove_book(bh, chosen_book)==-1){
				printf("\n!!!Didn't find the book, please check the ID!!!\n");
			}
            else if(remove_book(bh, chosen_book)==-2){
                printf("\n!!!This book has been borrowed by user, please don't remove it.!!!\n");
            }
			
			break;
		}
		
		
	}
	FILE *fr=fopen(filename, "w");
	store_books(bh, fr);
	fclose(fr);
}

int librarianCLI(User *user, Book *bh, User *uh, char *filename){
	char *str=(char*)malloc(100*sizeof(char));
	char *str2=(char*)malloc(100*sizeof(char));
	while(1){
        printf("\n***********************************************************************\n");
		printf("Please choose an option:\n");
		printf("1)Show the book list\n");
		printf("2)Show the user list\n");
		printf("3)Search book\n");
		printf("4)Add book\n");
		printf("5)Delete book\n");
		printf("6)quit\n");
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
			if(strcmp(str,"1")==0){
				if(list_books(bh, -1)==-1){
					printf("\n\n!!!No book in the library yet, please add some first.!!!\n\n");
				}
			}
			else if(strcmp(str,"2")==0){
				list_users(uh);
			}
			else if(strcmp(str,"3")==0){
				search_book(bh);
			}
			else if(strcmp(str,"4")==0){
				booklist_add(bh, filename);
			}
			else if(strcmp(str,"5")==0){
				book_remove(bh, filename);
				
			}
			else if(strcmp(str,"6")==0){
				return 0;
			}
			else{
				printf("\n!!!Invalid choice.!!!\n");
			}
		}
	}

}


