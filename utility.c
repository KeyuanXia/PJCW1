#include<stdio.h>

char checklength(int j){
	char typein[j];
	int i=0;
		while((ch = getchar()) != '\n'){
			if(i == j){    									//maximum length of user name is 15 charaters
				return "tl";
				}
			typein[i] = ch;
			i++;
			}
	if(i==0){
		return "ts";
	}
	return typein;
}
