#ifndef BORROW_MANAGEMENT_GUARD__H 
#define BORROW_MANAGEMENT_GUARD__H

int remove_chosen_book(Book *bh, Book chosenBook, BookList *ubh);

int add_borrow_book(Book *bh, Book chosen_book, BookList *ubh);

void choose_available_book(Book *abh, Book *bh, BookList *ubh);

int store_user_borrow(BookList *ubh, char *username, char *bookfile);

int find_book_by_id (Book *abh, unsigned int id);

#endif
