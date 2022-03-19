#include<stdio.h>

#include"book_management.h"
#include"User_management.h" 
int main(){
	int usertype;
	User *uh;
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
