#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"Linklist.h" 
#include"User_management.h" 
#include"utility.h"

int initial_userlist(User *h){
	h->Id=0;
	
	FILE *fr=fopen("Userlist.txt","r");
	switch(load_user_data(fr, h)){
		case -1:perror("\n!!!Lose the Userdata, the initial of userdata failed.!!!\n");return -1;
		case 0:printf("\n!!!User list is NULL, the initial of user data failed!!!\n");return 0;
		default:break;
	}
	fclose(fr);
	
	printf("\n\n***Userdata insert sucessfully!***\n\n"); 
	return 1;
}

int user_login(User *uh){
	User *p; 
	User *q;
	char *str;  
	int tl, id, type;
	str=(char*)malloc(100*sizeof(char));  
	while(1){
		printf("Login:\n"); 
		printf("username(less than 16 characters):");
		fgets(str,91,stdin);
		clear_n(str);
		fflush(stdin);
		tl = strlen(str);
		if(tl>=16){
			printf("\n!Your username is too long!\n");
			printf("Please try again or enter 'quit' to back to the login and register page.\n");
			continue;
		}
		else if(strcmpi(str, "quit")==0){
			return 0;
		}
		else if(tl==0){
			printf("\n!Your username cannot be empty!\n");
			continue;
		}
		
		id = check_usernam(uh,str);
		
		if(id==-1){
			printf("\n!The username has not been created before, please check your username.!\n");
			printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
		else{
			break;
		}
	}
	while(1){
		printf("password:");
		fgets(str,20,stdin);
		clear_n(str);
		fflush(stdin);
		tl = strlen(str);
		if(tl>=16){
			printf("\n!Your password is too long!\n");
			printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
		else if(strcmpi(str, "quit")==0){
			return 0;
		}
		type = check_password(uh, str, id);
		if(type==-1){
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
	
	User *q;
	q=uh;
	while(1){
		printf("\n\n***In the username check***\n\n");
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

int user_register(User *uh){
	char *typein_username, *typein_password; 
	int tl;
	typein_username=(char*)malloc(100*sizeof(char));  
	typein_password=(char*)malloc(100*sizeof(char));
	while(1){
		memset(typein_username, 0, sizeof(typein_username));
		printf("Register\n");
		printf("\tusername:");
		fgets(typein_username,20,stdin);
		clear_n(typein_username);
		fflush(stdin);
		tl=strlen(typein_username);
		if(tl>=16){
				printf("\n!Your username is too long!\n");
				printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
		else if(strcmpi(typein_username, "quit")==0){
			return 0;
		}
		else if(check_usernam(uh, typein_username)!=-1){
			printf("The username is already exist, please choose another.\n");
		}
		else{
			break;
		}
	}
	while(1){
		printf("password:");
		fgets(typein_password,16,stdin);
		clear_n(typein_password);
		fflush(stdin);
		tl=strlen(typein_password);
		if(tl>=90){
			printf("\n!Your password is too long!\n");
			printf("Please try again or enter 'quit' to back to the login and register page.\n");
		}
		else if(strcmpi(typein_password, "quit")==0){
			return 0;
		}
		else{
			user_register_datain(uh, typein_username, typein_password);
		}
	}
}

int librarianCLI(){
	printf("\nin librarian\n");
	return 0;
}

int userCLI(){
	printf("\nin user\n");
	return 0;
	
}

int login_or_register(User *uh){
	int i;
	i= initial_userlist(uh);
	if(i==-1){
		return -1;
	}
	else if(i==0){
		first_register(uh);
		initial_userlist(uh);
	}
	int j;
	char *str=NULL;
	str=(char*)malloc(100*sizeof(char));
	while(1){
		printf("Please login or register:\n");
		printf("1) Login\n");
		printf("2) Register an account\n");
		printf("3) Quit\n");
		printf("4) List users\n");
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
			else if(strcmp(str,"4\n")==0){
				list_users(uh);
			}
			else{
				printf("\ninvalid choose.\n");
			}
		}
	}
}

