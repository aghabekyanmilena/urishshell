## -*- text -*- ##
# Master Makefile for the GNU readline library.
# Copyright (C) 1994-2018 Free Software Foundation, Inc.

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

RL_LIBRARY_VERSION = 8.2
RL_LIBRARY_NAME = readline

PACKAGE = readline
VERSION = 8.2

PACKAGE_BUGREPORT = bug-readline@gnu.org
PACKAGE_NAME = readline
PACKAGE_STRING = readline 8.2
PACKAGE_VERSION = 8.2

PACKAGE_TARNAME = readline

srcdir = .

top_srcdir = .
BUILD_DIR = /home/atseruny/Desktop/minishell/libraries/readline-8.2

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL}
INSTALL_DATA = ${INSTALL} -m 644

CC = gcc
RANLIB = ranlib
AR = ar
ARFLAGS = cr
RM = rm -f
CP = cp
MV = mv


SHELL = /bin/sh

prefix = /home/atseruny/Desktop/minishell/libraries/readline
exec_prefix = ${prefix}

datarootdir = ${prefix}/share

bindir = ${exec_prefix}/bin
libdir = ${exec_prefix}/lib
mandir = ${datarootdir}/man
includedir = ${prefix}/include
datadir = ${datarootdir}
localedir = ${datarootdir}/locale
pkgconfigdir = ${libdir}/pkgconfig

infodir = ${datarootdir}/info

docdir = ${datarootdir}/doc/${PACKAGE_TARNAME}

man3dir = $(mandir)/man3

# Support an alternate destination root directory for package building
DESTDIR =

# Programs to make tags files.
ETAGS = etags
CTAGS = ctags -w

CFLAGS = -g -O2 -Wno-parentheses -Wno-format-security -Wno-tautological-constant-out-of-range-compare
LOCAL_CFLAGS =  -DRL_LIBRARY_VERSION='"$(RL_LIBRARY_VERSION)"' -DBRACKETED_PASTE_DEFAULT=1
CPPFLAGS = 

DEFS = -DHAVE_CONFIG_H 
LOCAL_DEFS = 

TERMCAP_LIB = -ltermcap

# For libraries which include headers from other libraries.
INCLUDES = -I. -I$(srcdir)

XCCFLAGS = $(ASAN_CFLAGS) $(DEFS) $(LOCAL_DEFS) $(INCLUDES) $(CPPFLAGS)
CCFLAGS = $(XCCFLAGS) $(LOCAL_CFLAGS) $(CFLAGS)

# could add -Werror here
GCC_LINT_FLAGS = -ansi -Wall -Wshadow -Wpointer-arith -Wcast-qual \
		 -Wwrite-strings -Wstrict-prototypes \
		 -Wmissing-prototypes -Wno-implicit -pedantic
GCC_LINT_CFLAGS = $(XCCFLAGS) $(GCC_LINT_FLAGS) -g -O2 -Wno-parentheses -Wno-format-security -Wno-tautological-constant-out-of-range-compare 

ASAN_XCFLAGS = -fsanitize=address -fno-omit-frame-pointer
ASAN_XLDFLAGS = -fsanitize=address

install_examples = install-examples

.c.o:
	${RM} $@
	$(CC) -c $(CCFLAGS) $<

# The name of the main library target.
LIBRARY_NAME = libreadline.a
STATIC_LIBS = libreadline.a libhistory.a

# The C code source files for this library.
CSOURCES = $(srcdir)/readline.c $(srcdir)/funmap.c $(srcdir)/keymaps.c \
	   $(srcdir)/vi_mode.c $(srcdir)/parens.c $(srcdir)/rltty.c \
	   $(srcdir)/complete.c $(srcdir)/bind.c $(srcdir)/isearch.c \
	   $(srcdir)/display.c $(srcdir)/signals.c $(srcdir)/emacs_keymap.c \
	   $(srcdir)/vi_keymap.c $(srcdir)/util.c $(srcdir)/kill.c \
	   $(srcdir)/undo.c $(srcdir)/macro.c $(srcdir)/input.c \
	   $(srcdir)/callback.c $(srcdir)/terminal.c $(srcdir)/xmalloc.c $(srcdir)/xfree.c \
	   $(srcdir)/history.c $(srcdir)/histsearch.c $(srcdir)/histexpand.c \
	   $(srcdir)/histfile.c $(srcdir)/nls.c $(srcdir)/search.c \
	   $(srcdir)/shell.c $(srcdir)/savestring.c $(srcdir)/tilde.c \
	   $(srcdir)/text.c $(srcdir)/misc.c $(srcdir)/compat.c \
	   $(srcdir)/mbutil.c

