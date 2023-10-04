#include <stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<time.h>

struct vecfloat {
  int nbele;
  float * v;
} ;
typedef struct vecfloat vec_t;

vec_t creeretremplir (int nb);
vec_t inserev (vec_t lr, vec_t aplacer);
vec_t triiv (vec_t l);
vec_t bullv (vec_t l);


struct cellfloat {
  float v;
  struct cellfloat * nxt;
} ;
typedef struct cellfloat cellfloat_t;
typedef struct cellfloat * liste;

liste creer (int nb);
void affliste (liste l);
liste insere (liste lr, liste aplacer);
liste trii (liste l);
liste bull (liste l);

int main (int argc, char ** argv) {
	int n, i;
	liste ll, lt;
	vec_t vec, vect;
	clock_t td, ta;
	n = 100;
	for (i = 0; i < 4-1; i++)
	{
		ll = creer(n);
		lt = NULL;
		td = clock();
		lt = trii (ll);
		ta = clock();
		printf("Tri insertion avec liste\t taille %d\t temps %d\n",n,(int) (ta - td));
		ll = creer(n);
		td = clock();
		lt = bull (ll);
		ta = clock();
		printf("Tri bulles avec liste	\t taille %d\t temps %d\n\n",n,(int) (ta - td));

		vec = creeretremplir(n);
		lt = NULL;
		td = clock();
		vect = triiv (vec);
		ta = clock();
		printf("Tri insertion avec vec	\t taille %d\t temps %d\n",n,(int) (ta - td));
		vec = creeretremplir(n);
		td = clock();
		vect = bullv (vec);
		ta = clock();
		printf("Tri bulles avec vec	\t taille %d\t temps %d\n\n",n,(int) (ta - td));

		n *= 10;
	}
	
}


vec_t creeretremplir (int nb) {
  vec_t w;
  int i;
  float x, y, z, *pt;
  if (nb < 2)
	nb = 10;
  w.nbele = nb;
  w.v = (float *) malloc (nb * sizeof(float));
  assert(w.v);
  x = 1.0;
  y = 0.13;
  z = 0.021;
  pt = w.v;
  for (i = 0; i < nb; i++) {
	*pt++ = x;
	x += y;
	y += z;
	if (x > 1.5) {
	  x -= 1.01;
	}
	if (x < 0.5) {
	  x += 0.499;
	}
	if (y > 1.) {
	  y = y - 1.01;
	}
	if (x < 0.5) {
	  y += 0.5001;
	}
  }
  return w;
}

liste creer (int nb) {
  liste tete, crt;
  int i;
  float x, y, z;
  if (nb < 2)
	nb = 10;
  tete = NULL;
  x = 1.0;
  y = 0.13;
  z = 0.021;
  for (i = 0; i < nb; i++) {
    crt = malloc (sizeof (cellfloat_t));
    assert (crt);
    crt->v   = x;
    crt->nxt = tete;
    tete     = crt;
    x += y;
    y += z;
    if (x > 1.5) {
      x -= 1.01;
    }
    if (x < 0.5) {
      x += 0.499;
    }
    if (y > 1.) {
      y = y - 1.01;
    }
    if (x < 0.5) {
      y += 0.5001;
    }
  }
  return tete;
}

void affliste (liste l)  {
  while (l) {
    printf("%f \t", l->v);
    l = l->nxt;
  }
  printf("\n");
}

liste insere (liste lr, liste aplacer) {
  liste crt, pred;
  if (! lr)
    return aplacer;
  if (lr->v > aplacer->v) {
    aplacer->nxt = lr;
    return aplacer;
  }
  crt  = lr->nxt;
  pred = lr;
  while (crt) {
    if (crt->v <= aplacer->v) {
      pred = crt;
      crt = crt->nxt;
    }
    else {
      break;
    }
  }
  aplacer->nxt = crt;
  pred->nxt = aplacer;
  return lr;
}

liste trii (liste l) {
  liste res, amettre;
  res = NULL;
  while (l) {
    amettre = l;
    l = l->nxt;
    amettre->nxt = NULL;
    res = insere(res, amettre);
  }
  return res;
}

liste bull (liste l) {
  liste crt, suiv, prec;
  int flag;
  if (! l || ! (l->nxt))
    return l;
  flag = 1;
  while (flag) {
    crt  = l->nxt;
    prec = l;
    flag = 0;
    //    affliste(l);
    if (prec->v > crt->v) {
      /* intervertir les deux premiers */
      prec->nxt = crt->nxt;
      crt->nxt = prec;
      l = crt;
      crt  = l->nxt;
      prec = l;
      flag = 1;
    }
    suiv = crt->nxt;
    while (suiv) {
      if (suiv->v < crt->v) {
	prec->nxt = suiv;
	crt->nxt  = suiv->nxt;
	suiv->nxt = crt;
	crt = suiv;
	suiv = crt->nxt;
	flag = 1;
      }
      prec = crt;
      crt = suiv;
      suiv = suiv->nxt;
    }
  }
  return l;
}

vec_t insere (vec_t lr, vec_t aplacer){

}
vec_t trii (vec_t l){

}
vec_t bull (vec_t l){

}