#include<stdio.h>

void main(){
	int usertype;
	User *uh;
	Book *bh;
	BookList *blh;
	
	while(1){
		usertype=login_or_register();
		if(usertype==1){
			librarianCLI();
		}
		else if(usertype==2){
			userCLI();
		}
		else if(usertype==-1){
			exist(1);
		}
	}
}
