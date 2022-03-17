typedef struct _User{
	int Id;
	char *username;
	char *password;
	int type;
	struct _User *last;
	struct _User *next;
}User;
