#include <string.h>
#include <libg.h>

typedef unsigned char uchar;

void
cursorswitch(Cursor *c)
{
	uchar *b;

	if(c == 0){
		b = bneed(1);
		b[0] = 'c';
		bflush();
		return;
	}

	b = bneed(1+8+2*(2*16));
	b[0] = 'c';
	BPLONG(b+1, c->offset.x);
	BPLONG(b+5, c->offset.y);
	memmove(b+9, c->clr, 2*16);
	memmove(b+41, c->set, 2*16);
	bflush();
}