# The header files for this library.
HSOURCES = $(srcdir)/readline.h $(srcdir)/rldefs.h $(srcdir)/chardefs.h \
	   $(srcdir)/keymaps.h $(srcdir)/history.h $(srcdir)/histlib.h \
	   $(srcdir)/posixstat.h $(srcdir)/posixdir.h $(srcdir)/posixjmp.h \
	   $(srcdir)/tilde.h $(srcdir)/rlconf.h $(srcdir)/rltty.h \
	   $(srcdir)/ansi_stdlib.h $(srcdir)/tcap.h $(srcdir)/rlstdc.h \
	   $(srcdir)/xmalloc.h $(srcdir)/rlprivate.h $(srcdir)/rlshell.h \
	   $(srcdir)/rltypedefs.h $(srcdir)/rlmbutil.h \
	   $(srcdir)/colors.h $(srcdir)/parse-colors.h

HISTOBJ = history.o histexpand.o histfile.o histsearch.o shell.o mbutil.o
TILDEOBJ = tilde.o
COLORSOBJ = colors.o parse-colors.o
OBJECTS = readline.o vi_mode.o funmap.o keymaps.o parens.o search.o \
	  rltty.o complete.o bind.o isearch.o display.o signals.o \
	  util.o kill.o undo.o macro.o input.o callback.o terminal.o \
	  text.o nls.o misc.o $(HISTOBJ) $(TILDEOBJ) $(COLORSOBJ) \
	  xmalloc.o xfree.o compat.o

# The texinfo files which document this library.
DOCSOURCE = doc/rlman.texinfo doc/rltech.texinfo doc/rluser.texinfo
DOCOBJECT = doc/readline.dvi
DOCSUPPORT = doc/Makefile
DOCUMENTATION = $(DOCSOURCE) $(DOCOBJECT) $(DOCSUPPORT)

CREATED_MAKEFILES = Makefile doc/Makefile examples/Makefile shlib/Makefile
CREATED_CONFIGURE = config.status config.h config.cache config.log \
		    stamp-config stamp-h readline.pc history.pc
CREATED_TAGS = TAGS tags

INSTALLED_HEADERS = readline.h chardefs.h keymaps.h history.h tilde.h \
		    rlstdc.h rlconf.h rltypedefs.h

OTHER_DOCS = $(srcdir)/CHANGES $(srcdir)/INSTALL $(srcdir)/README
OTHER_INSTALLED_DOCS = CHANGES INSTALL README

##########################################################################
TARGETS = static shared
INSTALL_TARGETS = install-static install-shared

all: $(TARGETS)

everything: all examples

asan:
	${MAKE} ${MFLAGS} ASAN_CFLAGS='${ASAN_XCFLAGS}' ASAN_LDFLAGS='${ASAN_XLDFLAGS}' everything

static: $(STATIC_LIBS)

libreadline.a: $(OBJECTS)
	$(RM) $@
	$(AR) $(ARFLAGS) $@ $(OBJECTS)
	-test -n "$(RANLIB)" && $(RANLIB) $@

libhistory.a: $(HISTOBJ) xmalloc.o xfree.o
	$(RM) $@
	$(AR) $(ARFLAGS) $@ $(HISTOBJ) xmalloc.o xfree.o
	-test -n "$(RANLIB)" && $(RANLIB) $@

# Since tilde.c is shared between readline and bash, make sure we compile
# it with the right flags when it's built as part of readline
tilde.o:	tilde.c
	rm -f $@
	$(CC) $(CCFLAGS) -DREADLINE_LIBRARY -c $(srcdir)/tilde.c

readline: $(OBJECTS) readline.h rldefs.h chardefs.h ./libreadline.a
	$(CC) $(CCFLAGS) -DREADLINE_LIBRARY -o $@ $(top_srcdir)/examples/rl.c ./libreadline.a ${TERMCAP_LIB}

