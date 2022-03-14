#include<stdio.h>

void main(){
	int usertype;
	while(1){
		usertype=login();
		if(usertype==0){
			Superlibrarian();
		}
		else if(usertype==1){
			librarian();
		}
		else if(usertype==2){
			user();
		}
	}
}
