# Version du programme et NomPrenom
version = V.1
NomPrenom = Bastien_Capiaux_21002589
# Nom du fichier exécutable
executable = prog
# Nom du fichier source principal
main = main
# Répertoires pour les fichiers d'en-tête et sources
header_dir = ./headers
source_dir = ./sources
# Liste des fichiers d'en-tête et sources
headers = $(wildcard $(header_dir)/*.h)
sources = $(wildcard $(source_dir)/*.c)
# Options du compilateur
CFLAGS = -Wextra -Wall -I$(header_dir)

# Règle par défaut pour la construction du programme exécutable
$(executable): $(main).o parenthese.o catalan.o
	gcc -o $@ $^
# Règle pour la compilation du fichier source principal
$(main).o: $(main).c $(headers)
	gcc -c $(CFLAGS) $<
# Règles pour la compilation des autres fichiers source
parenthese.o: $(source_dir)/parenthese.c $(headers)
	gcc -c $(CFLAGS) $<
catalan.o: $(source_dir)/catalan.c $(headers)
	gcc -c $(CFLAGS) $<
# Règle pour le nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f *.o $(executable)
# Règle pour créer une archive du projet
dist:
	tar -czvf $(main)_$(NomPrenom)_$(version).tar.gz $(main).c $(sources) $(headers) makefile readme
