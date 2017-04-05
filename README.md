Makefile :

make all génére l'exécutable demo

make all OPTS='-DPRINT_SOL -DPRINT_NOEUD -DPRINT_CONTRAINTES'
  - L'option -DPRINT_SOL affiche les solutions trouvés pendant une recherche
  - L'option -DPRINT_NOEUD affiche le nombre de nœuds visités
  - L'option -DPRINT_CONTRAINTES affiche le nombre de contraintes traitées
  - Pour changer d'options : make clean puis recompiler
