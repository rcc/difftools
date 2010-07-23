/*
 * difftools.h
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

#ifndef I__DIFFTOOLS_H__
	#define I__DIFFTOOLS_H__

#ifndef LINEBUF_SIZE
#define LINEBUF_SIZE		(4<<10)
#endif /* LINEBUF_SIZE */

struct appdata_priv {
	char linebuf1[LINEBUF_SIZE];
	char linebuf2[LINEBUF_SIZE];
};

#define APPDATA		((struct appdata_priv *)appdata)

#endif /* I__DIFFTOOLS_H__ */
