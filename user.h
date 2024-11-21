#ifndef USER_H
#define USER_H

#include <mysql/mysql.h>

void userMenu(MYSQL *conn);
int signIn(MYSQL *conn);
void signUp(MYSQL *conn);

#endif
