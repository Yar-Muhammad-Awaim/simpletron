simple: simple.c util.c 
	gcc util.c simple.c -o simple

clean:
	rm simple
