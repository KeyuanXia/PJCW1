#ifndef __USER_H__
#define __USER_H__

int initial_user_borrow(User *user, BookList *ubh, char *username, char *bookfile);

int _borrow_book(Book *bh, BookList *ubh, Book *abh, char *username, char *bookfile);

int borrow_book(User *user, Book *bh, BookList *ubh, char *username, char *bookfile);

int _return_book(Book *bh, BookList *ubh, char *filename);

int return_book(User *user, Book *bh, BookList *ubh, char *filename, char *bookfile);

int userCLI(User *user, Book *bh, char *filename, char *bookfile);

#endif
