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
#include <stdio.h>
#include <sys/types.h>

#include <cmds.h>
#include <getline.h>

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