lint:	force
	$(MAKE) $(MFLAGS) CCFLAGS='$(GCC_LINT_CFLAGS)' static

Makefile makefile: config.status $(srcdir)/Makefile.in
	CONFIG_FILES=Makefile CONFIG_HEADERS= $(SHELL) ./config.status

Makefiles makefiles: config.status $(srcdir)/Makefile.in
	@for mf in $(CREATED_MAKEFILES); do \
		CONFIG_FILES=$$mf CONFIG_HEADERS= $(SHELL) ./config.status ; \
	done

config.status: configure
	$(SHELL) ./config.status --recheck

config.h:	stamp-h

stamp-h: config.status $(srcdir)/config.h.in
	CONFIG_FILES= CONFIG_HEADERS=config.h ./config.status
	echo > $@

#$(srcdir)/configure: $(srcdir)/configure.ac	## Comment-me-out in distribution
#	cd $(srcdir) && autoconf	## Comment-me-out in distribution


shared:	force
	-test -d shlib || mkdir shlib
	( cd shlib ; ${MAKE} ${MFLAGS} all )

documentation: force
	-test -d doc || mkdir doc
	-( cd doc && $(MAKE) $(MFLAGS) )

examples: force
	-test -d examples || mkdir examples
	-(cd examples && ${MAKE} ${MFLAGS} all )

force:

install:	$(INSTALL_TARGETS)

install-headers: installdirs ${INSTALLED_HEADERS}
	for f in ${INSTALLED_HEADERS}; do \
		$(INSTALL_DATA) $(srcdir)/$$f $(DESTDIR)$(includedir)/readline ; \
	done

uninstall-headers:
	-test -n "$(includedir)" && cd $(DESTDIR)$(includedir)/readline && \
		${RM} ${INSTALLED_HEADERS}

maybe-uninstall-headers: uninstall-headers

install-pc: installdirs
	-$(INSTALL_DATA) $(BUILD_DIR)/readline.pc $(DESTDIR)$(pkgconfigdir)/readline.pc
	-$(INSTALL_DATA) $(BUILD_DIR)/history.pc $(DESTDIR)$(pkgconfigdir)/history.pc

uninstall-pc:
	-test -n "$(pkgconfigdir)" && cd $(DESTDIR)$(pkgconfigdir) && \
		${RM} readline.pc history.pc

maybe-uninstall-pc: uninstall-pc

install-static: installdirs $(STATIC_LIBS) install-headers install-doc ${install_examples} install-pc
	-$(MV) $(DESTDIR)$(libdir)/libreadline.a $(DESTDIR)$(libdir)/libreadline.old
	$(INSTALL_DATA) libreadline.a $(DESTDIR)$(libdir)/libreadline.a
	-test -n "$(RANLIB)" && $(RANLIB) $(DESTDIR)$(libdir)/libreadline.a
	-$(MV) $(DESTDIR)$(libdir)/libhistory.a $(DESTDIR)$(libdir)/libhistory.old
	$(INSTALL_DATA) libhistory.a $(DESTDIR)$(libdir)/libhistory.a
	-test -n "$(RANLIB)" && $(RANLIB) $(DESTDIR)$(libdir)/libhistory.a

installdirs: $(srcdir)/support/mkinstalldirs
	-$(SHELL) $(srcdir)/support/mkinstalldirs $(DESTDIR)$(includedir) \
		$(DESTDIR)$(includedir)/readline $(DESTDIR)$(libdir) \
		$(DESTDIR)$(infodir) $(DESTDIR)$(man3dir) $(DESTDIR)$(docdir) \
		$(DESTDIR)$(pkgconfigdir)

uninstall: uninstall-headers uninstall-doc uninstall-examples uninstall-pc
	-test -n "$(DESTDIR)$(libdir)" && cd $(DESTDIR)$(libdir) && \
		${RM} libreadline.a libreadline.old libhistory.a libhistory.old $(SHARED_LIBS)
	-( cd shlib; ${MAKE} ${MFLAGS} DESTDIR=${DESTDIR} uninstall )

install-shared: installdirs install-headers shared install-doc install-pc
	( cd shlib ; ${MAKE} ${MFLAGS} DESTDIR=${DESTDIR} install )
	
uninstall-shared: maybe-uninstall-headers maybe-uninstall-pc
	-( cd shlib; ${MAKE} ${MFLAGS} DESTDIR=${DESTDIR} uninstall )

