#ifndef __UTILITY_H__
#define __UTILITY_H__

int get_length(char str[]);

int store_user_data(FILE *fr, User *uh);

void clear_n(char *str);

int load_user_data(FILE *fr, User *uh);

int user_register_datain(User *uh, char *username, char *password);

int check_usernam(User *uh, char *str);

int check_password(User *uh, char *str, int id);

int list_users(User *uh);

#endif
