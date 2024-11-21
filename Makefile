CC = gcc
CFLAGS = -Wall -Wextra -I/usr/include/mysql
LDFLAGS = -lmysqlclient

all: wms

wms: main.o master.o order_c.o transaction.o user.o order_p.o statistics.o
	$(CC) $(CFLAGS) -o wms main.o master.o order_c.o transaction.o user.o order_p.o statistics.o $(LDFLAGS)

main.o: main.c master.h order_p.h transaction.h user.h order_c.h statistics.h
	$(CC) $(CFLAGS) -c main.c

master.o: master.c master.h
	$(CC) $(CFLAGS) -c master.c

order_c.o: order_c.c order_c.h
	$(CC) $(CFLAGS) -c order_c.c

order_p.o: order_p.c order_p.h
	$(CC) $(CFLAGS) -c order_p.c
statistics.o: statistics.c statistics.h
	$(CC) $(CFLAGS) -c statistics.c

transaction.o: transaction.c transaction.h
	$(CC) $(CFLAGS) -c transaction.c

user.o: user.c user.h
	$(CC) $(CFLAGS) -c user.c

clean:
	rm -f *.o wms
