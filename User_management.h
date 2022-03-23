#ifndef __USERMANAGEMENT_H__
#define __USERMANAGEMENT_H__



typedef struct _User{
	int Id;
	char *username;
	char *password;
	int type;
	struct _User *last;
	struct _User *next;
}User;

int initial_userlist(User *h);

int first_register(User *uh);

User *user_login(User *uh);

int user_register(User *uh);

User *login_or_register(User *uh);

int librarianCLI();

int userCLI();

#endif
