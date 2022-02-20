void rgb_render_out() {
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

int rgb_render() {
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
			else {	/* Colouring */
				switch (k % 6) {
					case 0: buffer[(i * (int) res + j) * 2] = '_'; break;
					case 1: buffer[(i * (int) res + j) * 2] = '='; break;
					case 2: buffer[(i * (int) res + j) * 2] = '`'; break;
					case 3: buffer[(i * (int) res + j) * 2] = '~'; break;
					case 4: buffer[(i * (int) res + j) * 2] = ']'; break;
					case 5: buffer[(i * (int) res + j) * 2] = '['; break;
				}
			}
			
			buffer[(i * (int) res + j) * 2 + 1] = buffer[(i * (int) res + j) * 2];
		}
	}
	rgb_render_out();
	
	free(buffer);
}
