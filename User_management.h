#ifndef __USERMANAGEMENT_H__
#define __USERMANAGEMENT_H__

#include"Linklist.h"


typedef struct _User{
	int Id;
	char *username;
	char *password;
	int type;
	struct _User *last;
	struct _User *next;
}User;

int initial_userlist(User *h);

int user_login(User *uh);

int check_usernam(User *uh, char *str);

int check_password(User *uh, char *str, int id);

int user_register_datain(User *uh, char *username, char *password);

int user_register(User *uh);

int login_or_register(User *uh);

int librarianCLI();

int userCLI();

#endif
