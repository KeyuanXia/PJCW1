#ifndef __LIBRARIAN_H__
#define __LIBRARIAN_H__

#include"User_management.h"
#include"book_management.h"

int booklist_add(Book *bh, char *bookfile);

int create_booklist_file(char *fileName);

BookList *create_booklist(Book *bh, char *str);

BookList *import_booklist(Book *bh, char *str);

int librarian_operation(Book *bh, User *uh, char *bookfile);

int librarianCLI(User *user, Book *bh, User *uh);


#endif
