#include <getopt.h>
#include <stdio.h>
#include <math.h> /* for sqrt(3) */
#include <unistd.h>

#define N (10)
#define NCOLS (120)

int fsum = 0;

double get_a(int n, int m)
{
	return (double)n/m - (m - 1)/2.0;
}

void show(int n, int m)
{
	printf("m=%d:\n", m);
	double a = get_a(n, m);
	printf("  a = get_a(n=%d, m=%d) => %.8lg\n", n, m, a);
	double b = (a + m - 1);
	printf("  b = (a(=%.8lg) + m(%d) - 1) => %.8lg\n", a, m, b);
	int i;
	double acc = 0.0;
	char *sep = "  Sum: ";
	size_t col = 0;
	if (fsum) {
		for (i = 0; i < m; i++) {
			col += printf("%s%.8lg(=%.8lg)",
				sep,
				a + i, (acc += a + i));
			if (col >= NCOLS) {
				col = 0;
				sep = "\n  + ";
			} else {
				sep = " + ";
			}
		}
		printf(" => %.8lg\n", acc);
	}
}

int main(int argc, char **argv)
{
	int opt;

	while ((opt = getopt(argc, argv, "v")) != EOF) {
		switch(opt) {
		case 'v': fsum = 1; break;
		}
	}

	char line[1024];
	while(1) {
		if (isatty(0)) {
			fprintf(stderr, "n> ");
			fflush(stderr);
		}
		if(!fgets(line, sizeof line, stdin)) break;
		int n, m;
		sscanf(line, "%d", &n);
		for (m = 1;m < 2*n; m += 2) {
			if (n % m) continue;
			show(n, m);
		}
		show(n, 2*n);
	}
}
