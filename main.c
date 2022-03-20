#include<stdio.h>

<<<<<<< HEAD
#include"book_management.h"
#include"User_management.h" 
int main(){
=======
void main(){
>>>>>>> d66d14c9459d8da730645a6b733f3ed98c753595
	int usertype;
	User *uh;
	Book *bh;
	BookList *blh;
	
	while(1){
<<<<<<< HEAD
		usertype=login_or_register(uh);
=======
		usertype=login_or_register();
>>>>>>> d66d14c9459d8da730645a6b733f3ed98c753595
		if(usertype==1){
			librarianCLI();
		}
		else if(usertype==2){
			userCLI();
		}
		else if(usertype==-1){
<<<<<<< HEAD
			return 0;
=======
			exist(1);
>>>>>>> d66d14c9459d8da730645a6b733f3ed98c753595
		}
	}
}
