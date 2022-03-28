#ifndef BORROW_MANAGEMENT_GUARD__H 
#define BORROW_MANAGEMENT_GUARD__H

int remove_choosen_book(Book *bh, Book choosen_book, BookList *ubh);

int add_borrow_book(Book *bh, Book choosen_book, BookList *ubh);

int choose_available_book(Book *abh, Book *bh, BookList *ubh);

int store_user_borrow(User *user, BookList *ubh, char *filename);

int find_book_by_id (Book *abh, unsigned int id);

#endif
