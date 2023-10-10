#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<string.h>

#define MAX 2000
typedef unsigned char uchar;
typedef unsigned char monplan [MAX][MAX];

void affiche (int sizex, int sizey, monplan pl);

void droite_triviale (int u, int v, monplan pl);
void droite_triviale_verif (int u, int v, monplan pl);

void droite_br (int u, int v, monplan pl);
void droite_br_verif (int u, int v, monplan pl);

void droite_rvw (int u, int v, monplan pl);
void droite_rvw_verif (int u, int v, monplan pl);

int main (int argc, char ** argv) {
  int sizex, sizey, dx, dy, i, j;
  monplan plan;
  clock_t t0, t1, dt;
  
  dx = 100;
  dy = 100;
  if (argc == 3) {
    dx = atoi (argv[1]);
    dy = atoi (argv[2]);
  }
  if (dx < 0)
    dx = 0 - dx;
  if (dy < 0)
    dy = 0 - dy;
  if (dx < dy) {
    dx += dy;
    dy = dx - dy;
    dx = dx - dy;
  } /* nous restons dans le premier octant */
  if (dx >= MAX)
    dx = MAX - 1;
  if (dy >= MAX)
    dy = MAX - 1;

  memset (plan, ' ', MAX*MAX);
  
  droite_triviale_verif (11, 3, plan);
  printf("Triviale\n");
  affiche (11, 3, plan);
  
  memset (plan, ' ', MAX*MAX);
  
  droite_triviale_verif (24, 10, plan);
  affiche (24, 10, plan);

  memset (plan, ' ', MAX*MAX);

  droite_br_verif (11, 3, plan);
  printf("Bresenham\n");
  affiche (11, 3, plan);

  memset (plan, ' ', MAX*MAX);
  
  droite_br_verif (24, 10, plan);
  affiche (24, 10, plan);
  
  memset (plan, ' ', MAX*MAX);

  droite_rvw_verif (11, 3, plan);
  printf("Rokne\n");
  affiche (11, 3, plan);
  
  memset (plan, ' ', MAX*MAX);

  droite_rvw_verif (24, 10, plan);
  affiche (24, 10, plan);

  t0 = clock();
  for (i = 0; i < dx; i++) {
    for (j = 0; j < dy; j++) {
      droite_triviale (i, j, plan);
    }
  }
  t1 = clock();
  printf("triviale %d\n", (int) (t1 - t0));

  t0 = clock();
  for (i = 0; i < dx; i++) {
    for (j = 0; j < dy; j++) {
      droite_br (i, j, plan);
    }
  }
  t1 = clock();
  printf("Bresenham %d\n", (int) (t1 - t0));

  t0 = clock();
  for (i = 0; i < dx; i++) {
    for (j = 0; j < i; j++) {
      droite_rvw (i, j, plan);
    }
    for (j = 0; j < i; j++) {
      droite_rvw (i, j, plan);
    }
  }
  t1 = clock();
  printf("Rokne %d\n", (int) (t1 - t0));
  

}

void droite_triviale (int u, int v, monplan pl) {
  int x, y;
  float z;
  for (x = 0; x <= u; x++) {
    z = ((float) x * v / u) + 0.5;
    y = (int) z;
  }
}
void droite_triviale_verif (int u, int v, monplan pl) {
  int x, y;
  for (x = 0; x <= u; x++) {
    y = (int) (((float) x * v / u) + 0.5);
    pl [x][y] = '.';
  }
}

void affiche (int sizex, int sizey, monplan pl) {
  int i, j;
  for(j = sizey; j >= 0; j--) {
    for (i = 0; i <= sizex; i++) 
      printf("%c", pl[i][j]);
    printf("\n");
  }
}

void droite_br (int u, int v, monplan pl) {
    /* u est dx, v est dy */
    int x, y, delta, incD, incH;

    incH   = v << 1;
    delta  = incH - u;
    incD   = delta - u;
    for (x = 0, y = 0; x <= u; x++) {
        if (delta > 0) {
            y++;
            delta += incD;
        }
        else {
            delta += incH;
        }
    }
}

void droite_br_verif (int u, int v, monplan pl) {
    /* u est dx, v est dy */
    int x, y, delta, incD, incH;

    incH   = v << 1;
    delta  = incH - u;
    incD   = delta - u;
    for (x = 0, y = 0; x <= u; x++) {
        if (delta > 0) {
            y++;
            delta += incD;
        }
        else {
            delta += incH;
        }
        pl [x][y] = '.';
    }
}

void droite_rvw (int u, int v, monplan pl) {
    int x, y, delta, incD, incH;

    incH   = v << 1;
    delta  = incH - u;
    incD   = delta - u;
    for (x = 0, y = 0; x <= u; x++) {
        if (delta > 0) {
            y++;
            delta += incD;
        }
        else {
            delta += incH;
        }
        delta = 2 * u * y + u - 2 * y * x;
    }
}

void droite_rvw_verif (int u, int v, monplan pl) {
    int x, y, delta, incD, incH;

    incH   = v << 1;
    delta  = incH - u;
    incD   = delta - u;
    for (x = 0, y = 0; x <= u; x++) {
        if (delta > 0) {
            y++;
            delta += incD;
        }
        else {
            delta += incH;
        }
        delta = 2 * u * y + u - 2 * y * x;
        pl [x][y] = '.';
    }
}