install-examples: installdirs install-headers
	-( cd examples ; ${MAKE} ${MFLAGS} DESTDIR=${DESTDIR} install )
	
uninstall-examples: maybe-uninstall-headers
	-( cd examples; ${MAKE} ${MFLAGS} DESTDIR=${DESTDIR} uninstall )

install-doc:	installdirs
	$(INSTALL_DATA) $(OTHER_DOCS) $(DESTDIR)$(docdir)
	-( if test -d doc ; then \
		cd doc && \
		${MAKE} ${MFLAGS} infodir=$(infodir) DESTDIR=${DESTDIR} install; \
	  fi )

uninstall-doc:
	-( cd $(DESTDIR)$(docdir) && ${RM} ${OTHER_INSTALLED_DOCS} )
	-( if test -d doc ; then \
		cd doc && \
		${MAKE} ${MFLAGS} infodir=$(infodir) DESTDIR=${DESTDIR} uninstall; \
	  fi )

TAGS:	force
	-( cd $(srcdir) && $(ETAGS) $(CSOURCES) $(HSOURCES) )

tags:	force
	-( cd $(srcdir) && $(CTAGS) $(CSOURCES) $(HSOURCES) )

clean:	force
	$(RM) $(OBJECTS) $(STATIC_LIBS)
	$(RM) readline readline.exe
	( cd shlib && $(MAKE) $(MFLAGS) $@ )
	-( cd doc && $(MAKE) $(MFLAGS) $@ )
	-( cd examples && $(MAKE) $(MFLAGS) $@ )

mostlyclean: clean
	( cd shlib && $(MAKE) $(MFLAGS) $@ )
	-( cd doc && $(MAKE) $(MFLAGS) $@ )
	-( cd examples && $(MAKE) $(MFLAGS) $@ )

distclean maintainer-clean: clean
	( cd shlib && $(MAKE) $(MFLAGS) $@ )
	-( cd doc && $(MAKE) $(MFLAGS) $@ )
	-( cd examples && $(MAKE) $(MFLAGS) $@ )
	$(RM) Makefile
	$(RM) $(CREATED_CONFIGURE)
	$(RM) $(CREATED_TAGS)

readline.pc:	config.status $(srcdir)/readline.pc.in
	$(SHELL) config.status

history.pc:	config.status $(srcdir)/history.pc.in
	$(SHELL) config.status

info dvi html pdf ps:
	-( cd doc && $(MAKE) $(MFLAGS) $@ )

install-info:
install-dvi:
install-html:
install-pdf:
install-ps:
check:
installcheck:

dist:   force
	@echo Readline distributions are created using $(srcdir)/support/mkdist.
	@echo Here is a sample of the necessary commands:
	@echo bash $(srcdir)/support/mkdist -m $(srcdir)/MANIFEST -s $(srcdir) -r $(RL_LIBRARY_NAME) $(RL_LIBRARY_VERSION)
	@echo tar cf $(RL_LIBRARY_NAME)-${RL_LIBRARY_VERSION}.tar ${RL_LIBRARY_NAME}-$(RL_LIBRARY_VERSION)
	@echo gzip $(RL_LIBRARY_NAME)-$(RL_LIBRARY_VERSION).tar

# Tell versions [3.59,3.63) of GNU make not to export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:

