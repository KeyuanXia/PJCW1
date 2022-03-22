#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"book_management.h"

int store_books(Book *bh, FILE *file){
	if (file==NULL){
		perror("\nDidn't find the bookfile.\n");
		return -1;
	}
	Book *q;
	q=bh->next;
	while(q!=0){
		fprintf(file, "%i ;%s ;%s ;%i ;%i\n", q->id, q->title, q->authors, q->year, q->copies);
		q=q->next;
	}
}

int load_books(Book *bh, FILE *file){
	if (file==NULL){
		perror("\nDidn't find the bookfile.\n");
		return -1;
	}
	char *title, *author; 
	title=(char*)malloc(100*sizeof(char));  
	author=(char*)malloc(100*sizeof(char));
	int i=0;
	Book *q=(Book *)malloc(sizeof(Book));
	Book *p;
	q=bh;
	while(1){
		if(feof(file)){
			break;
		}
		p=(Book *)malloc(sizeof(Book));
		
		if(fscanf(file, "%i ;%s ;%s ;%i ;%i\n", &q->id, title, author, &q->year, &q->copies)<=0){
			break;
		}
		p->title=strdup(title);
		p->authors=strdup(author);
		i++;
		q->next=p;
		p->last=q;
		q=p;
	}
	if(bh->next==0){
		return 0;
	}
	q->next=0; 
	bh->last=0;
	return i;
}

int add_book(Book *bh, Book book){
	Book *q, *p;
	q=bh;
	while(1){
		if(q->next==0){
			p=&book;
			q->next=p;
			p->last=q;
			return 0;
		}
		q=q->next;
	}
}

int remove_book(Book *bh, Book book){
	Book *q, *p;
	q=bh;
	while(1){
		if(q->id==book.id){
			if(q->next){
				p=q->next;
				q->last->next=p;
				p->last=q->last;
				free(q);
				return 0;
			}
			else{
				free(q);
				return 0;
			}
		}
		q=q->next;
	}
}




