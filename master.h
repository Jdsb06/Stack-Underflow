#ifndef MASTER_H
#define MASTER_H

#include <mysql/mysql.h>

void manageItems(MYSQL *conn);
void addItem(MYSQL *conn);
void displayItems(MYSQL *conn);
void updateItem(MYSQL *conn);

#endif
