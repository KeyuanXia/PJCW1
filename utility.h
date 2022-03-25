#ifndef __UTILITY_H__
#define __UTILITY_H__

#include"User_management.h"
#include"book_management.h"

char *strdpp(const char *s);

int check_numlen(int a);

int store_user_data(FILE *fr, User *uh);

void clear_n(char *str);

int load_user_data(FILE *fr, User *uh);

int user_register_datain(User *uh, char *username, char *password);

User *check_usernam(User *uh, char *str);

int check_passwor(User *user, char *str);

int list_users(User *uh);

int CreateFolder(const char *folderName);

int check_length_booklist(Book *bh);

int copy_booklist(BookList *to, BookList from);

int isnum(char *s);

#endif
