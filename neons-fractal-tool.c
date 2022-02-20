#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <math.h>
#include <stdbool.h>

double res;
int iter_c;
int type;

double c[2];
double z[2];
double tmp[2];
double focus[] = {0, 0};
double magnification = 1;
char *buffer;
int colour;

void iter() {
	if (type == 0) { /* Mandelbrot */
		tmp[0] = z[0] * z[0] - z[1] * z[1] + c[0];
		tmp[1] = 2 * z[0] * z[1] + c[1];
		
		z[0] = tmp[0];
		z[1] = tmp[1];
	} else if (type == 2) { /* Mandelberry */
		tmp[0] = z[0] * z[0] - z[1] * z[1] + c[0];
		tmp[1] = 1.2 * z[0] * z[1] + c[1];
		
		z[0] = tmp[0];
		z[1] = tmp[1];
	} else if (type == 1) { /* Burning ship */
		tmp[0] = fabs(z[0]) * fabs(z[0]) - fabs(z[1]) * fabs(z[1]) + c[0];
		tmp[1] = 2 * fabs(z[0]) * fabs(z[1]) + c[1];
		
		z[0] = tmp[0];
		z[1] = tmp[1];
	}
}

double dst() { /* returns the length of Z */
	return (z[0] * z[0]) + (z[1] * z[1]);
}

void render() {
	for (int i = 0; i < res * res; i++) {
		printf("%c", buffer[i * 2]);
		printf("%c", buffer[i * 2 + 1]);
		
		if ((i % (int) res == 0) && (i != 0))
			printf("\n");
	}
}

int main() {
	printf("Neon's Fractal Tool v1.5\n\n");
	printf("What resolution would you like? ");
	scanf("%lf", &res);
	printf("How many iterations would you like? ");
	scanf("%d", &iter_c);
	printf("How deep would you like to zoom? ");
	scanf("%lf", &magnification);
	printf("Where would you like to zoom? \n");
	scanf("%lf", &focus[0]);
	scanf("%lf", &focus[1]);
	printf("Which fractal?\n\t[0] Mandelbrot\n\t[1] Burning Ship\n\t[2] Mandelberry\n");
	scanf("%d", &type);
	printf("Would you like colouring?\n\t[0] No\n\t[1] Yes\n");
	scanf("%d", &colour);

	int k = 0;
	buffer = (char *) malloc(res * res * 2 + res);

	for (int i = 0; i < res; i++) {
		for (int j = 0; j < res; j++) {
			z[0] = 0;
			z[1] = 0;
		
			if (j < res / 2) /* Don't even try to make sense of this mess */
				c[0] = (double) ((double) j - res / 2) / ((res / 4) * magnification) + focus[0];
			else
				c[0] = (double) ((double) j - (res / 2 - 1)) / ((res / 4) * magnification) + focus[0];
			
			if (i < res / 2)
				c[1] = (double) ((double) i - res / 2) / ((res / 4) * magnification) + focus[1];
			else
				c[1] = (double) ((double) i - (res / 2 - 1)) / ((res / 4) * magnification) + focus[1];
				
			k = 0;
			
			while ((dst() <= 4) && (k < iter_c + 2)) { /* Iterate the function iter() */
				k++;
				iter();
			}
			
			if (k == iter_c + 2) /* If this point is part of the set */
				buffer[(i * (int) res + j) * 2] = '#';
			else if (colour != 0) {	/* Colouring (just various shades of grey) */
				switch (k % 3) {
					case 0: buffer[(i * (int) res + j) * 2] = '_'; break;
					case 1: buffer[(i * (int) res + j) * 2] = '='; break;
					case 2: buffer[(i * (int) res + j) * 2] = '`'; break;
				}
			} else { /* This part is useless, but I'm afraid to remove it */
				buffer[(i * (int) res + j) * 2] = ' ';
			}
			
			buffer[(i * (int) res + j) * 2 + 1] = buffer[(i * (int) res + j) * 2];
		}
	}
	render();
	
	free(buffer); /* Remember to free memory */
	exit(0);
}
