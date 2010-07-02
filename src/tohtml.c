/*
 * tohtml.c - html output.
 *
 * Copyright (C) 2010 Robert C. Curtis
 *
 * difftools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * difftools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with difftools.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "difftools.h"
#include <cmds.h>
#include <getline.h>

#include <stdio.h>
#include <string.h>


/* HTML colors */
#define COLOR_NO		"000000"
#define COLOR_RD 		"cc0000"
#define COLOR_GR 		"008800"
#define COLOR_BL 		"000088"
#define COLOR_MG 		"990099"
#define COLOR_CY 		"009999"
#define COLOR_YL 		"999900"

#define HTML_LINE_PREFIX	"<div style=\"" \
				"font-family: monospace; " \
				"font-size: 12px; " \
				"white-space: pre; " \
				"color: #%s; " \
				"\">"
#define HTML_LINE_SUFFIX	"</div>\n"

#define HTML_LT			"&lt;"
#define HTML_GT			"&gt;"
#define HTML_AMP		"&amp;"

static size_t htmlfixup(const char *in, size_t in_len,
		char *out, size_t out_len)
{
	size_t i, j;
	size_t sublen;
	const char *sub;

	for(i = 0, j = 0; (i < in_len) && (j < (out_len - 1)); i++) {
		switch(in[i]) {
			case '<':
				sub = HTML_LT;
				sublen = strlen(sub);
				break;
			case '>':
				sub = HTML_GT;
				sublen = strlen(sub);
				break;
			case '&':
				sub = HTML_AMP;
				sublen = strlen(sub);
				break;
			default:
				sub = &in[i];
				sublen = 1;
		}
		if((j + sublen) >= (out_len - 1))
			break;
		memcpy(&out[j], sub, sublen);
		j+=sublen;
	}
	out[j] = '\0';
	return j;
}

CMDHANDLER(file2htmlpart)
{
	FILE *inp = stdin, *outp = stdout;
	ssize_t l;

	/* XXX put support for reading a file instead of stdin here */

	while((l = getline(inp, APPDATA->linebuf1, LINEBUF_SIZE)) >= 0) {
		if(l == 0) {
			/* make empty lines just a space so the html
			 * preserves them */
			APPDATA->linebuf1[0] = ' ';
			APPDATA->linebuf1[1] = '\0';
			l = 1;
		}
		fprintf(outp, HTML_LINE_PREFIX, COLOR_NO);
		htmlfixup(APPDATA->linebuf1, l,
				APPDATA->linebuf2, LINEBUF_SIZE);
		fprintf(outp, "%s", APPDATA->linebuf2);
		fprintf(outp, HTML_LINE_SUFFIX);
	}

	return 0;
}
APPCMD(file2htmlpart, &file2htmlpart,
		"converts a raw file into a chunk of html",
		"usage: file2htmlpart\n"
		"    Takes input from stdin. Outputs to stdout.",
		NULL);

CMDHANDLER(diff2htmlpart)
{
	FILE *inp = stdin, *outp = stdout;
	ssize_t l;

	/* XXX put support for reading a file instead of stdin here */

	while((l = getline(inp, APPDATA->linebuf1, LINEBUF_SIZE)) >= 0) {
		if(l == 0) {
			/* make empty lines just a space so the html
			 * preserves them */
			APPDATA->linebuf1[0] = ' ';
			APPDATA->linebuf1[1] = '\0';
			l = 1;
		}
		switch(APPDATA->linebuf1[0]) {
			case '-':
				fprintf(outp, HTML_LINE_PREFIX, COLOR_RD);
				break;
			case '+':
				fprintf(outp, HTML_LINE_PREFIX, COLOR_GR);
				break;
			case '@':
				fprintf(outp, HTML_LINE_PREFIX, COLOR_MG);
				break;
			case '=':
				fprintf(outp, HTML_LINE_PREFIX, COLOR_BL);
				break;
			case ' ':
				fprintf(outp, HTML_LINE_PREFIX, COLOR_NO);
				break;
			default:
				fprintf(outp, HTML_LINE_PREFIX, COLOR_CY);
		}
		htmlfixup(APPDATA->linebuf1, l,
				APPDATA->linebuf2, LINEBUF_SIZE);
		fprintf(outp, "%s", APPDATA->linebuf2);
		fprintf(outp, HTML_LINE_SUFFIX);
	}

	return 0;
}
APPCMD(diff2htmlpart, &diff2htmlpart,
		"converts a unified diff into a chunk of html",
		"usage: diff2htmlpart\n"
		"    Takes input from stdin. Outputs to stdout.",
		NULL);
