/*
 * detab.c - tab expander.
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
#include <stdlib.h>
#include <sys/types.h>

#include <cmds.h>
#include <getline.h>

static FILE *inp;

#define LINEBUF_SIZE	2048
static char linebuf1[LINEBUF_SIZE];
static char linebuf2[LINEBUF_SIZE];

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
