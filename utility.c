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



int first_register(User *uh){

	char *typein_username, *typein_password; 
	User *q;
	q=(User *)malloc(sizeof(User));
	int tl;
	typein_username=(char*)malloc(100*sizeof(char));
	typein_password=(char*)malloc(100*sizeof(char));
	printf("please register the first user account, this user will be Librarian.\n\n");
	while(1){
		memset(typein_username, 0, sizeof(typein_username));
		printf("First_Register:\n");
		printf("username:");
		fgets(typein_username,16,stdin);
		fflush(stdin);
		tl=get_length(typein_username);
		if(tl>=16){
				printf("\n!Your username is too long!\n");
				printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
		else if(strcmpi(typein_username, "quit")==0){
			return 0;
		}
		else if(tl==0){
			printf("\nThe username can not be none.\n");
			printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
		else{
			break;
		}
	}
	while(1){
		printf("password:");
		fgets(typein_password,16,stdin);
		fflush(stdin);
		tl=strlen(typein_password);
		if(tl>=16){
			printf("\n!Your password is too long!\n");
			printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
		else if(strcmpi(typein_password, "quit")==0){
			return 0;
		}
		else if(tl==0){
			printf("\nThe password can not be none.\n");
			printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
		else{
				
				
				q->type=1;
				q->last=uh;
				q->next=0;
				q->Id=1;
				
				q->username=typein_username;
				q->password=typein_password;
				printf("\n***\n");
				uh->next=q;
				FILE *fr=fopen("Userlist.txt","w");
				store_user_data(fr, uh);
				fclose(fr);
				printf("\n***first user register successfully!***\n");
				return 1;
		}
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
