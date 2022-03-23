#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"book_management.h"
#include"utility.h"

int store_books(Book *bh, FILE *file){
	if (file==NULL){
		perror("\nDidn't find the booklist.\n");
		return -1;
	}
	Book *q;
	q=bh->next;
	while(q!=0){
		fprintf(file, "%i\n", q->id);
		fputs(q->title,file);fprintf(file,"\n");
		fputs(q->authors,file);fprintf(file,"\n");
		fprintf(file, "%i\n", q->year);
		fprintf(file, "%i\n", q->copies);
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
	author=(char*)malloc(120*sizeof(char));
	int i=0;
	Book *q=(Book *)malloc(sizeof(Book));
	Book *p;
	q=bh;
	while(1){
		if(feof(file)){
			break;
		}
		p=(Book *)malloc(sizeof(Book));
		
		if(fscanf(file, "%i\n", &p->id)<=0){
			break;
		}
		fgets(title, 101, file);
		fgets(author, 101, file);
		fscanf(file, "%i\n", &p->year);
		fscanf(file, "%i\n", &p->copies);
		clear_n(title);
		clear_n(author);
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

BookList find_book_by_title (Book *bh, const char *title){
	Book *q, *p;
	BookList *blh;
	blh=(BookList *)malloc(sizeof(BookList));
	p=blh->list;
	blh->length=0;
	q=bh;
	while(1){
		if(!q){
			if(blh->length==0){
				printf("Didn't find book with title: '%s'", title);
				return *blh;
			}
			else{
				return *blh;
			}
		}
		if(strcmp(q->title, title)==0){	
			p->next=q;
			p=p->next;
			blh->length++;
		}
		q=q->next;
	}
}

BookList find_book_by_author (Book *bh, const char *author){ //when add authors, remenber to add "h,"at first, or strtok won't work well.
	Book *q, *p;
	BookList *blh;
	char *t; 
	blh=(BookList *)malloc(sizeof(BookList));
	p=blh->list;
	blh->length=0;
	q=bh;
	while(1){
		if(!q){
			if(blh->length==0){
				printf("Didn't find book with author: '%s'", author);
				return *blh;
			}
			else{
				return *blh;
			}
		}
		t=strtok(q->authors, ",");
		while(t){
			t=strtok(NULL, ",");
			if(strcmp(t, author)==0){	
				p->next=q;
				p=p->next;
				blh->length++;
				break;
			}
		}
		q=q->next;
	}
}

BookList find_book_by_year (Book *bh, unsigned int year){
	Book *q, *p;
	BookList *blh;
	blh=(BookList *)malloc(sizeof(BookList));
	p=blh->list;
	blh->length=0;
	q=bh;
	while(1){
		if(!q){
			if(blh->length==0){
				printf("Didn't find book published at '%i'", year);
				return *blh;
			}
			else{
				return *blh;
			}
		}
		if(q->year==year){	
			p->next=q;
			p=p->next;
			blh->length++;
		}
		q=q->next;
	}
}
