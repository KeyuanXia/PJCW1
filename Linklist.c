#include<stdio.h>
#include<stdlib.h>

#include"book_management.h"

#define CreatNode(p) p=(Book *)malloc(sizeof(Book));
#define DeleteNode(p) free(p);

Book *AddBook(Book *h, Book *a){  //CREAT
	Book *q;
	if(a->next==NULL){
		CreatNode(a);
		a=h->next;
		return a;
	}
	else{
		CreatNode(a);
		CreatNode(q);
		q=h->next;
		a=h->next;
		a->next=q;
		free(q);
		return a;
	}
}

void DeleteBook(Book *h, Book *d){
	h->next=d->next;
	free(d);
}

Book *ChooseBook(Book *h, int j){
	Book *q;
	int i;
	CreatNode(q);
	q=h
	for(i=0,i<j){
		q=q->next;
	}
	return q;
}
