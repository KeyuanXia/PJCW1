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
	while(1){
		if(i->next==NULL){
			q=bh->next;
			while(1){
				if(!q){
					return -1;
				}
				else if(q->id==choosen_book.id){
					q->copies--;
					p=(Book *)malloc(sizeof(Book));
					p->copies=1;
					p->totalcopies=1;
					p->year=q->year;
					p->title=strdpp(q->title);
					p->authors=strdpp(q->authors); 
					p->id=q->id;
					i->next=p;
					p->last=i;
					p->next=NULL;
					return 0;
				}
				q=q->next;
			}
		}
		else
			i=i->next;
	}
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
		if(b.id=u->id)
			remove_book(abh,b);
		u=u->next;
	}
}

int store_user_borrow(User *user, BookList *ubh, char *filename){
	char *temp=(char *)malloc(100*sizeof(char));
	char *temp_2=(char *)malloc(100*sizeof(char));
	strcpy(temp,"./Userdata/");
	strcpy(temp_2,".txt");
	strcat(temp,filename);
	strcat(temp,temp_2);
	FILE *fr=fopen(temp,"w");
	switch(store_books(ubh->list, fr)){
		case -1:printf("\n!!!Didn't find the user's borrow history, new one is added!!!\n\n");return -1;
		case 0:return 0;
		default:break;
	}
	fclose(fr);
	printf("\n***User borrowed books stored sucessfully!***\n");
	return 1;
}

int find_book_by_id(Book *abh, unsigned int id){
	Book *q;
	int i=0;
	q=abh->next;
	while(1){
		if(!q){
			if(i==0){
				return -1;
			}
			else{
				return 1;
			}
		}
		if(q->id==id){
			if(q->copies==0){
				return 2;
			}
			i++;
		}
		q=q->next;
	}
}

