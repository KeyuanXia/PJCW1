#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <unistd.h>

#include"User_management.h"
#include"book_management.h"

char *strdpp(const char *s){
    size_t size = strlen(s) + 1;
    char *p = (char *)malloc(size*sizeof(char));
    if (p) {
        memcpy(p, s, size);
    }
    return p;
}

int check_numlen(int a){
	int i;
	for(i=0;a>1;i++){
		a=a/10;
        if(a==1) i++;
	}
	return i;
}

void CreateFolder(const char *folderName){
    if (access(folderName, 0) == -1)
    {
        mkdir(folderName,0777);
    }
}

int store_user_data(FILE *fr, User *uh){
	if (fr==NULL){
		return -1;
	}
	User *q;
	q=uh->next;
	while(q!=0){
		fprintf(fr, "%i\n", q->Id);
		fputs(q->username,fr);fprintf(fr,"\n");
		fputs(q->password,fr);fprintf(fr,"\n");
		fprintf(fr, "%i\n", q->type);
		q=q->next;
	}
    return 0;
}

void clear_n(char *str){
	char *tmp = NULL;
	if ((tmp = strstr(str, "\n")))
	{
	     *tmp = '\0';
	}
}

int load_user_data(FILE *fr, User *uh){
	if (fr==NULL){
		return -1;
	}
	char *username, *password; 
	username=(char*)malloc(100*sizeof(char));  
	password=(char*)malloc(100*sizeof(char));
	int i=0, d;
	User *q, *p;
	q=uh;
	while(1){
		if(feof(fr)){
			break;
		}
		p=(User *)malloc(sizeof(User));
		
		if(fscanf(fr, "%i\n", &p->Id)<=0){
			break;
		}
		fgets(username, 20, fr);
		fgets(password, 20, fr);
		fscanf(fr, "%i\n", &p->type);
		clear_n(username);
		clear_n(password);
		p->username=strdpp(username);
		p->password=strdpp(password);
		
		i++;
		q->next=p;
		p->last=q;
		q=p;
	}
	if(uh->next==0){
		return 0;
	}
	q->next=NULL; 
	uh->last=NULL;
	return i;
}

int user_register_datain(User *uh, char *username, char *password){
	User *q;
	User *p;
	q=uh;
	while(1){
		if(q->next==NULL){
			p=(User*)malloc(sizeof(User));
			q->next=p;
			p->Id=q->Id+1;
			p->username=strdpp(username);
			p->password=strdpp(password);
			p->last=q;
			p->type=2;
			p->next=0;
			break;
		}
		q=q->next;
	}
	FILE *fr=fopen("./Userdata/Userlist.txt","w");
	store_user_data(fr, uh);
	fclose(fr);
	printf("\n***user register successfully!***\n");
	return 1;
}

User *check_usernam(User *uh, char *str){
	User *q, *p=(User *)malloc(sizeof(User));
	q=uh->next;
	while(1){
		if(!q){
			p->type=-1; 
			return p;
		}
		if(strcmp(q->username, str)==0){	
			return q;
		}
		q=q->next;
	}
}

int check_passwor(User *user, char *str){
	if(strcmp(str,user->password)==0){
		if(user->type==1){
			return 1;
		}
		else if(user->type==2){
			return 2;
		}
	}
	else{
		return -1;
	}
}

int list_users(User *uh){
	User *q;
	q=uh->next;
        printf("\n------------------------------------------------------------------------------------------------\n");
	printf("\nid\t\tusername\t\tpassword\t\ttype\n");
	while(q){
		printf("%-16i%-24s%-24s%i\n", q->Id, q->username,q->password,q->type);
		q=q->next;
	}
        printf("\n------------------------------------------------------------------------------------------------\n");
}

int check_length_booklist(Book *bh){
	Book *q;
	q=bh;
	int count = 0;
	while (q->next)
	{
		count++;
		q=q->next;
	}
	return count;
	
}

int copy_book(Book *to, Book *from){
	to->id=from->id;
	to->title=strdpp(from->title);
	to->authors=strdpp(from->authors);
	to->copies=from->copies;
	to->totalcopies=from->totalcopies;
	to->year=from->year;
    to->bookfile= strdpp(from->bookfile);
}

int copy_book_to_nonpointer(Book to, Book *from){
    to.id=from->id;
    to.title=strdpp(from->title);
    to.authors=strdpp(from->authors);
    to.copies=from->copies;
    to.totalcopies=from->totalcopies;
    to.year=from->year;
    to.bookfile= strdpp(from->bookfile);
}

int copy_booklist(BookList *to, BookList *from){
    int i;
    Book *q, *p, *temp;
    if(from->length==0){
        to->length=0;
        return -1;
    }
    to->length=from->length;
    to->list=from->list;
    q=to->list;
    p=from->list->next;
    for(i=0;i<from->length;i++){
        temp=(Book *)malloc(sizeof(Book));
        copy_book(temp,p);
        q->next=temp;
        q=q->next;
        p=p->next;
    }
}

int isnum(char *s){
    int i;
    for(i=0;i<strlen(s);i++){
        if(s[i]<'0'||s[i]>'9'){return 0;}}
    return 1;
}
