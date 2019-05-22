#include <errno.h>
#include <getopt.h>
#include <math.h> /* for sqrt(3) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define N			(10)
#define NCOLS		(120)
#define MIN_NCOLS	(32)

#define F(_fmt) __FILE__":%d:%s: " _fmt, __LINE__, __func__

int fsum = 0;
size_t ncols = NCOLS;

static void show(int a, int m)
{
	size_t col = 0;
	col += printf("m(=%d):", m);
	int b = (a + m - 1);
	col += printf(" a => %d; b => %d;", a, b);
	int i;
	int acc = 0;
	char *sep = "";
	if (fsum) {
		printf(" sum: ");
		for (i = 0; i < m; i++) {
			acc += a;
			col += printf("%s%d(=%d)",
				sep, a, acc);
			a++;
			if (col >= ncols) {
				col = 0;
				sep = "\n  + ";
			} else {
				sep = " + ";
			}
		}
		col += printf(" => %d", acc);
	}
	printf("\n");
}

static void process(FILE *f)
{
	char line[128];
	int istty = isatty(fileno(f));
	while(1) {
		if (istty) {
			fprintf(stderr, "n> ");
			fflush(stderr);
		}
		if(!fgets(line, sizeof line, f)) break;
		int n, m;
		sscanf(line, "%d", &n);
		show(n, 1);
		for (m = 2; m < (n << 1); m++) {

			/* we have 2*a = 2*n/m - m + 1, so first 2*n must
			 * be multiple of m, then 2*a must be even. */
			if ((n << 1) % m) continue;

			/* 2*n/m - m + 1 must be even */
			int a;
			if ((a = (n << 1)/m - m + 1) & 1) continue;
			a >>= 1;

			show(a, m);
#if 0
			if (a == 1)
				show(0, m+1);
#endif
		}
		show(1-n, n << 1);
	}
}

int main(int argc, char **argv)
{
	int opt, err = 0;
	while ((opt = getopt(argc, argv, "vc:")) != EOF) {
		switch(opt) {
		case 'v': fsum = 1; break;
		case 'c': ncols = atoi(optarg); break;
		}
	}
	if (ncols < MIN_NCOLS) ncols = MIN_NCOLS;
	argc -= optind;
	argv += optind;

	int i;
	if (argc) for(i = 0; i < argc; i++) {
		FILE *f = fopen(argv[i], "rt");
		if (!f) {
			fprintf(stderr,
				F("fopen: %s: %s (errno=%d)\n"),
				argv[i], strerror(errno), errno);
			err++;
			continue;
		}
		process(f);
		fclose(f);
	} else {
		process(stdin);
	}
	return err;
}
