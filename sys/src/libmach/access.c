/*
 * functions to read and write an executable or file image
 */

#include <u.h>
#include <libc.h>
#include <bio.h>
#include <mach.h>

static	int	mget(Map*, ulong, char*, int);
static	int	mput(Map*, ulong, char*, int);
static int	reloc(Map*, ulong, long*);

/*
 * routines to get/put various types
 */

int
get4(Map *map, ulong addr, long *x)
{
	if (!map) {
		werrstr("get4: invalid map");
		return -1;
	}

	if (map->fd < 0) {
		*x = addr;
		return 1;
	}
	if (mget(map, addr, (char *)x, 4) < 0)
		return -1;
	*x = machdata->swal(*x);
	return (1);
}

int
get2(Map *map, ulong addr, ushort *x)
{
	if (!map) {
		werrstr("get2: invalid map");
		return -1;
	}

	if (map->fd < 0) {
		*x = addr;
		return 1;
	}
	if (mget(map, addr, (char *)x, 2) < 0)
		return -1;
	*x = machdata->swab(*x);
	return (1);
}

int
get1(Map *map, ulong addr, uchar *x, int size)
{
	uchar *cp;

	if (!map) {
		werrstr("get1: invalid map");
		return -1;
	}

	if (map->fd < 0) {
		cp = (uchar*)&addr;
		while (cp < (uchar*)(&addr+1) && size-- > 0)
			*x++ = *cp++;
		while (size-- > 0)
			*x++ = 0;
	} else
		return mget(map, addr, (char*)x, size);
	return 1;
}

int
put4(Map *map, ulong addr, long v)
{
	if (!map || map->fd < 0) {
		werrstr("put4: missing or unopened map");
		return -1;
	}
	v = machdata->swal(v);
	return mput(map, addr, (char *)&v, 4);
}

int
put2(Map *map, ulong addr, ushort v)
{
	if (!map || map->fd < 0) {
		werrstr("put2: missing or unopened map");
		return -1;
	}
	v = machdata->swab(v);
	return mput(map, addr, (char *)&v, 2);
}

int
put1(Map *map, ulong addr, uchar *v, int size)
{
	if (!map || map->fd < 0) {
		werrstr("put1: missing or unopened map");
		return -1;
	}
	return mput(map, addr, (char *)v, size);
}

static int
mget(Map *map, ulong addr, char *buf, int size)
{
	long off;
	int i, j, k;

	if (reloc(map, addr, &off) < 0)
		return -1;

	seek(map->fd, off, 0);
	for (i = j = 0; i < 2; i++) {	/* in case read crosses page */
		k = read(map->fd, buf, size-j);
		if (k < 0) {
			werrstr("can't read address %lux: %r", addr);
			return -1;
		}
		j += k;
		if (j == size)
			return j;
	}
	werrstr("partial read at address %lux", addr);
	return -1;
}

static int
mput(Map *map, ulong addr, char *buf, int size)
{
	long off;
	int i, j, k;

	if (reloc(map, addr,&off) < 0)
		return -1;

	seek(map->fd, off, 0);
	for (i = j = 0; i < 2; i++) {	/* in case read crosses page */
		k = write(map->fd, buf, size-j);
		if (k < 0) {
			werrstr("can't write address %lux: %r", addr);
			return -1;
		}
		j += k;
		if (j == size)
			return j;
	}
	werrstr("partial write at address %lux", addr);
	return -1;
}

/*
 *	convert address to file offset; returns nonzero if ok
 */
static int
reloc(Map *map, ulong addr, long *offp)
{
	int i;

	for (i = 0; i < map->nsegs; i++) {
		if (map->seg[i].inuse)
		if (map->seg[i].b <= addr && addr < map->seg[i].e) {
			*offp = addr + map->seg[i].f - map->seg[i].b;
			return 1;
		}
	}
	werrstr("can't translate address %lux", addr);
	return -1;
}
