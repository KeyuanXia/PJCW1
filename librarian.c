#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"utility.h"
#include"book_management.h"
#include"User_management.h"
#include"librarian.h"


int booklist_add(Book *bh, char *bookfile){
	char *str=(char*)malloc(100*sizeof(char));
	Book new_Book;
	while(1){
		while(1){
			printf("booktitle:\n");
			fgets(str,91,stdin);
			clear_n(str);
			fflush(stdin);
			if(strlen(str)==0){
				printf("You did not enter anything yet, please try again.\n");
			}
			else if(strlen(str)>=24){
				printf("Your book name is too long, please try again or enter 'quit' to go back.\n");
			}
			else if(strcmpi(str, "quit")==0){
				return -1;
			}
			else{
				new_Book.title=strdup(str);
				break;
			}
		}
		while(1){
			printf("Copies:\n");
			fgets(str,91,stdin);
			clear_n(str);
			fflush(stdin);
			if(strcmpi(str, "quit")==0){
				return -1;
			}
			else if(isnum(str)==0){
				printf("Please just enter integer number.\n");
			}
			else if(strlen(str)==0){
				printf("You did not enter anything yet, please try again or enter 'quit' to go back.\n");
			}
			else if(strlen(str)>=90){
				printf("The copies are too much.\n");
			}
			else{
				new_Book.copies=atoi(str);
				new_Book.totalcopies=new_Book.copies;
				break;
			}
		}
		while(1){
			printf("Publish year:\n");
			fgets(str,91,stdin);
			clear_n(str);
			fflush(stdin);
			if(strcmpi(str, "quit")==0){
				return -1;
			}
			else if(isnum(str)==0){
				printf("Please just enter integer number.\n");
			}
			else if(strlen(str)==0){
				printf("You did not enter anything yet, please try again or enter 'quit' to go back.\n");
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
			printf("Authors(with comma separated):\n");
			fgets(str,91,stdin);
			clear_n(str);
			fflush(stdin);
			if(strlen(str)==0){
				printf("You did not enter anything yet, please try again.\n");
			}
			else if(strlen(str)>=90){
				printf("Your author list is too long, please try again or enter 'quit' to go back.\n");
			}
			else if(strcmpi(str, "quit")==0){
				return -1;
			}
			else{
				new_Book.authors=strdup(str);
				
				add_book(bh, new_Book);
				break;
			}
		}
		while(1){
			printf("1) Continue to add book\n");
			printf("2) Show the book list\n");
			printf("3) Quit\n");
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
					continue;
				}
				else if(strcmp(str,"2")==0){
					list_books(bh);
				}
				else if(strcmp(str,"3")==0){	///Quit
					printf("\n\nbookfile=%s\n\n",bookfile);
					FILE *fr=fopen(bookfile, "w");
					store_books(bh, fr);
					fclose(fr);
					return -1;
				}
				else{
					printf("\ninvalid choose.\n");
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

BookList *create_booklist(Book *bh, char *str){
	str=(char*)malloc(100*sizeof(char));
	char *str2=(char*)malloc(100*sizeof(char));
	char *str3=(char*)malloc(100*sizeof(char));
	BookList *blh=(BookList *)malloc(sizeof(BookList));
	while(1){
		printf("booklist name:");
		fgets(str,91,stdin);
		clear_n(str);
		fflush(stdin);
		if(strlen(str)==0){
			printf("You has not choose yet, please try again.\n");
		}
		else if(strlen(str)>20){
			printf("Your list name is too long, please try again.\n");
		}
		else if(strcmpi(str, "quit")==0){
			blh->length=-1;
			return blh;
		}
		if(strstr(".",str)){
			printf("Don't carry suffix.\n");
			printf("Please use another name or enter quit to back to the booklist page.\n");
		}
		else if(CreateFolder(str)==0){
			printf("Booklist is already exist.\n");
			printf("Please use another name or enter quit to back to the booklist page.\n");
		}
		else{
			
			strcpy(str2,str);
			strcpy(str,"./");
			strcat(str,str2);
			create_booklist_file(str);
			strcpy(str3,"/");
			strcat(str,str3);
			strcpy(str3,".txt");
			strcat(str,str2);
			strcat(str,str3);
			booklist_add(bh, str);
			FILE *fr=fopen(str,"r");
			if(load_books(bh, fr)==-1){
				return blh;
			}
			fclose(fr);
			printf("Booklist %s created successfully.\n", str);
			return blh;
		}
	}
}

BookList *import_booklist(Book *bh, char *str){
	BookList *blh=(BookList *)malloc(sizeof(BookList));
	char *str2=(char*)malloc(100*sizeof(char));
	char *str3=(char*)malloc(100*sizeof(char));
	while(1){
		printf("booklist name(without file suffix):");
		fgets(str,91,stdin);
		clear_n(str);
		fflush(stdin);
		if(strlen(str)==0){
			printf("You has not choose yet, please try again.\n");
		}
		else if(strlen(str)>16){
			printf("Your list name is too long, please try again.\n");
		}
		else if(strcmpi(str, "quit")==0){
			blh->length=-1;
			return blh;
		}
		if(strstr(".",str)){
			printf("Don't carry suffix.\n");
			printf("Please use another name or enter quit to back to the booklist page.\n");
		}
		else if(Check_Folder(str)==0){
			printf("Booklist is not exist\n");
			printf("Please check the booklist name or enter quit to back to the booklist page.\n");
		}
		else{
			strcpy(str2,str);
			strcpy(str,"./");
			strcat(str,str2);
			strcpy(str3,"/");
			strcat(str,str3);
			strcat(str,str2);
			strcpy(str3,".txt");
			strcat(str,str3);
			FILE *fr=fopen(str,"r");
			if(load_books(bh, fr)==-1){
				return blh;
			}
			fclose(fr);
			blh->list=bh;
			blh->length=check_length_booklist(bh);
			break;
		}
	}
}

int find_author(Book *bh){
	char *str=(char*)malloc(100*sizeof(char));
	BookList *bl=(BookList *)malloc(sizeof(BookList));
	while(1){
		printf("Author:");
		fgets(str,91,stdin);
		clear_n(str);
		fflush(stdin);
		if(strlen(str)==0){
			printf("You did not enter anything yet, please try again.\n");
		}
		else if(strlen(str)>=90){
			printf("Your author name is too long, please try again or enter 'quit' to go back.\n");
		}
		else if(strcmpi(str, "quit")==0){
			return -1;
		}
		else{
			copy_booklist(bl, find_book_by_author(bh, str));
			if(bl->length!=0){
				list_books(bl->list);
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
	char *str=(char*)malloc(100*sizeof(char));
	BookList *bl=(BookList *)malloc(sizeof(BookList));
	while(1){
		printf("booktitle:");
		fgets(str,91,stdin);
		clear_n(str);
		fflush(stdin);
		if(strlen(str)==0){
			printf("\nYou did not enter anything yet, please try again.\n");
		}
		else if(strlen(str)>=24){
			printf("\nYour book name is too long, please try again or enter 'quit' to go back.\n");
		}
		else if(strcmpi(str, "quit")==0){
			return -1;
		}
		else{
			copy_booklist(bl, find_book_by_title(bh, str));
			printf("\n\nblh->length=%i\n",bl->length);
			if(bl->length!=0){
				list_books(bl->list);
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
	char *str=(char*)malloc(100*sizeof(char));
	BookList *bl=(BookList *)malloc(sizeof(BookList));
	int year;
	while(1){
		printf("Publish year:");
		fgets(str,91,stdin);
		clear_n(str);
		fflush(stdin);
		if(strcmpi(str, "quit")==0){
			return -1;
		}
		else if(isnum(str)==0){
			printf("Please just enter integer number.\n");
		}
		else if(strlen(str)==0){
			printf("You did not enter anything yet, please try again or enter 'quit' to go back.\n");
		}
		else if(strlen(str)>=5){
			printf("The year is impossible to exist...\n");
		}
		else{
			year = atoi(str);
			copy_booklist(bl, find_book_by_year(bh, year));
			
			
			
			if(bl->length!=0){
				list_books(bl->list);
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
	char *str=(char*)malloc(100*sizeof(char));
	while(1){
		printf("\nPlease choose an option:\n");
		printf("1)Search book by title\n");
		printf("2)Search book by author\n");
		printf("3)Search book by year\n");
		printf("4)quit\n");
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

int librarian_operation(Book *bh, User *uh, char *bookfile){
	char *str=(char*)malloc(100*sizeof(char));
	char *str2=(char*)malloc(100*sizeof(char));
	while(1){
		printf("\nPlease choose an option:\n");
		printf("1)Show the booklist\n");
		printf("2)Show the userlist\n");
		printf("3)Search book\n");
		printf("4)Search user\n");
		printf("5)Add book\n");
		printf("6)Delete book\n");
		printf("7)quit\n");
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
				list_books(bh);
			}
			else if(strcmp(str,"2")==0){
				list_users(uh);
			}
			else if(strcmp(str,"3")==0){
				search_book(bh);
			}
			else if(strcmp(str,"4")==0){
				
			}
			else if(strcmp(str,"5")==0){
				booklist_add(bh, bookfile);
			}
			else if(strcmp(str,"6")==0){
	
			}
			else if(strcmp(str,"7")==0){
				return 0;
			}
			else{
				printf("Invalid choice.\n");
			}
		}
	}
}

int librarianCLI(User *user, Book *bh, User *uh){
	char *bookfile=(char*)malloc(100*sizeof(char));
	BookList *blh;
	char *str=(char*)malloc(100*sizeof(char));
	char *state=(char*)malloc(100*sizeof(char));
	while(1){
		printf("\nWelcome, %s\n", user->username);
		printf("1)Import booklist\n");
		printf("2)Create a new booklist\n");
		printf("3)quit\n");
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
				blh = import_booklist(bh, bookfile);
				
				if(blh->length!=-1)
					librarian_operation(bh, uh, bookfile);
			}
			else if(strcmp(str,"2")==0){
				blh = create_booklist(bh, bookfile);
				if(blh->length!=-1)
					librarian_operation(bh, uh, bookfile);
			}
			else if(strcmp(str,"3")==0){
				return 0;
			}
			else{
				printf("Invalid choice\n");
			}
		}
	}

}


