#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include<sys/io.h>
#include"User_management.h" 
#include"utility.h"


int initial_userlist(User *h){
	h->Id=0;
	FILE *fr=fopen("Userdata/Userlist.txt","r");
	switch(load_user_data(fr, h)){
		case -1:printf("\n!!!Lose the Userdata, the initial of userdata failed.!!!\n");return 0;
		case 0:printf("\n!!!User list is NULL, the initial of user data failed!!!\n");return 0;
		default:break;
	}
	fclose(fr);
	printf("\n***Userdata insert sucessfully!***\n");
	return 1;
}

int first_register(User *uh){
	char *typein_username, *typein_password;
	User *q;
	q=(User *)malloc(sizeof(User));
	unsigned long tl;
	typein_username=(char*)malloc(100*sizeof(char));
	typein_password=(char*)malloc(100*sizeof(char));
	printf("please register the first user account, this user will be Librarian.\n\n");
	while(1){
		printf("First_Register\n");
		printf("\tusername(less than 16 characters):");
		fgets(typein_username,20,stdin);
		clear_n(typein_username);
		fflush(stdin);
		tl=strlen(typein_username);
		if(tl>=16){
				printf("\n!Your username is too long!\n");
				printf("Please try again or enter 'q' to back to the login and register page.\n");
		}
		else if(strcmp(typein_username, "q")==0){
			return -1;
		}
		else if (tl == 0) {
            printf("\nThe username can not be none.\n");
            printf("Please try again or enter 'q' to leave the program.\n");
        } else break;
	}
	while(1){
		printf("\tpassword(less than 16 characters):");
		fgets(typein_password,20,stdin);
		clear_n(typein_password);
		fflush(stdin);
		tl=strlen(typein_password);
		if(tl>=16){
			printf("\n!Your password is too long!\n");
			printf("Please try again or enter 'q' to back to the login and register page.\n");
		}
		else if(strcmp(typein_password, "q")==0){
			return -1;
		}
		else if(tl==0){
			printf("\nThe password can not be none.\n");
			printf("Please try again or enter 'q' to leave the program.\n");
		}
		else{

				q->type=1;
				q->last=uh;
				q->next=NULL;
				q->Id=1;

				q->username= strdpp(typein_username);
				q->password= strdpp(typein_password);

				uh->next=q;
            list_users(uh);
				if(access("./Userdata", 0)==-1){

					CreateFolder("Userdata");
				}

				FILE *fr=fopen("./Userdata/Userlist.txt","w");

				store_user_data(fr, uh);

				fclose(fr);

				printf("\n***first user register successfully!***\n");

				return 1;
		}
	}
}

User *user_login(User *uh){
	User *user, *q=(User *)malloc(sizeof(User));
	char *str;
	unsigned long tl;
	str=(char*)malloc(100*sizeof(char));
	q->type=-1;
	while(1){
		printf("Login:\n"); 
		printf("\tusername(less than 16 characters):");
		fgets(str,91,stdin);
		clear_n(str);
		fflush(stdin);
		tl = strlen(str);
		if(tl>=16){
			printf("\n!Your username is too long!\n");
			printf("Please try again or enter 'q' to back to the login and register page.\n");
			continue;
		}
		else if(strcmp(str, "q")==0){
			return q;
		}
		else if(tl==0){
			printf("\n!Your username cannot be empty!\n");
			continue;
		}
		user = check_usernam(uh,str);
		
		if(user->type==-1){
			printf("\n!The username has not been created before, please check your username.!\n");
			printf("Please try again or enter 'q' to back to the login and register page.\n");
		}
		else{
			break;
		}
	}
	while(1){
		printf("\tpassword(less than 16 characters):");
		fgets(str,20,stdin);
		clear_n(str);
		fflush(stdin);
		tl = strlen(str);
		if(tl>=16){
			printf("\n!Your password is too long!\n");
			printf("Please try again or enter 'q' to back to the login and register page.\n");
		}
		else if(strcmp(str, "q")==0){
			return q;
		}
		if(check_passwor(user, str)==-1){
			printf("\n!Wrong password!\n");
			printf("Please try again or enter 'q' to back to the login and register page.\n");
		}
		else if(check_passwor(user, str)==1||check_passwor(user, str)==2){
			
			return user;
		}
	}
}

int user_register(User *uh){
	char *typein_username, *typein_password; 
	unsigned long tl;
	typein_username=(char*)malloc(20*sizeof(char));
	typein_password=(char*)malloc(16*sizeof(char));
	while(1){
		printf("Register\n");
		printf("\tusername(less than 16 characters):");
		fgets(typein_username,20,stdin);
		clear_n(typein_username);
		fflush(stdin);
		tl=strlen(typein_username);
		if(tl>=16){
				printf("\n!Your username is too long!\n");
				printf("Please try again or enter 'q' to back to the login and register page.\n");
		}
		else if(strcmp(typein_username, "q")==0){
			return 0;
		}
		else if(check_usernam(uh, typein_username)->type!=-1){
			printf("The username is already exist, please choose another.\n");
		}
		else{
			break;
		}
	}
	while(1){
		printf("\tpassword(less than 16 characters):");
		fgets(typein_password,16,stdin);
		clear_n(typein_password);
		fflush(stdin);
		tl=strlen(typein_password);
		if(tl>=90){
			printf("\n!Your password is too long!\n");
			printf("Please try again or enter 'q' to back to the login and register page.\n");
		}
		else if(strcmp(typein_password, "q")==0){
			return 0;
		}
		else{
			user_register_datain(uh, typein_username, typein_password);
			return 1; 
		}
	}
}

User *login_or_register(User *uh){
	int i;
	User *q=(User *)malloc(sizeof(User));
    q->type=-1;
	i= initial_userlist(uh);
	if(i==0){
		if(-1==first_register(uh)){
            return q;
        }
		initial_userlist(uh);
	}
	User *user;
	char *str=NULL;
	str=(char*)malloc(100*sizeof(char));
	while(1){
		printf("\nPlease login or register:\n");
		printf("1) Login\n");
		printf("2) Register an account\n");
		printf("3) quit\n");
		printf("4) List users\n");
		printf("choice:");
		fgets(str,10,stdin);
		clear_n(str);
		fflush(stdin);
		if(strlen(str)==0){
			printf("You has not choose yet, please try again.\n");
		}
		else if(strlen(str)>1){
			printf("Your choice is too long, please try again.\n");
		}
		else{
			if(strcmp(str,"1")==0){			///Login
				user=user_login(uh);
				
				if(user->type==1||user->type==2){
					
					return user;
				}
			}
			else if(strcmp(str,"2")==0){	///Register
				user_register(uh);
			}
			else if(strcmp(str,"3")==0){	///q
				return q;
			}
			else if(strcmp(str,"4")==0){
				list_users(uh);
			}
			else{
				printf("\ninvalid choose.\n");
			}
		}
	}
}

