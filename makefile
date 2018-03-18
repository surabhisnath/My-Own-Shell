all:
	gcc -o ls ls.c -w
	gcc -o cat cat.c -w
	gcc -o mkdir mkdir.c -w
	gcc -o rm rm.c -w
	gcc -o date date.c -w
	gcc -o shell Assignment0.c -w

clean:
	rm ls cat mkdir rm date shell 