# Dependencies
bind.o: ansi_stdlib.h posixstat.h
bind.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
bind.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h rlstdc.h
bind.o: history.h
callback.o: rlconf.h
callback.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
callback.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h rlstdc.h
compat.o: ${BUILD_DIR}/config.h
compat.o: rlstdc.h rltypedefs.h
complete.o: ansi_stdlib.h posixdir.h posixstat.h
complete.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
complete.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h rlstdc.h
display.o: ansi_stdlib.h posixstat.h
display.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
display.o: tcap.h
display.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h
display.o: history.h rlstdc.h
funmap.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h
funmap.o: rlconf.h ansi_stdlib.h rlstdc.h
funmap.o: ${BUILD_DIR}/config.h
histexpand.o: ansi_stdlib.h
histexpand.o: history.h histlib.h rlstdc.h rltypedefs.h
histexpand.o: ${BUILD_DIR}/config.h
histfile.o: ansi_stdlib.h
histfile.o: history.h histlib.h rlstdc.h rltypedefs.h
histfile.o: ${BUILD_DIR}/config.h
history.o: ansi_stdlib.h
history.o: history.h histlib.h rlstdc.h rltypedefs.h
history.o: ${BUILD_DIR}/config.h
histsearch.o: ansi_stdlib.h
histsearch.o: history.h histlib.h rlstdc.h rltypedefs.h
histsearch.o: ${BUILD_DIR}/config.h
input.o: ansi_stdlib.h
input.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
input.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h rlstdc.h
isearch.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
isearch.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h
isearch.o: ansi_stdlib.h history.h rlstdc.h
keymaps.o: emacs_keymap.c vi_keymap.c
keymaps.o: keymaps.h rltypedefs.h chardefs.h rlconf.h ansi_stdlib.h
keymaps.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h
keymaps.o: ${BUILD_DIR}/config.h rlstdc.h
kill.o: ansi_stdlib.h
kill.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
kill.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h
kill.o: history.h rlstdc.h
macro.o: ansi_stdlib.h
macro.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
macro.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h
macro.o: history.h rlstdc.h
mbutil.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
mbutil.o: readline.h keymaps.h rltypedefs.h chardefs.h rlstdc.h
misc.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h
misc.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
misc.o: history.h rlstdc.h ansi_stdlib.h
nls.o: ansi_stdlib.h
nls.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
nls.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h  
nls.o: history.h rlstdc.h  
parens.o: rlconf.h
parens.o: ${BUILD_DIR}/config.h
parens.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h rlstdc.h
readline.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h
readline.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
readline.o: history.h rlstdc.h
readline.o: posixstat.h ansi_stdlib.h posixjmp.h
rltty.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
rltty.o: rltty.h
rltty.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h rlstdc.h
savestring.o: ${BUILD_DIR}/config.h
search.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
search.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h
search.o: ansi_stdlib.h history.h rlstdc.h
shell.o: ${BUILD_DIR}/config.h
shell.o: ansi_stdlib.h
signals.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
signals.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h
signals.o: history.h rlstdc.h
terminal.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
terminal.o: tcap.h
terminal.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h
terminal.o: history.h rlstdc.h
text.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h
text.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
text.o: history.h rlstdc.h ansi_stdlib.h
tilde.o: ansi_stdlib.h
tilde.o: ${BUILD_DIR}/config.h
tilde.o: tilde.h
undo.o: ansi_stdlib.h
undo.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
undo.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h
undo.o: history.h rlstdc.h
util.o: posixjmp.h ansi_stdlib.h
util.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
util.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h rlstdc.h
vi_mode.o: rldefs.h ${BUILD_DIR}/config.h rlconf.h
vi_mode.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h
vi_mode.o: history.h ansi_stdlib.h rlstdc.h
xfree.o: ${BUILD_DIR}/config.h
xfree.o: ansi_stdlib.h
xmalloc.o: ${BUILD_DIR}/config.h
xmalloc.o: ansi_stdlib.h

colors.o: ${BUILD_DIR}/config.h colors.h
colors.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h rlstdc.h
colors.o: rlconf.h  
colors.o: ansi_stdlib.h posixstat.h
parse-colors.o: ${BUILD_DIR}/config.h colors.h parse-colors.h
parse-colors.o: rldefs.h rlconf.h
parse-colors.o: readline.h keymaps.h rltypedefs.h chardefs.h tilde.h rlstdc.h

bind.o: rlshell.h
histfile.o: rlshell.h
nls.o: rlshell.h
readline.o: rlshell.h
shell.o: rlshell.h
terminal.o: rlshell.h
histexpand.o: rlshell.h

bind.o: rlprivate.h
callback.o: rlprivate.h
complete.o: rlprivate.h
display.o: rlprivate.h
input.o: rlprivate.h
isearch.o: rlprivate.h
kill.o: rlprivate.h
macro.o: rlprivate.h
mbutil.o: rlprivate.h
misc.o: rlprivate.h
nls.o: rlprivate.h   
parens.o: rlprivate.h
readline.o: rlprivate.h
rltty.o: rlprivate.h 
search.o: rlprivate.h
signals.o: rlprivate.h
terminal.o: rlprivate.h
text.o: rlprivate.h
undo.o: rlprivate.h
util.o: rlprivate.h
vi_mode.o: rlprivate.h
colors.o: rlprivate.h
parse-colors.o: rlprivate.h

