#include<stdio.h>
#include<stdlib.h>

#include"book_management.h"
#include"User_management.h" 
#include"librarian.h"
int main(){
	User *user;
	User *uh=(User *)malloc(sizeof(User));
	Book *bh=(Book *)malloc(sizeof(Book));
	while(1){
		user=login_or_register(uh);
		if(user->type==1){
			librarianCLI(user, bh);
		}
		else if(user->type==2){
			userCLI();
		}
		else if(user->type==-1){
			printf("\n\nquit\n\n");
			return 0;
		}
	}
}
