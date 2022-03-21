#ifndef __UTILITY_H__
#define __UTILITY_H__

int get_length(char str[]);

int store_user_data(FILE *fr, User *uh);

int first_register(User *uh);

void clear_n(char *str);

int load_user_data(FILE *fr, User *uh);

int list_users(User *uh);

#endif
