void rgb_render() {
	for (int i = 0; i < res * res; i++) {
		switch (buffer[i * 2]) {
			case '_': printf("\x1B[35m"); break;
			case '=': printf("\x1B[31m"); break;
			case '`': printf("\x1B[33m"); break;
			case '~': printf("\x1B[32m"); break;
			case ']': printf("\x1B[36m"); break;
			case '[': printf("\x1B[34m"); break;
		}
		
		printf("##");
		
		printf("\x1B[0m");
		
		if ((i % (int) res == 0) && (i != 0))
			printf("\n");
	}
}

int rgb() {
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
				switch (k % 6) {
					case 0: buffer[(i * (int) res + j) * 2] = '_'; break;
					case 1: buffer[(i * (int) res + j) * 2] = '='; break;
					case 2: buffer[(i * (int) res + j) * 2] = '`'; break;
					case 3: buffer[(i * (int) res + j) * 2] = '~'; break;
					case 4: buffer[(i * (int) res + j) * 2] = ']'; break;
					case 5: buffer[(i * (int) res + j) * 2] = '['; break;
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
