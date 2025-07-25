# This makefile for Readline library documentation is in -*- text -*- mode.
# Emacs likes it that way.

# Copyright (C) 1996-2009 Free Software Foundation, Inc.

#   This program is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.

#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.

#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.

PACKAGE_TARNAME = readline

topdir = ..
srcdir = .


prefix = /home/atseruny/Desktop/minishell/libraries/readline

datarootdir = ${prefix}/share

docdir = ${datarootdir}/doc/${PACKAGE_TARNAME}
infodir = ${datarootdir}/info

mandir = ${datarootdir}/man
manpfx = man

man1ext = .1
man1dir = $(mandir)/$(manpfx)1
man3ext = .3
man3dir = $(mandir)/$(manpfx)3

# set this to a value to have the HTML documentation installed
htmldir =

# Support an alternate destination root directory for package building
DESTDIR =

SHELL = /bin/sh
RM = rm -f

INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644

BUILD_DIR = /home/atseruny/Desktop/minishell/libraries/readline-8.2
TEXINPUTDIR = $(srcdir)

MAKEINFO    = LANGUAGE= makeinfo
TEXI2DVI    = $(srcdir)/texi2dvi
TEXI2HTML   = $(srcdir)/texi2html
QUIETPS     = #set this to -q to shut up dvips
PAPERSIZE   = letter
PSDPI       = 600
DVIPS       = dvips -D ${PSDPI} $(QUIETPS) -t ${PAPERSIZE} -o $@     # tricky
# experimental; uses external texi2dvi for now; this needs pdftex to be present
TEXI2PDF    = texi2dvi --pdf

# These tools might not be available; they're not required
DVIPDF      = dvipdfm -o $@ -p ${PAPERSIZE}
PSPDF       = gs -sPAPERSIZE=${PAPERSIZE} -sDEVICE=pdfwrite -dNOPAUSE -dBATCH -sOutputFile=$@

RLSRC = $(srcdir)/rlman.texi $(srcdir)/rluser.texi \
	$(srcdir)/rltech.texi $(srcdir)/version.texi \
	$(srcdir)/rluserman.texi $(srcdir)/fdl.texi
HISTSRC = $(srcdir)/history.texi $(srcdir)/hsuser.texi \
	  $(srcdir)/hstech.texi $(srcdir)/version.texi $(srcdir)/fdl.texi

# This should be a program that converts troff to an ascii-readable format
NROFF       = groff -Tascii

# This should be a program that converts troff to postscript
GROFF       = groff

DVIOBJ = readline.dvi history.dvi rluserman.dvi
INFOOBJ = readline.info history.info rluserman.info
PSOBJ = readline.ps history.ps rluserman.ps readline_3.ps history_3.ps
HTMLOBJ = readline.html history.html rluserman.html
TEXTOBJ = readline.0 history.0
PDFOBJ = readline.pdf history.pdf rluserman.pdf

INTERMEDIATE_OBJ = rlman.dvi

DIST_DOCS = $(DVIOBJ) $(PSOBJ) $(HTMLOBJ) $(INFOOBJ) $(TEXTOBJ) $(PDFOBJ)

.SUFFIXES:      .0 .3 .ps .txt .dvi .html .pdf

.3.0:
	$(RM) $@
	-${NROFF} -man $< > $@

.ps.pdf:
	$(RM) $@
	-${PSPDF} $<

.dvi.pdf:
	$(RM) $@
	-${DVIPDF} $<

#.texi.pdf:
#	$(RM) $@
#	-${TEXI2PDF} $<

all: info dvi html ps text pdf
nodvi: info html text

xdist: $(DIST_DOCS)

info:	$(INFOOBJ)
dvi:	$(DVIOBJ)
ps:	$(PSOBJ)
html:	$(HTMLOBJ)
text:	$(TEXTOBJ)
pdf:	$(PDFOBJ)

readline.dvi: $(RLSRC)
	TEXINPUTS=.:$(TEXINPUTDIR):$$TEXINPUTS $(TEXI2DVI) $(srcdir)/rlman.texi
	mv rlman.dvi readline.dvi

readline.info: $(RLSRC)
	$(MAKEINFO) --no-split -I $(TEXINPUTDIR) -o $@ $(srcdir)/rlman.texi

rluserman.dvi: $(RLSRC)
	TEXINPUTS=.:$(TEXINPUTDIR):$$TEXINPUTS $(TEXI2DVI) $(srcdir)/rluserman.texi

rluserman.info: $(RLSRC)
	$(MAKEINFO) --no-split -I $(TEXINPUTDIR) -o $@ $(srcdir)/rluserman.texi

history.dvi: ${HISTSRC}
	TEXINPUTS=.:$(TEXINPUTDIR):$$TEXINPUTS $(TEXI2DVI) $(srcdir)/history.texi

history.info: ${HISTSRC}
	$(MAKEINFO) --no-split -I $(TEXINPUTDIR) -o $@ $(srcdir)/history.texi

readline.ps:	readline.dvi
	$(RM) $@
	$(DVIPS) readline.dvi

rluserman.ps:	rluserman.dvi
	$(RM) $@
	$(DVIPS) rluserman.dvi

history.ps:	history.dvi
	$(RM) $@
	$(DVIPS) history.dvi

#
# This leaves readline.html and rlman.html -- rlman.html is for www.gnu.org
#
readline.html:	${RLSRC}
	$(MAKEINFO) -o $@ --html --no-split -I$(TEXINPUTDIR) $(srcdir)/rlman.texi

rlman.html:	${RLSRC}
	$(MAKEINFO) -o $@ --html --no-split -I$(TEXINPUTDIR) $(srcdir)/rlman.texi

