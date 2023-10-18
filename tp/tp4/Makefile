NomPrenom = Bastien_Capiaux_21002589
version = V_1
tp = TP4

prog: $(tp).o
	gcc -o prog $(tp).o

$(tp).o: $(tp).c
	gcc -c -Wextra -Wall $(tp).c

clean: 
	rm *.o prog

dist: 
	tar -czvf $(tp)_$(NomPrenom)_$(version).tar.gz $(tp).c makefile