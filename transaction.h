#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <mysql/mysql.h>

void manageTransactions(MYSQL *conn);

#endif
