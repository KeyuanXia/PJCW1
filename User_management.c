#include<stdio.h>
#include<string.h>

#include"Linklist.h" 
#include"User_management.h" 
#include"utility.h"

int initial_userlist(User *h){
	User *h=malloc(sizeof(User));
	User *q=malloc(sizeof(User));
	User *p;
	FILE *fr=fopen("Userlist.txt","rb");
	if(fr==NULL){
		perror("\n!!!Lose the Userdata, the initial of userdata failed.!!!\n");
		return -1;
	}
	q=h;
	while(q!=NULL){
		*p=(User *)malloc(sizeof(User));
		if(fread(&p, sizeof(User), 1, fr)==NULL){
			break;
		}
		q->next=p;
		p->last=q;
		q=p;
	}
	fr.close();
	printf("\n\n***Userdata insert sucessfully!***\n\n"); 
}

int user_login(){
	User *p; 
	User *q;
	int id,type;
	char typein[16];
	while(1){
		printf("username:");
		typein = checklength(16);
		if(typein=="tl"){
			printf("\n!Your username is too long!\n");
			printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
		else if(typein =="quit"){
			return 0;
		}
		id = check_username(*uh,typein);
		if(id==-1){
			printf("\n!The username has not been created before, please check your username.!\n");
			printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
	}
	while(1){
		printf("password:");
		typein = checklength(16);
		if(typein=="tl"){
			printf("\n!Your password is too long!\n");
			printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
		else if(typein =="quit"){
			return 0;
		}
		type = check_password(*uh,typein);
		if(type==0){
			printf("\n!Wrong password!\n");
			printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
		else if(type==-1){
			return 0;
		}
		else if(type==1){
			return 1;
		}
		else if(type==2){
			return 2;
		}
	}
}

int user_register(){
	
}

int librarianCLI(){
	
}

int userCLI(){
	
}

int login_or_register(){
	initial_userlist(*uh);
	char typein[10];
	int j;
	while(1){
		printf("Please login or register:\n");
		printf("1) Login\n");
		printf("2) Register an account\n");
		printf("3) Quit\n")
		printf("choice:")
		typein = checklength(1);
		if(typein=="ts"){
			printf("You has not choose yet, please try again.\n");
		}
		else if(typein=="tl"){
			printf("Your choice is too long, please try again.\n");
		}
		else if(i==1){
			if(typein[0]=='1'){			///Login
				j=user_login();
				if(j==1){
					return 1;
				}
				else if(j==2){
					return 2;
				}
			}
			else if(typein[0]=='2'){	///Register
				j=user_register();
			}
			else if(typein[0]=='3'){	///Quit
				return -1;
			}
		}
	}
}

int login(){
	
}