bind.o: xmalloc.h
callback.o: xmalloc.h
complete.o: xmalloc.h
display.o: xmalloc.h
funmap.o: xmalloc.h
histexpand.o: xmalloc.h
histfile.o: xmalloc.h
history.o: xmalloc.h
input.o: xmalloc.h
isearch.o: xmalloc.h
keymaps.o: xmalloc.h
kill.o: xmalloc.h
macro.o: xmalloc.h
mbutil.o: xmalloc.h
misc.o: xmalloc.h
readline.o: xmalloc.h
savestring.o: xmalloc.h
search.o: xmalloc.h
shell.o: xmalloc.h
terminal.o: xmalloc.h
text.o: xmalloc.h
tilde.o: xmalloc.h
undo.o: xmalloc.h
util.o: xmalloc.h
vi_mode.o: xmalloc.h
xfree.o: xmalloc.h
xmalloc.o: xmalloc.h
colors.o: xmalloc.h
parse-colors.o: xmalloc.h

complete.o: rlmbutil.h
display.o: rlmbutil.h
histexpand.o: rlmbutil.h
input.o: rlmbutil.h    
isearch.o: rlmbutil.h
mbutil.o: rlmbutil.h
misc.o: rlmbutil.h
readline.o: rlmbutil.h
search.o: rlmbutil.h 
text.o: rlmbutil.h
vi_mode.o: rlmbutil.h

bind.o: $(srcdir)/bind.c
callback.o: $(srcdir)/callback.c
compat.o: $(srcdir)/compat.c
complete.o: $(srcdir)/complete.c
display.o: $(srcdir)/display.c
funmap.o: $(srcdir)/funmap.c
input.o: $(srcdir)/input.c
isearch.o: $(srcdir)/isearch.c
keymaps.o: $(srcdir)/keymaps.c $(srcdir)/emacs_keymap.c $(srcdir)/vi_keymap.c
kill.o: $(srcdir)/kill.c
macro.o: $(srcdir)/macro.c
mbutil.o: $(srcdir)/mbutil.c
misc.o: $(srcdir)/misc.c
nls.o: $(srcdir)/nls.c
parens.o: $(srcdir)/parens.c
readline.o: $(srcdir)/readline.c
rltty.o: $(srcdir)/rltty.c
savestring.o: $(srcdir)/savestring.c
search.o: $(srcdir)/search.c
shell.o: $(srcdir)/shell.c
signals.o: $(srcdir)/signals.c
terminal.o: $(srcdir)/terminal.c
text.o: $(srcdir)/text.c
tilde.o: $(srcdir)/tilde.c
undo.o: $(srcdir)/undo.c
util.o: $(srcdir)/util.c
vi_mode.o: $(srcdir)/vi_mode.c
xfree.o: $(srcdir)/xfree.c
xmalloc.o: $(srcdir)/xmalloc.c

colors.o: $(srcdir)/parse-colors.c
parse-colors.o: $(srcdir)/parse-colors.c

histexpand.o: $(srcdir)/histexpand.c
histfile.o: $(srcdir)/histfile.c
history.o: $(srcdir)/history.c
histsearch.o: $(srcdir)/histsearch.c

bind.o: bind.c
callback.o: callback.c
compat.o: compat.c
complete.o: complete.c
display.o: display.c
funmap.o: funmap.c
input.o: input.c
isearch.o: isearch.c
keymaps.o: keymaps.c emacs_keymap.c vi_keymap.c
kill.o: kill.c
macro.o: macro.c
mbutil.o: mbutil.c
misc.o: misc.c
nls.o: nls.c
parens.o: parens.c
readline.o: readline.c
rltty.o: rltty.c
savestring.o: savestring.c
search.o: search.c
shell.o: shell.c
signals.o: signals.c
terminal.o: terminal.c
text.o: text.c
tilde.o: tilde.c
undo.o: undo.c
util.o: util.c
vi_mode.o: vi_mode.c
xfree.o: xfree.c
xmalloc.o: xmalloc.c

histexpand.o: histexpand.c
histfile.o: histfile.c
history.o: history.c
histsearch.o: histsearch.c
