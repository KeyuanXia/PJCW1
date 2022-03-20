#ifndef __LINKLIST_H__
#define __LINKLIST_H__

#include"book_management.h"

Book *library_initial();

Book *AddBook(Book *h, Book *a);

void DeleteBook(Book *h, Book *d);

Book *ChooseBook(Book *h, int j);

#endif
