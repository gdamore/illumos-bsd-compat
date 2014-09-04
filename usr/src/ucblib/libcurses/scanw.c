/*
 * Copyright 2014 Garrett D'Amore <garrett@damore.org>
 *
 * Copyright 2004 Sun Microsystems, Inc.  All rights reserved.
 * Use is subject to license terms.
 */

/*	Copyright (c) 1983, 1984, 1985, 1986, 1987, 1988, 1989 AT&T	*/
/*	  All Rights Reserved  	*/

/*
 * Copyright (c) 1980 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

/*LINTLIBRARY*/

#include	<stdio.h>
#include	<stdarg.h>
#include	<string.h>

/*
 * scanw and friends
 */

#include	"curses.ext"

/*
 * BSD headers don't have this, but we need it (its in stdio.h normally.)
 */
extern int vsscanf(const char *, const char *, va_list);

/*
 *	This routine implements a scanf on the standard screen.
 */

int
scanw(char *fmt, ...)
{	int j;
	va_list ap;

	va_start(ap, fmt);
	j = _sscans(stdscr, fmt, ap);
	va_end(ap);
	return (j);
}

/*
 *	This routine implements a scanf on the given window.
 */

int
wscanw(WINDOW *win, char *fmt, ...)
{
	va_list ap;
	int j;

	va_start(ap, fmt);
	j = _sscans(win, fmt, ap);
	va_end(ap);
	return (j);
}
/*
 *	This routine actually executes the scanf from the window.
 *
 *	This is really a modified version of "sscanf".  As such,
 * it assumes that sscanf interfaces with the other scanf functions
 * in a certain way.  If this is not how your system works, you
 * will have to modify this routine to use the interface that your
 * "sscanf" uses.
 */

int
_sscans(WINDOW *win, char *fmt, va_list	ap)
{
	char	buf[100];
	if (wgetstr(win, buf) == ERR)
		return (ERR);
	return (vsscanf(buf, fmt, ap));
}
