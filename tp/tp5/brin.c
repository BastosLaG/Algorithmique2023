#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

typedef short unsigned Shu;

struct strand {
  Shu node; // short unsign = node 
  short next; // short = next brin
};
typedef struct strand strand;

struct strandgraph {
  Shu nbs; // nombre sommet total du graphe
  Shu nbstr; // nombre arrete total du graphe 
  
  short * node; /*first strand*/
  strand * nxt; /*node and next strand*/
};
typedef struct strandgraph strgr;

strgr creerstrandgraphe(int nbs){
  Shu i, j, max, num;
  float v, taux;
  strgr g;
  g.nbs = nbs;
  max = nbs;
  // taux = 25.0;
  // num = nbs / 10;
  // while (num > 1) {
	// num /= 5;
	// taux /= 3.0;
  // }
  // taux /= 100.0;
  // printf("taux %g\n", taux);
  g.node = (short *) malloc (max * sizeof(short));
  assert(g.node);
  g.nxt = (strand *) malloc (max * sizeof(strand));
  assert(g.nxt);
  memset(g.node, 0, max);
  // srand(time(NULL));
  for (num = 0, i = 0; i < nbs; i++)
	for (j = 0; j < nbs; j++) {
	  v = (float) rand () / RAND_MAX;
	  g.node[num++] = v < taux ? (Shu) (v * 1000.) : 0;
	}
  return g;
}

void voirgraf (strgr g) {
  Shu i, j, nb, num;
  nb = g.nbs;
  printf("Graphe\n");
  for (i = 0, num = 0; i < nb; i++) {
	for (j = 0; j < nb; j++)
	  printf("%c ", g.node[num++]? '1' : ' ');
	printf("\n");
  }
}

int main(){
  strgr g;
  g = creerstrandgraphe(20);
  // voirgraf(g);
  return 0;
}