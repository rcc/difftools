#include <stdio.h>
#include <sys/types.h>

#include <cmds.h>

#define COLOR_NO	"\x1b[00;00m"
#define COLOR_BR 	"\x1b[00;01m"
#define COLOR_RD 	"\x1b[00;31m"
#define COLOR_GR 	"\x1b[00;32m"
#define COLOR_YL 	"\x1b[00;33m"
#define COLOR_BL 	"\x1b[00;34m"
#define COLOR_MG 	"\x1b[00;35m"
#define COLOR_CY 	"\x1b[00;36m"

static FILE *inp;

#define LINEBUF_SIZE	2048
static char linebuf[LINEBUF_SIZE];

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

CMDHANDLER(colorize)
{
	inp = stdin;
	ssize_t l;

	/* XXX put support for reading a file instead of stdin here */

	while((l = getline(inp, linebuf, LINEBUF_SIZE)) >= 0) {
		switch(linebuf[0]) {
			case '-':
				printf(COLOR_RD "%s" COLOR_NO "\n", linebuf);
				break;
			case '+':
				printf(COLOR_GR "%s" COLOR_NO "\n", linebuf);
				break;
			case '@':
				printf(COLOR_MG "%s" COLOR_NO "\n", linebuf);
				break;
			case '=':
				printf(COLOR_CY "%s" COLOR_NO "\n", linebuf);
				break;
			default:
				printf(COLOR_NO "%s" COLOR_NO "\n", linebuf);
				break;
		}
	}

	return 0;
}
APPCMD(colorize, &colorize,
		"colorize diff formatted text",
		"usage: diffcolorize\n"
		"    Takes input from stdin. Outputs to stdout",
		NULL);
