/*
 * getline.c
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
#include <getline.h>

ssize_t getline(FILE *fp, char *buf, size_t bufsz)
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
