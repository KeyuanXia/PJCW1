#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"Linklist.h" 
#include"User_management.h" 
#include"utility.h"

int initial_userlist(User *h){
	h=(User *)malloc(sizeof(User));
	User *q=(User *)malloc(sizeof(User));
	User *p;
	FILE *fr=fopen("Userlist.txt","rb");
	if(fr==NULL){
		perror("\n!!!Lose the Userdata, the initial of userdata failed.!!!\n");
		return -1;
	}
	q=h;
	while(q!=NULL){
		p=(User *)malloc(sizeof(User));
		if(fread(&p, sizeof(User), 1, fr)==NULL){
			break;
		}
		q->next=p;
		p->last=q;
		q=p;
	}
	fclose(fr);
	printf("\n\n***Userdata insert sucessfully!***\n\n"); 
}

int user_login(User *uh){
	User *p; 
	User *q;
	char * str;  
	int tl, id, type;
	str=(char*)malloc(100*sizeof(char));  
	while(1){
		printf("Login:\n");
		printf("username:");
		fgets(str,16,stdin);
		fflush(stdin);
		tl = strlen(str);
		if(tl>=90){
			printf("\n!Your username is too long!\n");
			printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
		else if(strcmpi(str, "quit")){
			return 0;
		}
		id = check_usernam(uh,str);
		if(id==-1){
			printf("\n!The username has not been created before, please check your username.!\n");
			printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
	}
	while(1){
		printf("password:");
		tl = strlen(str);
		if(tl>=90){
			printf("\n!Your password is too long!\n");
			printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
		else if(strcmpi(str, "quit")){
			return 0;
		}
		type = check_password(uh, *str, id);
		if(type==0){
			printf("\n!Wrong password!\n");
			printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
		else if(type==1){
			return 1;
		}
		else if(type==2){
			return 2;
		}
	}
}

int check_usernam(User *uh, char *str){
	User *p; 
	User *q;
	q=uh;
	p=q->next;
	while(1){
		if(p==NULL){
			return -1;
		}
		else if(strcmp(p->username, str)==0){
			return p->Id;
		}
		q=p;
		p=q->next;
	}
}

int check_password(User *uh, char *str, int id){
	User *p; 
	User *q;
	q=uh;
	p=q->next;
	while(1){
		if(id==p->Id){
			break;
		}
		q=p;
		p=q->next;
	}
	if(strcmp(str,p->password)==0){
		if(p->type==1){
			return 1;
		}
		else if(p->type==2){
			return 2;
		}
	}
	else{
		return 0;
	}

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
			p->username=username;
			p->password=password;
			p->last=q;
			p->type=2;
			break;
		}
		q=q->next;
	}
	FILE *fr=fopen("Userlist.txt","wb");
	q=uh->next;
	while(q!=NULL){
		fwrite(&q, sizeof(User), 1, fr);
		q=q->next;
	}
	fclose(fr);
	printf("\n***user register successfully!***\n");
	return 1;
}

int user_register(User *uh){
	char *typein_username, *typein_password; 
	int tl;
	typein_username=(char*)malloc(100*sizeof(char));  
	typein_password=(char*)malloc(100*sizeof(char));
	while(1){
	printf("username:");
	fgets(typein_username,16,stdin);
	fflush(stdin);
	tl=get_length(typein_username);
	if(tl>=16){
			printf("\n!Your username is too long!\n");
			printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
		else if(strcmpi(typein_username, "quit")){
			return 0;
		}
	}
	while(1){
		printf("password:");
		scanf("%s", &typein_password);
		tl=strlen(typein_password);
		if(tl>=90){
			printf("\n!Your password is too long!\n");
			printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
		else if(strcmpi(typein_password, "quit")){
			return 0;
		}
		else{
			user_register_datain(uh, typein_username, typein_password);
		}
	}
}

int librarianCLI(){
	
}

int userCLI(){
	
}

int login_or_register(User *uh){
	if(initial_userlist(uh)==-1){
		return -1;
	}
	int j;
	char *str=NULL;
	str=(char*)malloc(100*sizeof(char));
	while(1){
		printf("Please login or register:\n");
		printf("1) Login\n");
		printf("2) Register an account\n");
		printf("3) Quit\n");
		printf("choice:");
		fgets(str,10,stdin);
		fflush(stdin);
		if(get_length(str)==0){
			printf("You has not choose yet, please try again.\n");
		}
		else if(get_length(str)>1){
			printf("Your choice is too long, please try again.\n");
		}
		else{
			if(strcmp(str,"1\n")==0){			///Login
				j=user_login(uh);
				printf("1");
				if(j==1){
					return 1;
				}
				else if(j==2){
					return 2;
				}
			}
			else if(strcmp(str,"2\n")==0){	///Register
				j=user_register(uh);
			}
			else if(strcmp(str,"3\n")==0){	///Quit
				return -1;
			}
			else{
				printf("\ninvalid choose.\n");
			}
		}
	}
}

