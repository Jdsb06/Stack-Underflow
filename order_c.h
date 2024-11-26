#ifndef ORDER_C_H
#define ORDER_C_H

#include <mysql/mysql.h>

void manageOrders_c(MYSQL *conn);
void viewCustomerOrders(MYSQL *conn);
void completeCustomerOrder(MYSQL *conn);


#endif
