#include<stdio.h>
#include<stdlib.h>

#include"book_management.h"

int load_books(Book *bh, char file[]){
	FILE *fr=NULL;
	fr=fopen(file, "rb");
	if (fr==NULL){
		perror("Didn't find the library file, please check the library name.\n");
		return -1;
	}
	int i=0;
	Book *q=(Book *)malloc(sizeof(Book));
	Book *p;
	bh=q;
	while(q!=NULL){
		p=(Book *)malloc(sizeof(Book));
		if(fread(&p, sizeof(Book), 1, fr)==NULL){
			break;
		}
		i++;
		q->next=p;
		p->last=q;
		q=p;
	}
	printf("\n\n***Load %i books from library sucessfully!***\n\n", i);
	return i;
}





