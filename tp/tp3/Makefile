NomPrenom = Bastien_Capiaux_21002589
version = V.1
tp = TP3

prog: $(tp).o
	gcc -o prog $(tp).o

TP$(tp).o: $(tp).c
	gcc -c -Wextra -Wall $(tp).c

clean: 
	rm *.o prog

dist: 
	tar -czvf $(tp)_$(NomPrenom)_$(version).tar.gz $(tp).c makefile