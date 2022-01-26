all: loopback

serial.o: serial.c
	gcc -c serial.c -o serial.o

loopback.o: loopback.c
	gcc -c loopback.c -o loopback.o

loopback: loopback.o serial.o
	gcc loopback.o serial.o -o loopback

run: loopback
	./loopback

clean:
	rm *.o
	rm loopback

