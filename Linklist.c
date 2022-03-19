#include<stdio.h>
#include<stdlib.h>

#include"book_management.h"
#include"User_management.h"

#define CreatNode(p) p=(Book *)malloc(sizeof(Book));
#define DeleteNode(p) free(p);


Book *library_initial(){
	Book *h=(Book *)malloc(sizeof(Book));
	if(NULL==h){
		printf("malloc library fail.");
		return NULL;
	}
	h->next=NULL;
	return h;
}

Book *AddBook(Book *h, Book *a){  //CREATE
	Book *q;
	CreatNode(q);
	if(h->next==NULL){
		a=h->next;
		a->next=NULL;
		return a;
	}
	q=h->next;
	while(1){
		if(q->next!=NULL){
			q=q->next;
		}
		else{
			break;
		}
	}
	q->next=a;
	free(q);
	return a;
}

void DeleteBook(Book *h, Book *d){
	Book *q;
	CreatNode(q);
	if(h->next==NULL){
		printf("\nBook list has not been loaded yet.\n");
		exit(1);
	}
	else{
		q=h->next;
	}
	while(1){
		if(q->id==d->id){
			q->next=d->next;
			free(d);
			while(1){
				if(q->next!=NULL){
					q=q->next;
					q->id--;
				}
				else{
					break;
				}
			}
			break;
		}
		else{
			q=q->next;
		}
	}
	free(q);
	
}

Book *ChooseBook(Book *h, int j){
	Book *q;
	int i;
	CreatNode(q);
	q=h;
	for(i=0;i<j;i++){
		q=q->next;
	}
	return q;
}

int check_username(User *uh, char username[16]){
	User *p, *q;
	p=uh->next;
		while(p->username!=username){
			if(p->next==NULL){
				return -1;
			}
			q=p->next;
			p=q;
		}
	return p->Id;
}

int check_password(User *uh, char password[16]){
	User *p, *q;
	p=uh->next;
		while(p->password!=password){
			if(p->next==NULL){
				return -1;
			}
			q=p->next;
			p=q;
		}
	return p->type;
}


