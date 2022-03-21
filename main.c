#include<stdio.h>
#include<stdlib.h>

#include"book_management.h"
#include"User_management.h" 
int main(){
	int usertype;
	User *uh=(User *)malloc(sizeof(User));
	Book *bh;
	BookList *blh;
	while(1){
		usertype=login_or_register(uh);
		if(usertype==1){
			librarianCLI();
		}
		else if(usertype==2){
			userCLI();
		}
		else if(usertype==-1){
			return 0;
		}
	}
}
