#ifndef __UTILITY_H__
#define __UTILITY_H__

#include"User_management.h"
#include"book_management.h"

//used to malloc the string space according to the length of string and copy the string
char *strdpp(const char *s);

//used to check the length of copies and total copies for the integrity of interface
int check_numlen(int a);

//store the user list in a specified folder
int store_user_data(FILE *fr, User *uh);

//clean the n at the last char of string
//this is working for the fgets()
void clear_n(char *str);

//load the user list from specified file
int load_user_data(FILE *fr, User *uh);

//add the registered user data into user list
int user_register_datain(User *uh, char *username, char *password);

User *check_usernam(User *uh, char *str);

int check_passwor(User *user, char *str);

int list_users(User *uh);

int CreateFolder(const char *folderName);

int check_length_booklist(Book *bh);

int copy_booklist(BookList *to, BookList from);

//malloc and copy a book
int copy_book(Book *to, Book *from);

int copy_book_to_nonpointer(Book to, Book *from);

//used to check a string whether be a number
int isnum(char *s);

#endif
