/*
 * colorize.c - diff colorizer.
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

#define COLOR_NO	"\x1b[0m"
#define COLOR_BR 	"\x1b[30m"
#define COLOR_RD 	"\x1b[31m"
#define COLOR_GR 	"\x1b[32m"
#define COLOR_YL 	"\x1b[33m"
#define COLOR_BL 	"\x1b[34m"
#define COLOR_MG 	"\x1b[35m"
#define COLOR_CY 	"\x1b[36m"


CMDHANDLER(colorize)
{
	FILE *inp = stdin, *outp = stdout;
	ssize_t l;

	/* XXX put support for reading a file instead of stdin here */

	while((l = fgetline(inp, APPDATA->linebuf1, LINEBUF_SIZE)) >= 0) {
		switch(APPDATA->linebuf1[0]) {
			case '-':
				fprintf(outp, COLOR_RD "%s" COLOR_NO "\n",
						APPDATA->linebuf1);
				break;
			case '+':
				fprintf(outp, COLOR_GR "%s" COLOR_NO "\n",
						APPDATA->linebuf1);
				break;
			case '@':
				fprintf(outp, COLOR_MG "%s" COLOR_NO "\n",
						APPDATA->linebuf1);
				break;
			case '=':
				fprintf(outp, COLOR_CY "%s" COLOR_NO "\n",
						APPDATA->linebuf1);
				break;
			case ' ':
				fprintf(outp, COLOR_NO "%s" COLOR_NO "\n",
						APPDATA->linebuf1);
				break;
			default:
				fprintf(outp, COLOR_YL "%s" COLOR_NO "\n",
						APPDATA->linebuf1);
		}
	}

	return 0;
}
APPCMD(diffcolorize, &colorize,
		"colorize diff formatted text",
		"usage: diffcolorize\n"
		"    Takes input from stdin. Outputs to stdout",
		NULL);
