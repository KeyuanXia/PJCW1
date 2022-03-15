typedef struct _User{
	int Id;
	char *username;
	char *password;
	struct _User *next;
}User;
