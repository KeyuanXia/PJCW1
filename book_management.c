#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"book_management.h"
#include"utility.h"

int initial_booklist(Book *bh, char *filename){
	bh->id=0;
	FILE *fr=fopen(filename,"r");
	switch(load_books(bh, fr, filename)){
		case -1:printf("\n!!!Didn't find the booklist.!!!\n");return -1;
		case 0:printf("\n!!!Book list is NULL!!!\n");return 0;
		default:break;
	}
	
	fclose(fr);
	printf("\n***Book list insert successfully!***\n");
	return 1;
}

int store_books(Book *bh, FILE *file){
	if (file==NULL){
		return -1;
	}
	Book *q;
	q=bh->next;
	while(q!=0){
		fprintf(file, "%i\n", q->id);
		fputs(q->title,file);fprintf(file,"\n");
		fputs(q->authors,file);fprintf(file,"\n");
        fputs(q->bookfile,file);fprintf(file,"\n");
		fprintf(file, "%i\n", q->year);
		fprintf(file, "%i\n", q->copies);
		fprintf(file, "%i\n", q->totalcopies);
		q=q->next;
	}
    return 0;
}

int load_books(Book *bh, FILE *file, char *bookfile){
	if (file==NULL){
		return -1;
	}
    char *title=(char*)malloc(30*sizeof(char));
    char *author=(char*)malloc(100*sizeof(char));
    char *bookfile_name = (char *) malloc(100 * sizeof(char));
	int i=0;
	Book *q;
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
		fgets(title, 30, file);
		fgets(author, 100, file);
        fgets(bookfile_name, 100, file);
		fscanf(file, "%i\n", &p->year);
		fscanf(file, "%i\n", &p->copies);
		fscanf(file, "%i\n", &p->totalcopies);
		clear_n(title);
		clear_n(author);
        clear_n(bookfile_name);
		p->title=strdpp(title);
		p->authors=strdpp(author);
        p->bookfile=strdpp(bookfile_name);
        if(strcmp(bookfile_name,bookfile)==0){
            i++;
            q->next = p;
            p->last = q;
            q = p;
        }
	}
	if(bh->next==0){
		free(title);
		free(author);
		return 0;
	}
	free(title);
	free(author);
	q->next=NULL; 
	bh->last=NULL;
	return i;
}

int add_book(Book *bh, Book book){
	Book *q, *p;
	q=bh;
	while(1){
		if(q->next==NULL){
			p=(Book *)malloc(sizeof(Book));
			p->copies=book.copies;
			p->totalcopies=book.totalcopies;
			p->year=book.year;
			p->title=strdpp(book.title);
			p->authors=strdpp(book.authors);
            p->bookfile=strdpp(book.bookfile);
			p->id=q->id+1;
			q->next=p;
			p->last=q;
			p->next=NULL;
			return 0;
		}
		q=q->next;
	}
}

int remove_book(Book *bh, Book book){
	Book *q, *p;
	q=bh;
	while(q){
		if(q->id==book.id){
            if(book.totalcopies==-2){
                book.totalcopies=-2;
            }
            else if(q->copies<q->totalcopies){
                return -2;
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

BookList *find_book_by_title (Book *bh, const char *title){
	Book *q, *p, *temp;
	BookList *blh;
	blh=(BookList *)malloc(sizeof(BookList));
    blh->list=(Book *)malloc(sizeof(Book));
	p=blh->list;
	blh->length=0;
	q=bh->next;
	while(1){

		if(!q){
			if(blh->length==0){

				return blh;
			}
			else{

				return blh;
			}
		}
		if(strcmp(q->title, title)==0){
			temp=(Book *)malloc(sizeof(Book));
			copy_book(temp, q);
			p->next=temp;
			p=p->next;
			blh->length++;
		}
		q=q->next;
	}
}

BookList *find_book_by_author (Book *bh, const char *author){ 
	Book *q, *p, *temp2, *temp;
	BookList *blh;
	char *t; 
	blh=(BookList *)malloc(sizeof(BookList));
    blh->list=(Book *)malloc(sizeof(Book));
	temp=(Book *)malloc(sizeof(Book));
	p=blh->list;
	blh->length=0;
	q=bh->next;
	while(1){
		if(!q){
			if(blh->length==0){
				printf("\nDidn't find book with author: '%s'\n", author);
				return blh;
			}
			else{
				
				return blh;
			}
		}
		temp->authors=strdpp(q->authors);
		t=strtok(temp->authors, ",");
		while(t!=NULL){
			if(strcmp(t, author)==0){
				temp2=(Book *)malloc(sizeof(Book));
				copy_book(temp2, q);
				p->next=temp2;
				p=p->next;
				blh->length++;
				break;
			}
			t=strtok(NULL, ",");
		}
		q=q->next;
	}
    free(temp);
}

BookList *find_book_by_year (Book *bh, unsigned int year){
	Book *q, *p, *temp;
	BookList *blh;
	blh=(BookList *)malloc(sizeof(BookList));
    blh->list=(Book *)malloc(sizeof(Book));
	p=blh->list;
	blh->length=0;
	q=bh->next;
	while(1){
		if(!q){
			if(blh->length==0){
				printf("\nDidn't find book published at %i\n", year);
				
				return blh;
			}
			else{
				return blh;
			}
		}
		if(q->year==year){
			temp=(Book *)malloc(sizeof(Book));
			copy_book(temp, q);
			p->next=temp;
			p=p->next;
			blh->length++;
		}
		q=q->next;
	}
}

int list_books(Book *bh, unsigned int length){
	Book *q;
	int i=0;
	if(!bh->next){
		return -1;
	}
	printf("\nid\ttitle\t\t\tcopies\t\t\t\tYear\t\tauthors\n");
	q=bh->next;
	while(q){
		if(i==length){
			break;
		}
		printf("%i\t%s", q->id, q->title);
		if(strlen(q->title)<4)
			printf("\t\t\t\t%i/%i",q->copies, q->totalcopies);
		else if(strlen(q->title)>=4&&strlen(q->title)<8)
			printf("\t\t\t%i/%i",q->copies, q->totalcopies);
		else if(strlen(q->title)>=8&&strlen(q->title)<12)
			printf("\t\t%i/%i",q->copies, q->totalcopies);
        else if(strlen(q->title)>=12)
            printf("\t%i/%i",q->copies, q->totalcopies);
			
		if((check_numlen(q->copies)+check_numlen(q->totalcopies))<3)
			printf("\t\t\t\t\t%-4i\t\t%s\n",q->year, q->authors);
		else if((check_numlen(q->copies)+check_numlen(q->totalcopies))>=3&&(check_numlen(q->copies)+check_numlen(q->totalcopies))<7)
			printf("\t\t\t\t%-4i\t\t%s\n",q->year, q->authors);
        else if((check_numlen(q->copies)+check_numlen(q->totalcopies))>=7&&(check_numlen(q->copies)+check_numlen(q->totalcopies))<15)
            printf("\t\t\t%-4i\t\t%s\n",q->year, q->authors);
		
		q=q->next;
		i++;
	}
    return 0;
}
