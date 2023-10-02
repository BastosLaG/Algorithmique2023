#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include<string.h>

#define MAX 2000
typedef unsigned char uchar;
typedef unsigned char monplan [MAX][MAX];

void droite_triviale (int u, int v, monplan pl);
void droite_triviale_verif (int u, int v, monplan pl);
void affiche (int sizex, int sizey, monplan pl);
void droite (int x0, int y0, int x1, int y1, monplan pl);
void droite_br (int u, int v, monplan pl);

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

void droite (int x0, int y0, int x1, int y1, monplan pl) {
	int x, y;
	float yf;
	
	for (x = x0; x <= x1; x++) {
		yf = (float) (x - x0) * (y1 - y0);
		yf /= (x1 - x0);
		yf += y0;
		y = (int) (yf + 0.5); /* approximation à l’entier le plus proche*/
		affiche(x,y,pl);
	}	
}

void droite_br (int u, int v, monplan pl) {
/* u est dx, v est dy */
	int x, y, delta, incD, incH;
	incH   = v << 1;
	delta  = incH - u;
   	incD   = delta - u;
   	for (x = 0, y = 0; x <= u; x++) {
		affiche(x, y, pl);
		if (delta > 0) {
			y++;
			delta += incD;
		}
		else {
			delta += incH;
		}
   	}
}


