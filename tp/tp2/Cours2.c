/*
Sources disponible: 
https://jj.up8.site/AA/AA23_Droites.html
https://jj.up8.site/AA/AA23_TP_Droites.html

Attention lien surement obselete
https://jj.up8.site/AA/AA22_TP_Droites.html
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 250

void trivial (int a, int b);
void trivialf (int a, int b);




int main(void){

    trivial(5, 2);
    return 0;
}


void trivial (int a, int b){
    int x, y; 
    for (x = 0; x < MAX; x++) //seulement si a <= 1
    {
        y = a*x + b;
        putpixel(x,y);
    }
    
}

void trivialf (int a, int b){
    int x, y;
    float yf;
    for (x = 0; x < MAX; x++) //seulement si a <= 1
    {
        yf = a*x + b;
        y = (int) (yf + 0.5f);
        putpixel(x,y);
    }    
}

/*
pente a : v/u = (dy)/(dx)
translation y = ((vx)/u) + b // putpixel (x, y+b)

// putpixel (x + x0, y + y0) si on part de l'origine 

Jack Bresenham

yf = (v*x)/u 

si  |yf - y|        >= 0.5          --> y++
    |(vx/u) - y|    >= 0.5
    |(vx) - yu|     >= u/2
    |2(vx) - 2uy|   >= u            --> y++
    
f(x,y) = (|2(vx) - 2uy|) - u > 0    --> y++

g(x,y) = (|2(vx) - 2uy|)

si      g(x,y) <  0  --> -g(x,y) >  u  --> y++
                        sinon !(-g(x,y) >  u)  --> rien

sinon   g(x,y) >= 0  -->  g(x,y) >= u  --> y++
                        sinon !(g(x,y) >  u)   --> rien


|y - yf|        >   |y+1 - yf| --> y++
|y - ((vx)/u)|  >   |y+1 - ((vx)/u)| --> y++
|uy - vx|       >   |(uy + u) - vx| --> y++
  (A)                      (B) 


A   B
<0  <0  --> y++
<0  >=0 --> y++
>=0 <0  --> cas impossible (dépassement binaire valeur négatif)
>=0 >=0 --> rien

*/

void bresenham(int u, int v){
    int delta, x, y;
    delta = u;
    y = 0;
    for (x = 0; x <= u; x++)
    {
        if (delta < 0){
            y++;
        }
        delta = ((2*u*y) +u) - (2*v*x);
        putpixel(x, y);
    }
}

void bresenham2(int u, int v){
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
        putpixel(x, y);
   	}
}