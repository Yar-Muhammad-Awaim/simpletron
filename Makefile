simple: simple.c libutil.a  
	gcc simple.c -L. -lutil -o simple

libutil.a: util.o 
	ar rcs libutil.a util.o 

util.o: util.c 
	gcc -c util.c

clean:
	rm simple libutil.a util.o  
