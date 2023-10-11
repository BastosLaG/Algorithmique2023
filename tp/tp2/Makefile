NomPrenom = Bastien_Capiaux_21002589
version = V.2
tp = TP2

prog: $(tp).o
	gcc -o prog $(tp).o

TP$(tp).o: $(tp).c
	gcc -c -Wextra -Wall -fsanitize $(tp).c

clean: 
	rm *.o prog

dist: 
	tar -czvf $(tp)_$(NomPrenom)_$(version).tar.gz $(tp).c makefile