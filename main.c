#include<stdio.h>
#include<stdlib.h>

#include"book_management.h"
#include"User_management.h" 
#include"librarian.h"
#include"User.h"

int main(){
	int check;
	User *user;
	User *uh=(User *)malloc(sizeof(User));
	Book *bh=(Book *)malloc(sizeof(Book));
	bh->next=NULL;
	bh->id=0;
	while(1){
		user=login_or_register(uh);
		if(user->type==1){
			check=librarianCLI(user, bh, uh);
		}
		else if(user->type==2){
			check=userCLI();
		}
		else if(user->type==-1){
			printf("\nquit\n");
			return 0;
		}
		if(check==-1){
			return 0;
		}
	}
}
