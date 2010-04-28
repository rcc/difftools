#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include <cmds.h>

static FILE *inp;

#define LINEBUF_SIZE	2048
static char linebuf1[LINEBUF_SIZE];
static char linebuf2[LINEBUF_SIZE];

static ssize_t getline(FILE *fp, char *buf, size_t bufsz)
{
	int have_cr = 0, have_lf = 0;
	size_t i = 0;
	int c;

	while(((c = getc(fp)) != EOF) && (i < (bufsz - 1))) {
		if(((char)c != '\n') && ((char)c != '\r')) {
			if(have_cr || have_lf) {
				ungetc(c, fp);
				break;
			} else {
				buf[i++] = (char)c;
			}
		} else {
			if((char)c == '\n') {
				have_cr++;
			} else if((char)c == '\r') {
				have_lf++;
			}
			if((have_cr > 1) || (have_lf > 1)) {
				ungetc(c, fp);
				break;
			}
		}
	}

	buf[i] = '\0'; /* NULL Terminate */

	if((c == EOF) && !i && !have_cr && !have_lf)
		return -1;

	return (ssize_t)i;
}

CMDHANDLER(detab)
{
	inp = stdin;
	ssize_t l;
	size_t i,j;
	int tabstop = 4;
	int ret = 0;

	/* XXX put support for reading a file instead of stdin here */

	if(argc == 1) {
		ret = 1;
		tabstop = atoi(argv[0]);
		if(tabstop < 1 || tabstop > 80)
			tabstop = 4;
	}

	while((l = getline(inp, linebuf1, LINEBUF_SIZE)) >= 0) {
		i = 0;
		j = 0;
		while(linebuf1[i] && j < (LINEBUF_SIZE - 1)) {
			if(linebuf1[i] == '\t') {
				size_t destj = (j + tabstop);
				destj = destj - (destj % tabstop);
				while(j < destj)
					linebuf2[j++] = ' ';
			} else {
				linebuf2[j++] = linebuf1[i];
			}
			i++;
		}
		linebuf2[j] = '\0';
		printf("%s\n", linebuf2);
	}

	return 0;
}
APPCMD(detab, &detab,
		"expand tabs in text",
		"usage: detab [tabstop]\n"
		"    Takes input from stdin. Outputs to stdout.\n"
		"    Tabstop is optional. Default is 4.",
		NULL);
