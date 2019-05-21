#include <stdio.h>
#include <math.h> /* for sqrt(3) */
#include <unistd.h>

#define N (10)

int f(double n, double a)
{
	return sqrt(a*(a - 1.0) + 2*n - 0.25) - a - 0.5;
}

double sum(double a, int m)
{
	return a * (m + 1) + m * (m + 1) / 2;
}

int main()
{
	char line[1024];
	while(1) {
		if (isatty(0)) {
			fprintf(stderr, "n, a > ");
			fflush(stderr);
		}
		if(!fgets(line, sizeof line, stdin)) break;
		double n, a;
		sscanf(line, "%lg%lg", &n, &a);
		int m = f(n, a);
		printf("m = f(n=%0.8g, a=%0.8g) => %d\n", n, a, m);
		double s = sum(a, m);
		printf("s = sum(a=%0.8g, m=%d) => %0.8g\n", a, m, s);
		double b = n - s;
		printf("b = n(%0.8g) - s(%0.8g) => %0.8g\n", n, s, b);
		int i;
		double acc = 0.0;
		char *sep = "  ";
		for (i = 0; i <= m; i++) {
			printf("%s%lg(=>%lg)",
				sep,
				a + i,
				(acc += a + i));
			sep = i % N + 1 == N ? "\n+ " : " + ";
		}
		printf("%sb(=>%lg) = %lg\n",
			sep, b, (acc += b));
	}
}
