#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"utility.h"
#include"book_management.h"
#include"User_management.h"
#include"search.h"
#include"librarian.h"
#include"User.h"
#include"borrow_management.h"


int remove_choosen_book(Book *bh, Book choosen_book, BookList *ubh){
	Book *q, *p, *c, *b;
	q=ubh->list;
	b=bh;
	while(q){
		if(q->id==choosen_book.id){
			while(b){
				if(b->id==q->id){
					b->copies++;
				}
				b=b->next;
			}
			if(q->next){
				p=q->next;
				q->last->next=p;
				p->last=q->last;
				free(q);
				return 0;
			}
			else{
				q->last->next=NULL;
				free(q);
				return 0;
			}
		}
		q=q->next;
	}
	return -1;
}

int add_borrow_book(Book *bh, Book choosen_book, BookList *ubh){
	Book *q, *p, *i;
	q=bh->next;
	i=ubh->list;
	while(q){
		while(i->next!=NULL){
			i=i->next;
		}
		if(q->id==choosen_book.id){
			q->copies--;
			p=(Book *)malloc(sizeof(Book));
			p->copies=choosen_book.copies;
			p->totalcopies=choosen_book.totalcopies;
			p->year=choosen_book.year;
			p->title=strdpp(choosen_book.title);
			p->authors=strdpp(choosen_book.authors); 
			p->id=choosen_book.id;
			i->next=p;
			p->last=i;
			p->next=NULL;
			return 0;
		}
		q=q->next;
	}
	return -1;
} 

int choose_available_book(Book *abh, Book *bh, BookList *ubh){
	Book *q, *p, *book, *u, b;
	int i;
	q=abh;
	book=bh->next;
	u=ubh->list->next;
	while(book){
		p=(Book *)malloc(sizeof(Book));
		copy_book(p,book);
		q->next=p;
		p->last=q;
		q=q->next;
		book=book->next;
	}
	while(u){
		b.id=u->id;
		remove_book(abh,b);
	}
}

int store_user_borrowed(User *user, BookList *ubh, char *filename){
	ubh->list->id=0;
	char *temp=(char *)malloc(100*sizeof(char));
	char *temp_2=(char *)malloc(100*sizeof(char));
	strcpy(temp,"./Userdata/");
	strcpy(temp_2,".txt");
	strcat(temp,filename);
	strcat(temp,temp_2);
	FILE *fr=fopen(temp, "w");
	if(store_books(ubh->list, fr)==-1)
		printf("\n!!!Lose the Userdata folder, store user borrowed book failed.!!!\n\n");
	fclose(fr);
}

int load_borrow_books(Book *ubh, FILE *file){
	
}

int store_borrow_books(Book *ubh, FILE *file){
	
}