rluserman.html:	${RLSRC}
	$(MAKEINFO) --html --no-split -I$(TEXINPUTDIR) $(srcdir)/rluserman.texi

history.html:	${HISTSRC}
	$(MAKEINFO) --html --no-split -I$(TEXINPUTDIR) $(srcdir)/history.texi

readline.0: readline.3

readline_3.ps: $(srcdir)/readline.3
	${RM} $@
	${GROFF} -man < $(srcdir)/readline.3 > $@ 

history.0: history.3

history_3.ps: $(srcdir)/history.3
	${RM} $@
	${GROFF} -man < $(srcdir)/history.3 > $@ 

readline.pdf:	$(RLSRC)
	TEXINPUTS=.:$(TEXINPUTDIR):$$TEXINPUTS $(TEXI2PDF) $(srcdir)/rlman.texi
	mv rlman.pdf $@

history.pdf:	$(HISTSRC)
	TEXINPUTS=.:$(TEXINPUTDIR):$$TEXINPUTS $(TEXI2PDF) $(srcdir)/history.texi

rluserman.pdf:	$(RLSRC)
	TEXINPUTS=.:$(TEXINPUTDIR):$$TEXINPUTS $(TEXI2PDF) $(srcdir)/rluserman.texi

clean:
	$(RM) *.aux *.bak *.cp *.fn *.ky *.log *.pg *.toc *.tp *.vr *.cps \
	      *.pgs *.bt *.bts *.rw *.rws *.fns *.kys *.tps *.vrs *.o \
	      core *.core

mostlyclean: clean

distclean: clean maybe-clean
	$(RM) $(INTERMEDIATE_OBJ)
	$(RM) Makefile

maybe-clean:
	-if test "X$(topdir)" != "X.." && test "X$(topdir)" != "X$(BUILD_DIR)"; then \
		$(RM) $(DIST_DOCS); \
	fi

maintainer-clean: clean
	$(RM) $(DIST_DOCS)
	$(RM) $(INTERMEDIATE_OBJ)
	$(RM) $(PDFOBJ)
	$(RM) Makefile

installdirs:	$(topdir)/support/mkdirs
	-$(SHELL) $(topdir)/support/mkdirs $(DESTDIR)$(infodir) $(DESTDIR)$(man3dir)
	-if test -n "${htmldir}" ; then \
		$(SHELL) $(topdir)/support/mkdirs $(DESTDIR)$(htmldir) ; \
	fi

install:	installdirs
	if test -f readline.info; then \
		${INSTALL_DATA} readline.info $(DESTDIR)$(infodir)/readline.info; \
	else \
		${INSTALL_DATA} $(srcdir)/readline.info $(DESTDIR)$(infodir)/readline.info; \
	fi
	if test -f rluserman.info; then \
		${INSTALL_DATA} rluserman.info $(DESTDIR)$(infodir)/rluserman.info; \
	else \
		${INSTALL_DATA} $(srcdir)/rluserman.info $(DESTDIR)$(infodir)/rluserman.info; \
	fi
	if test -f history.info; then \
		${INSTALL_DATA} history.info $(DESTDIR)$(infodir)/history.info; \
	else \
		${INSTALL_DATA} $(srcdir)/history.info $(DESTDIR)$(infodir)/history.info; \
	fi
	-if $(SHELL) -c 'install-info --version' >/dev/null 2>&1; then \
		install-info --dir-file=$(DESTDIR)$(infodir)/dir \
			$(DESTDIR)$(infodir)/readline.info ; \
		install-info --dir-file=$(DESTDIR)$(infodir)/dir \
			$(DESTDIR)$(infodir)/history.info ; \
		install-info --dir-file=$(DESTDIR)$(infodir)/dir \
			$(DESTDIR)$(infodir)/rluserman.info ; \
	else true; fi
	-${INSTALL_DATA} $(srcdir)/readline.3 $(DESTDIR)$(man3dir)/readline$(man3ext)
	-${INSTALL_DATA} $(srcdir)/history.3 $(DESTDIR)$(man3dir)/history$(man3ext)
	-if test -n "${htmldir}" ; then \
		if test -f readline.html; then \
			${INSTALL_DATA} readline.html $(DESTDIR)$(htmldir)/readline.html; \
		else \
			${INSTALL_DATA} $(srcdir)/readline.html $(DESTDIR)$(htmldir)/readline.html; \
		fi ; \
		if test -f history.html; then \
			${INSTALL_DATA} history.html $(DESTDIR)$(htmldir)/history.html; \
		else \
			${INSTALL_DATA} $(srcdir)/history.html $(DESTDIR)$(htmldir)/history.html; \
		fi ; \
		if test -f rluserman.html; then \
			${INSTALL_DATA} rluserman.html $(DESTDIR)$(htmldir)/rluserman.html; \
		else \
			${INSTALL_DATA} $(srcdir)/rluserman.html $(DESTDIR)$(htmldir)/rluserman.html; \
		fi ; \
	fi

uninstall:
	$(RM) $(DESTDIR)$(infodir)/readline.info
	$(RM) $(DESTDIR)$(infodir)/rluserman.info
	$(RM) $(DESTDIR)$(infodir)/history.info
	$(RM) $(DESTDIR)$(man3dir)/readline$(man3ext)
	$(RM) $(DESTDIR)$(man3dir)/history$(man3ext)
	-if test -n "${htmldir}" ; then \
		$(RM) $(DESTDIR)$(htmldir)/readline.html ; \
		$(RM) $(DESTDIR)$(htmldir)/rluserman.html ; \
		$(RM) $(DESTDIR)$(htmldir)/history.html ; \
	fi
