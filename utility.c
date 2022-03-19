#include<stdio.h>

int get_length(char str[]){
	char *p = str;
	int count = 0;
	while (*p++ != '\n')
	{
		count++;
	}
	return count;
}

