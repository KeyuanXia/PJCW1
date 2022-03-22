#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"User_management.h"
int get_length(char str[]){
	char *p = str;
	int count = 0;
	while (*p++ != '\n')
	{
		count++;
	}
	return count;
}

int store_user_data(FILE *fr, User *uh){
	if (fr==NULL){
		return -1;
	}
	User *q;
	
	q=uh->next;
	
	while(q!=0){
		fprintf(fr, "%i ;%s ;%s ;%i\n", q->Id, q->username, q->password, q->type);
		q=q->next;
	}
}

int load_user_data(FILE *fr, User *uh){
	if (fr==NULL){
		return -1;
	}
	char *username, *password; 
	username=(char*)malloc(100*sizeof(char));  
	password=(char*)malloc(100*sizeof(char));
	int i=0, d=0;
	User *q=(User *)malloc(sizeof(User));
	User *p;
	q=uh;
	while(1){
		if(feof(fr)){
			break;
		}
		p=(User *)malloc(sizeof(User));
		
		if(fscanf(fr, "%i ;%s ;%s ;%i\n", &p->Id, username, password, &p->type)<=0){
			break;
		}
		p->username=strdup(username);
		p->password=strdup(password);
		i++;
		q->next=p;
		p->last=q;
		q=p;
	}
	if(uh->next==0){
		return 0;
	}
	q->next=0; 
	uh->last=0;
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
			p->username=strdup(username);
			p->password=strdup(password);
			p->last=q;
			p->type=2;
			p->next=0;
			break;
		}
		q=q->next;
	}
	FILE *fr=fopen("Userlist.txt","w");
	store_user_data(fr, uh);
	fclose(fr);
	printf("\n***user register successfully!***\n");
	return 1;
}

int check_usernam(User *uh, char *str){
	
	User *q;
	q=uh;
	while(1){
		if(!q){
			return -1;
		}
		if(strcmp(q->username, str)==0){	
			return q->Id;
		}
		q=q->next;
		
	}
}

int check_password(User *uh, char *str, int id){
	User *q;
	q=uh;
	while(1){
		if(id==q->Id){
			break;
		}
		q=q->next;
	}
	if(strcmp(str,q->password)==0){
		if(q->type==1){
			return 1;
		}
		else if(q->type==2){
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
	printf("\nid\tusername\tpassword\ttype\n");
	while(q){
		printf("%i\t%s", q->Id, q->username);
		if(strlen(q->username)<8)
			printf("\t\t%s",q->password);
		else if(strlen(q->username)>=8)
			printf("\t%s",q->password);
		if(strlen(q->password)<8)
			printf("\t\t%i\n", q->type);
		else if(strlen(q->password)>=8)
			printf("\t%i\n",q->type);
		q=q->next;
	}
}

void clear_n(char *str){
	char *tmp = NULL;
	if ((tmp = strstr(str, "\n")))
	{
	     *tmp = '\0';
	}
}
