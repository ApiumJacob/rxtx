all: loopback rx tx

serial.o: serial.c
	gcc -c serial.c -o serial.o

loopback.o: loopback.c
	gcc -c loopback.c -o loopback.o

rx.o: rx.c
	gcc -c rx.c -o rx.o

tx.o: tx.c
	gcc -c tx.c -o tx.o

loopback: loopback.o serial.o
	gcc loopback.o serial.o -o loopback

rx: rx.o serial.o
	gcc rx.o serial.o -o rx

tx: tx.o serial.o
	gcc tx.o serial.o -o tx

run: loopback
	./loopback

clean:
	rm *.o loopback rx tx

