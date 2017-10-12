ltauth: auth.o main.o isconnect.o ip.o
	$(CC) $(LDFLAGS) auth.o main.o isconnect.o ip.o -o ltauth  

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

auth.o: auth.c  
	$(CC) $(CFLAGS) -c auth.c  

isconnect.o: isconnect.c
	$(CC) $(CFLAGS) -c isconnect.c

ip.o: ip.c
	$(CC) $(CFLAGS) -c ip.c

# remove object files and executable when user executes "make clean"  
clean:  
	rm *.o ltauth  
