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
vec_t inserev (vec_t lr);
vec_t bullev (vec_t lr);
void quickSort(float arr[], int low, int high);
int partition(float arr[], int low, int high);
vec_t qsvec(vec_t lr);
vec_t selectionSortv(vec_t lr) {
    int i, j, min_idx, n;
    n = lr.nbele;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (lr.v[j] < lr.v[min_idx]) {
                min_idx = j;
            }
        }
        // Échanger l'élément minimum trouvé avec l'élément actuel de l'itération
        float temp = lr.v[min_idx];
        lr.v[min_idx] = lr.v[i];
        lr.v[i] = temp;
    }
    return lr;
}



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
liste partitionL(liste l, liste* gauche, liste* droite);
liste qs(liste l);
liste selectionSort(liste l);

int main (int argc, char ** argv) {
	int n, i;
	liste ll, lt;
	vec_t vec, vect;
	clock_t td, ta;
	n = 100;
	for (i = 0; i < 4; i++)
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
		printf("Tri bulles avec liste	\t taille %d\t temps %d\n",n,(int) (ta - td));
    ll = creer(n);
		td = clock();
		lt = selectionSort(ll);
		ta = clock();
		printf("Tri selection avec liste\t taille %d\t temps %d\n",n,(int) (ta - td));
    ll = creer(n);
		td = clock();
		lt = qs(ll);
		ta = clock();
		printf("Quicksort avec liste	\t taille %d\t temps %d\n\n",n,(int) (ta - td));

		vec = creeretremplir(n);
		lt = NULL;
		td = clock();
		vect = inserev(vec);
		ta = clock();
		printf("Tri insertion avec vec	\t taille %d\t temps %d\n",n,(int) (ta - td));
		vec = creeretremplir(n);
		td = clock();
		vect = bullev (vec);
		ta = clock();
		printf("Tri bulles avec vec	\t taille %d\t temps %d\n",n,(int) (ta - td));
    vec = creeretremplir(n);
		td = clock();
    vect = selectionSortv(vec);
		ta = clock();
		printf("Tri selection avec vec	\t taille %d\t temps %d\n",n,(int) (ta - td));
    vec = creeretremplir(n);
		td = clock();
    vect = qsvec(vec);
		ta = clock();
		printf("Quicksort avec vec	\t taille %d\t temps %d\n\n",n,(int) (ta - td));
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
    printf("%f, ", l->v);
    l = l->nxt;
  }
  printf("\n\n");
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
liste partitionL(liste l, liste* gauche, liste* droite) {
	if (!l || !l->nxt) {
		*gauche = l;
		*droite = NULL;
		return l;
	}
	liste pivot = l;
	l = l->nxt;
	pivot->nxt = NULL;
	liste gauche_head = NULL, gauche_tail = NULL;
	liste droite_head = NULL, droite_tail = NULL;
	while (l) {
		liste suivant = l->nxt;
		if (l->v <= pivot->v) {
			if (!gauche_head) {
				gauche_head = l;
				gauche_tail = l;
			} else {
				gauche_tail->nxt = l;
				gauche_tail = l;
			}
		} else {
			if (!droite_head) {
				droite_head = l;
				droite_tail = l;
			} else {
				droite_tail->nxt = l;
				droite_tail = l;
			}
		}
		l = suivant;
	}
	if (gauche_tail) {
		gauche_tail->nxt = NULL;
	}
	if (droite_tail) {
		droite_tail->nxt = NULL;
	}
	*gauche = gauche_head;
	*droite = droite_head;
	return pivot;
}

liste qs(liste l) {
    if (!l || !l->nxt) {
        return l;
    }

    liste gauche = NULL, droite = NULL;
    liste pivot = partitionL(l, &gauche, &droite);

    gauche = qs(gauche);
    droite = qs(droite);

    if (gauche) {
        liste crt = gauche;
        while (crt->nxt) {
            crt = crt->nxt;
        }
        crt->nxt = pivot;
    } else {
        gauche = pivot;
    }

    pivot->nxt = droite;

    return gauche;
}   

liste selectionSort(liste l) {
  if (!l || !l->nxt) {
    return l;  // Already sorted or empty list
  }

  liste current = l;
  liste sorted = NULL;

  while (current) {
    liste minNode = current;
    liste minPrev = NULL;

    // Find the minimum node in the remaining unsorted part of the list
    liste temp = current;
    while (temp->nxt) {
      if (temp->nxt->v < minNode->v) {
        minNode = temp->nxt;
        minPrev = temp;
      }
      temp = temp->nxt;
    }

    // Remove the minimum node from the unsorted list
    if (minPrev) {
      minPrev->nxt = minNode->nxt;
    } else {
      current = current->nxt;
    }

    // Add the minimum node to the sorted list
    minNode->nxt = sorted;
    sorted = minNode;
  }

  return sorted;
}

vec_t inserev(vec_t w) {
    int i, j;
    float temp;
    for (i = 1; i < w.nbele; i++) {
        temp = w.v[i];
        j = i - 1;
        while (j >= 0 && w.v[j] > temp) {
            w.v[j + 1] = w.v[j];
            j--;
        }
        w.v[j + 1] = temp;
    }
    return w;
}

vec_t bullev(vec_t w) {
    int n = w.nbele;
    int i, j;
    float temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (w.v[j] > w.v[j + 1]) {
                temp = w.v[j];
                w.v[j] = w.v[j + 1];
                w.v[j + 1] = temp;
            }
        }
    }
    return w;
}



int partition(float arr[], int low, int high) {
    float pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            float temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    float temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return (i + 1);
}

void quickSort(float arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

vec_t qsvec(vec_t lr) {
    quickSort(lr.v, 0, lr.nbele - 1);
    return lr;
}

