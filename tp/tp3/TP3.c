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

int PGCD(int a, int b);
void droite_pgcd(int u, int v, monplan pl);
void droite_pgcd_verif(int u, int v, monplan pl);

char* droite_Green_and_Pittway(int dx, int dy);
void droite_Green_and_Pittway_verif(int dx, int dy, monplan pl);


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

  droite_pgcd_verif (11, 3, plan);
  printf("PGCD\n");
  affiche (11, 3, plan);
  
  memset (plan, ' ', MAX*MAX);

  droite_pgcd_verif (24, 10, plan);
  affiche (24, 10, plan);
  
  memset (plan, ' ', MAX*MAX);

  droite_Green_and_Pittway_verif(11, 3, plan);
  printf("Trace\n");
  affiche (11, 3, plan);
  
  memset (plan, ' ', MAX*MAX);

  droite_Green_and_Pittway_verif (24, 10, plan);
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
      	droite_pgcd (i, j, plan);
    }
  }
  t1 = clock();
  printf("Pgcd %d\n", (int) (t1 - t0));

  t0 = clock();
  for (i = 1; i < dx; i++) {
    for (j = 1; j < i; j++) {
      	droite_Green_and_Pittway(i, j);
    }
  }
  t1 = clock();
  printf("Trace %d\n", (int) (t1 - t0));
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
        pl [x][(int) (((float) x * v / u) + 0.5)] = '.';
        if (delta > 0) {
            y++;
            delta += incD;
        }
        else {
            delta += incH;
        }
    }
}

int PGCD(int a, int b) {
	if (a <= 0 || b <= 0) return 0;
	if(a==b) return a; 
	else {
		if(a>b) return PGCD(a-b, b);
		else return PGCD(a, b-a);
	}
}
void droite_pgcd(int u, int v, monplan pl){
	int g, ug, vg, x, y, incH, delta, incD;
	g = PGCD(u,v);
	if (g == 0) {}
	else{
		ug = (u/g);
		vg = (v/g);
		incH   = vg << 1;
		delta  = incH - ug;
		incD   = delta - ug;
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
}

void droite_pgcd_verif(int u, int v, monplan pl){
	int g, ug, vg, x, y, incH, delta, incD;
	g = PGCD(u,v);
	ug = (u/g);
	vg = (v/g);
	incH   = vg << 1;
    delta  = incH - ug;
    incD   = delta - ug;
    for (x = 0, y = 0; x <= u; x++) {
        pl [x][(int) (((float) x * v / u) + 0.5)] = '.';
        if (delta > 0) {
            y++;
            delta += incD;
        }
        else {
            delta += incH;
        }
    }
}

// char* droitebest (dx, dy) {
// 	dx -= dy;
// 	s = "0";
// 	t = "1";
// 	while (dx != dy) {
// 		if (dx > dy) {
// 		dx -= dy;
// 		t = s . t ^ (-1);
// 		}
// 		else {
// 		dy -= dx;
// 		s = t . s ^(-1);
// 		}
// 	}
// 	return ( s . t ^ (-1) ) ^dx;
// }

char* droite_Green_and_Pittway(int dx, int dy) {
	int i;
	dx -= dy;
	char* s = "0";
    char* t = "1";
	char* temp = malloc(sizeof(char) * (strlen(s) + strlen(t) + 1));
	char* result = malloc(sizeof(char) * (strlen(s) + strlen(t) + 1));
	while (dx != dy) {
		if (dx > dy) {
			dx -= dy;
			if (sizeof(char) * (strlen(s) + strlen(t) + 1) >= sizeof(temp)) {
    			temp = (char*)realloc(temp, sizeof(char) * (strlen(s) + strlen(t) + 1));
			}
			strcpy(temp, s);
			strcat(temp, t);
			t = temp;
		} else {
			dy -= dx;
			if (sizeof(char) * (strlen(s) + strlen(t) + 1) >= sizeof(temp)) {
    			temp = (char*)realloc(temp, sizeof(char) * (strlen(s) + strlen(t) + 1));
			}
			strcpy(temp, s);
			strcat(temp, t);
			s = temp;
		}
	}
	result = (char*)realloc(result, sizeof(char) * (strlen(s) + strlen(t) + 1));
	strcpy(result, s);
	strcat(result, t);
    return result;
}

void droite_Green_and_Pittway_verif(int dx, int dy, monplan pl){
	char* result = droite_Green_and_Pittway(dx, dy);
	int i, dxi;
	int x = 0, y = 0;
	for (dxi = 0; dxi < dx; dxi++)
	{
		for ( i = 0; result[i] != '\0'; i++) {
			pl[x][(int) (((float) x * dy / dx) + 0.5)] = '.';
			if (result[i] == '1') {
				y++;
			}
			x++;
		}
		pl[x][(int) (((float) x * dy / dx) + 0.5)] = '.';    			
	}
	free(result);
}
