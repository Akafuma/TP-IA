/*
 * Codage interne du CSP
 * vars : 0 ... n - 1 ( entiers )
 * valeurs : 0 ... m - 1 ( entiers)
 * 
 * ___________________________________________________________
 * Codage des domaines : ( matrice nxm : variables x valeurs)
 * 
 * ligne : variables
 * si une valeur appartient au domaine : t[variable][valeur] = 1, sinon 0
 * 
 * __________________________________________________________
 * Codage des contraintes et relations
 * 
 * matrice des contraintes C (nxn : variables x variables)
 * C[i][j] = null s'il n'y a pas de contraintes entre i et j
 * sinon pointeur vers la table de tout les tuples permis par la contrainte
 * 
 * table : matrice (mxm)
 * table[i][j] = 1 si le tuple (i,j) est compatible avec la contrainte,
 * 0 sinon
 * 
 * Affecter courate gerer par une pile
 */
