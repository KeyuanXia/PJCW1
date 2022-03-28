#ifndef __LIBRARIAN_H__
#define __LIBRARIAN_H__

#include"User_management.h"
#include"book_management.h"

int booklist_add(Book *bh, char *bookfile);

int create_booklist_file(char *fileName);

int book_remove(Book *bh, char *filename);

int librarianCLI(User *user, Book *bh, User *uh, char *filename);


#endif
