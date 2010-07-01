#ifndef I__DIFFTOOLS_H__
	#define I__DIFFTOOLS_H__

#ifndef LINEBUF_SIZE
#define LINEBUF_SIZE		(4<<10)
#endif /* LINEBUF_SIZE */

struct difftools_priv {
	char linebuf1[LINEBUF_SIZE];
	char linebuf2[LINEBUF_SIZE];
};

#define APPDATA		((struct difftools_priv *)appdata)

#endif /* I__DIFFTOOLS_H__ */
