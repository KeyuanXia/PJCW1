#ifndef __USER_H__
#define __USER_H__

int initial_user_borrow(User *user, BookList *ubh, char *filename);

int store_user_borrow(User *user, BookList *ubh, char *filename);

int _borrow_book(Book *bh, BookList *ubh, Book *abh, char *filename);

int borrow_book(User *user, Book *bh, BookList *ubh, char *filename, char *bookfile);

int _return_book(Book *bh, BookList *ubh, char *filename);

int return_book(User *user, Book *bh, BookList *ubh, char *filename, char *bookfile);

int store_user_borrowed(User *user, BookList *ubh, char *filename);

int userCLI(User *user, Book *bh, char *filename, char *bookfile);

#endif
