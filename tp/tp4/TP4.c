/* Arbres binaires tout simplement */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(i, j) (((i) > (j)) ? (i) : (j))

struct noeud {
  int num;
  float val;
  struct noeud * sg;
  struct noeud * sd;
} ;

typedef struct noeud noeud;
typedef struct noeud * arbre;

void afficharbre (arbre) ;
void blancs (int);
void voisarbre (arbre, int);
arbre ajout (arbre, int, float);
arbre creation (int);

/*----------------------------------------------------------------*/
// arbre V1 
int compte_n(arbre);
int is_in_arbre (arbre, float);
arbre is_noeud_in_arbre (arbre, float);
int profondeur_noeud_in_arbre(arbre, arbre);
void range_arbre(arbre*);
/*----------------------------------------------------------------*/
// arbre V2


int main () {
  int n, v1, v2;
  arbre a, b, c;
  v1 = 1;
  v2 = 1;
  n = 20;
  a = creation (n);
  afficharbre (a);
  printf("\n\n");
  voisarbre (a,0);

  /*---------------------------------------------------------------*/  
  // arbre V1
  if (v1){
    printf("\n\nNombre de noeud : %d\n",compte_n (a));

    if (is_in_arbre(a, 1.2f)) printf("La valeur %f est dans l'arbre\n",1.2f);
    else printf("La valeur %f n'est pas dans l'arbre\n",1.2f);
    printf("%d\n",is_in_arbre(a, 1.2f));

    c = is_noeud_in_arbre(a, 1.2f);
    if (c) printf("num : %d / val : %f\n", c->num, c->val);
    else printf("La valeur 1.2f n'a pas été trouvée dans l'arbre.\n");

    printf("Profondeur de c : %d\n", profondeur_noeud_in_arbre(a, c));

    b = a;

    range_arbre(&b);
    afficharbre (b);
    printf("\n\n");
    voisarbre (b,0);

    c = is_noeud_in_arbre(b, 1.2f);
    if (c) printf("num : %d / val : %f\n", c->num, c->val);
    else printf("La valeur 1.2f n'a pas été trouvée dans l'arbre.\n");

    printf("Profondeur de c : %d\n", profondeur_noeud_in_arbre(b, c));
  } 
  /*----------------------------------------------------------------*/
  // arbre V2
  if (v2){
    
  }
  


}

arbre ajout (arbre a, int v, float x) {
  arbre new;
  int rande;
  if (! a) {
	new = (arbre) malloc (sizeof (noeud));
	new->num = v;
	new->val = x;
	new->sg = (arbre) 0;
	new->sd = (arbre) 0;
	return new;
  }
  rande = rand ();
  printf(" insere %d en %d avec %2d\n", v, a->num, rande %10);
  if (rande & 0x01) {
	/* on le met à gauche*/
	if (! (a->sg)) {
	  /* s’il ny a pas de fils gauche */
	  a->sg = (arbre) malloc (sizeof (noeud));
	  a->sg->num = v;
	  a->sg->val = x;
	  a->sg->sg = (arbre) 0;
	  a->sg->sd = (arbre) 0;
	  return a;
	}
	a->sg = ajout(a->sg, v, x);
	return a;
  }
  /* on le met donc a droite*/
  if (! (a->sd)) {
	/* s’il ny a pas de fils droit */
	a->sd = (arbre) malloc (sizeof (noeud));
	a->sd->num = v;
	a->sd->val = x;
	a->sd->sg = (arbre) 0;
	a->sd->sd = (arbre) 0;
	return a;
  }
  a->sd = ajout(a->sd, v, x);
  return a;
}
arbre creation (int n) {
  arbre a;
  float x, y;
  x = 1.5;
  y = 0.21;
  a = (arbre) 0;
  /*
  srand(time(NULL));
  */
  while (n--) {
	a = ajout (a, n, x);
	printf("\n");
	x += y;
	y += 0.06;
	if (x > 3.0 || x < -2.0) {
	  y = - y;
	}
  }
  return a;
}
void afficharbre (arbre a) {
  if (a) {
	afficharbre (a->sg);
	printf("%d %3.2f ", a->num, a->val);
	afficharbre (a->sd);
  }
}
void blancs (int n) {
  while (n--)
	printf("  ");
}
void voisarbre (arbre a, int nbb) {
  if (a) {
	voisarbre (a->sg, nbb + 1);
	blancs (nbb);
	printf(" %2d %d %3.2f\n", nbb, a->num, a->val);
	voisarbre (a->sd, nbb + 1);
  }
}

/*----------------------------------------------------------------*/
// arbre V1 

int compte_n(arbre a){
  int n = 0;
  if(a){
    n++;
    return n + compte_n(a->sg) + compte_n(a->sd);
  }
  else return n;
}

int is_in_arbre (arbre a, float val) {
  if(a){
    if (a->val == val) return 1;
    else {
      return is_in_arbre(a->sg, val) || is_in_arbre(a->sd, val);
    }
  }
  return 0;
}

arbre is_noeud_in_arbre (arbre a, float val) {
  arbre res_g, res_d;
  if(a){
    if (a->val == val) {
      printf("a->val = %f\n", a->val);
      return a;
    }
    else {
      res_g = is_noeud_in_arbre(a->sg, val);
      res_d = is_noeud_in_arbre(a->sd, val);
      if (res_g) return res_g;
      else if (res_d) return res_d;
    }
  }
  return NULL;
}

int profondeur_noeud_in_arbre(arbre a, arbre noeud){
  int res = 0;
  if (a)
  {
    if (a == noeud) return res;
    else return 1 + MAX(profondeur_noeud_in_arbre(a->sg, noeud), profondeur_noeud_in_arbre(a->sd, noeud));
  }
  return 0;
}

void range_arbre(arbre* a){
  arbre temp;
  if (*a){
    // si le sous-arbre gauche est strictement plus petit que le sous-arbre droit
    if ((*a)->sg && (*a)->sd && (*a)->sg->val < (*a)->sd->val){
      temp = (*a)->sg;
      (*a)->sg = (*a)->sd;
      (*a)->sd = temp;
    }
    if ((*a)->sg) range_arbre(&((*a)->sg));
    if ((*a)->sd) range_arbre(&((*a)->sd));
  }
}