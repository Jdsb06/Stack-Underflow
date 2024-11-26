#ifndef ORDER_H
#define ORDER_H

#include <mysql/mysql.h>

void manageOrders_p(MYSQL *conn);
void addPurchaseOrder(MYSQL *conn);
void viewPurchaseOrders(MYSQL *conn);
void completePurchaseOrder(MYSQL *conn);

#endif
