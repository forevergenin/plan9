void	setenv(byte*, byte*);
Font*	getfont(int, int, byte*);
(byte*, Rune*, int)	getarg(Text*, int, int);
(byte*, byte*)		getbytearg(Text*, int, int);
void	new(Text*, Text*, Text*, int, int, Rune*, int);
void	scrsleep(uint);
void	savemouse(Window*);
void	restoremouse(Window*);
void	clearmouse();
(Rune*, int) cleanname(Rune*, int);
void	run(Window*, byte*, Rune*, int, int, byte*, byte*);
void fsysclose();
void	setcurtext(Text*, int);
int	isfilec(Rune);
void	rxinit();
(Rune*, int)	dirname(Text*, Rune*, int);
void	error(byte*);
void	warning(Mntdir*, byte*, ...);
void	cvttorunes(byte*, int, Rune*, int*, int*, int*);
void*	tmalloc(uint);
void	tfree();
void	killprocs();
void	killtasks();
int	runeeq(Rune*, uint, Rune*, uint);
int	ALEF_tid();
Rune*	strrune(Rune*, Rune);
void	iconinit();
Timer*	timerstart(int);
void	timerstop(Timer*);
void	timerinit();
int	runestrlen(Rune*);
void	cut(Text*, Text*, Text*, int, int, Rune*, int);
void	paste(Text*, Text*, Text*, int, int, Rune*, int);
void	get(Text*, Text*, Text*, int, int, Rune*, int);
void	put(Text*, Text*, Text*, int, int, Rune*, int);
void	fontx(Text*, Text*, Text*, int, int, Rune*, int);
void	timerwaittask(Timer*);
int	isalnum(Rune);
void	execute(Text*, uint, uint, int, Text*);
int	search(Text*, Rune*, uint);
void	look3(Text*, uint, uint, int);
uint	min(uint, uint);
uint	max(uint, uint);
Window*	lookfile(Rune*, int);
Window*	lookid(int, int);
byte*	runetobyte(Rune*, int);
(Rune*,int)	bytetorune(byte*);
void	fsysinit();
Mntdir*	fsysmount(Rune*, int, Rune**, int);
void		fsysdelid(Mntdir*);
Xfid*		respond(Xfid*, Fcall*, byte*);
void*	fbufalloc();
void		fbuffree(void*);
int		rxcompile(Rune*);
int		rgetc(Rune*, uint);
int		tgetc(Text*, uint);
int		isaddrc(int);
(Rune*, int)		findbl(Rune*, int);
(Rune*, int)		skipbl(Rune*, int);
(int, Rangeset)		rxexecute(Text*, uint, uint);
(int, Rangeset)		rxbexecute(Text*, uint);
(int, int, Range)		address(Text*, Range, Range, void*, uint, uint, int (*)(void*, uint),  int);
Window*	newwindow(Text *t);
int	expand(Text*, uint, uint, Expand*);

#define	runemalloc(a)		(Rune*)malloc((a)*sizeof(Rune))
#define	runerealloc(a, b)	(Rune*)realloc((a), (b)*sizeof(Rune))
#define	runemove(a, b, c)	memmove((a), (b), (c)*sizeof(Rune))
