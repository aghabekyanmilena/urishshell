## -*- text -*- ##
# Makefile for the GNU readline library shared library support.
#
# Copyright (C) 1998-2009 Free Software Foundation, Inc.

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

PACKAGE = readline
VERSION = 8.2

PACKAGE_BUGREPORT = bug-readline@gnu.org
PACKAGE_NAME = readline
PACKAGE_STRING = readline 8.2
PACKAGE_VERSION = 8.2

RL_LIBRARY_VERSION = 8.2
RL_LIBRARY_NAME = readline

datarootdir = ${prefix}/share

srcdir = .
VPATH = ..
topdir = ..
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
LN = ln

SHELL = /bin/sh

host_os = linux-gnu
host_vendor = pc

prefix = /home/atseruny/Desktop/minishell/libraries/readline
exec_prefix = ${prefix}
includedir = ${prefix}/include
bindir = ${exec_prefix}/bin
libdir = ${exec_prefix}/lib
datadir = ${datarootdir}
localedir = ${datarootdir}/locale

# Support an alternate destination root directory for package building
DESTDIR =

CFLAGS = -g -O2 -Wno-parentheses -Wno-format-security -Wno-tautological-constant-out-of-range-compare
LOCAL_CFLAGS =  -DRL_LIBRARY_VERSION='"$(RL_LIBRARY_VERSION)"' -DBRACKETED_PASTE_DEFAULT=1
CPPFLAGS = 
LDFLAGS =   -g -O2 -Wno-parentheses -Wno-format-security -Wno-tautological-constant-out-of-range-compare

DEFS = -DHAVE_CONFIG_H 
LOCAL_DEFS = 

#
# These values are generated for configure by ${topdir}/support/shobj-conf.
# If your system is not supported by that script, but includes facilities for
# dynamic loading of shared objects, please update the script and send the
# changes to bash-maintainers@gnu.org.
#
SHOBJ_CC = gcc
SHOBJ_CFLAGS = -fPIC
SHOBJ_LD = ${CC}

SHOBJ_LDFLAGS = -shared -Wl,-soname,$@
SHOBJ_XLDFLAGS = 
SHOBJ_LIBS = 

SHLIB_XLDFLAGS =  -Wl,-rpath,$(libdir) -Wl,-soname,`basename $@ $(SHLIB_MINOR)`
SHLIB_LIBS =  

SHLIB_DOT = .
SHLIB_LIBPREF = lib
SHLIB_LIBSUFF = so

SHLIB_LIBVERSION = $(SHLIB_LIBSUFF).$(SHLIB_MAJOR)$(SHLIB_MINOR)
SHLIB_DLLVERSION = $(SHLIB_MAJOR)

SHLIB_STATUS = supported

TERMCAP_LIB = -ltermcap

# shared library versioning
SHLIB_MAJOR=		8
# shared library systems like SVR4's do not use minor versions
SHLIB_MINOR=		.2

# For libraries which include headers from other libraries.
INCLUDES = -I. -I.. -I$(topdir)

CCFLAGS = $(DEFS) $(LOCAL_DEFS) $(INCLUDES) $(CPPFLAGS) $(LOCAL_CFLAGS) $(CFLAGS)

.SUFFIXES:	.so

.c.so:
	${RM} $@
	$(SHOBJ_CC) -c $(CCFLAGS) $(SHOBJ_CFLAGS) -o $*.o $< 
	$(MV) $*.o $@

# The name of the main library target.

SHARED_READLINE = $(SHLIB_LIBPREF)readline$(SHLIB_DOT)$(SHLIB_LIBVERSION)
SHARED_HISTORY = $(SHLIB_LIBPREF)history$(SHLIB_DOT)$(SHLIB_LIBVERSION)
SHARED_LIBS = $(SHARED_READLINE) $(SHARED_HISTORY)

# The C code source files for this library.
CSOURCES = $(topdir)/readline.c $(topdir)/funmap.c $(topdir)/keymaps.c \
	   $(topdir)/vi_mode.c $(topdir)/parens.c $(topdir)/rltty.c \
	   $(topdir)/complete.c $(topdir)/bind.c $(topdir)/isearch.c \
	   $(topdir)/display.c $(topdir)/signals.c $(topdir)/emacs_keymap.c \
	   $(topdir)/vi_keymap.c $(topdir)/util.c $(topdir)/kill.c \
	   $(topdir)/undo.c $(topdir)/macro.c $(topdir)/input.c \
	   $(topdir)/callback.c $(topdir)/terminal.c $(topdir)/xmalloc.c $(topdir)/xfree.c \
	   $(topdir)/history.c $(topdir)/histsearch.c $(topdir)/histexpand.c \
	   $(topdir)/histfile.c $(topdir)/nls.c $(topdir)/search.c \
	   $(topdir)/shell.c $(topdir)/savestring.c $(topdir)/tilde.c \
	   $(topdir)/text.c $(topdir)/misc.c $(topdir)/compat.c \
	   $(topdir)/colors.c $(topdir)/parse-colors.c \
	   $(topdir)/mbutil.c

# The header files for this library.
HSOURCES = $(topdir)/readline.h $(topdir)/rldefs.h $(topdir)/chardefs.h \
	   $(topdir)/keymaps.h $(topdir)/history.h $(topdir)/histlib.h \
	   $(topdir)/posixstat.h $(topdir)/posixdir.h $(topdir)/posixjmp.h \
	   $(topdir)/tilde.h $(topdir)/rlconf.h $(topdir)/rltty.h \
	   $(topdir)/ansi_stdlib.h $(topdir)/tcap.h $(topdir)/rlstdc.h \
	   $(topdir)/xmalloc.h $(topdir)/rlprivate.h $(topdir)/rlshell.h \
	   $(topdir)/rltypedefs.h $(topdir)/rlmbutil.h \
           $(topdir)/colors.h $(topdir)/parse-colors.h

SHARED_HISTOBJ = history.so histexpand.so histfile.so histsearch.so shell.so \
		 mbutil.so
SHARED_TILDEOBJ = tilde.so
SHARED_COLORSOBJ = colors.so parse-colors.so
SHARED_OBJ = readline.so vi_mode.so funmap.so keymaps.so parens.so search.so \
	  rltty.so complete.so bind.so isearch.so display.so signals.so \
	  util.so kill.so undo.so macro.so input.so callback.so terminal.so \
	  text.so nls.so misc.so \
	  $(SHARED_HISTOBJ) $(SHARED_TILDEOBJ) $(SHARED_COLORSOBJ) \
	  xmalloc.so xfree.so compat.so

##########################################################################

all: $(SHLIB_STATUS)

supported: $(SHARED_LIBS)

unsupported:
	@echo "Your system and compiler (${host_os}-${CC}) are not supported by the"
	@echo "${topdir}/support/shobj-conf script."
	@echo "If your operating system provides facilities for creating"
	@echo "shared libraries, please update the script and re-run configure."
	@echo "Please send the changes you made to bash-maintainers@gnu.org"
	@echo "for inclusion in future bash and readline releases."

$(SHARED_READLINE):	$(SHARED_OBJ)
	$(RM) $@
	$(SHOBJ_LD) ${SHOBJ_LDFLAGS} ${SHLIB_XLDFLAGS} -o $@ $(SHARED_OBJ) $(SHLIB_LIBS)

$(SHARED_HISTORY):	$(SHARED_HISTOBJ) xmalloc.so xfree.so
	$(RM) $@
	$(SHOBJ_LD) ${SHOBJ_LDFLAGS} ${SHLIB_XLDFLAGS} -o $@ $(SHARED_HISTOBJ) xmalloc.so xfree.so $(SHLIB_LIBS)

# Since tilde.c is shared between readline and bash, make sure we compile 
# it with the right flags when it's built as part of readline
tilde.so:        tilde.c
	${RM} $@
	$(SHOBJ_CC) -c $(CCFLAGS) $(SHOBJ_CFLAGS) -DREADLINE_LIBRARY -c -o tilde.o $(topdir)/tilde.c
	$(MV) tilde.o $@

installdirs: $(topdir)/support/mkdirs
	-$(SHELL) $(topdir)/support/mkdirs $(DESTDIR)$(libdir)
	-$(SHELL) $(topdir)/support/mkdirs $(DESTDIR)$(bindir)

install-supported: installdirs $(SHLIB_STATUS)
	$(SHELL) $(topdir)/support/shlib-install -O $(host_os) -V $(host_vendor) -d $(DESTDIR)$(libdir) -b $(DESTDIR)$(bindir) -i "$(INSTALL_DATA)" $(SHARED_HISTORY)
	$(SHELL) $(topdir)/support/shlib-install -O $(host_os) -V $(host_vendor) -d $(DESTDIR)$(libdir) -b $(DESTDIR)$(bindir) -i "$(INSTALL_DATA)" $(SHARED_READLINE)
	@echo install: you may need to run ldconfig

install-unsupported:
	@echo install: shared libraries not supported

install: install-$(SHLIB_STATUS)

uninstall-supported:
	$(SHELL) $(topdir)/support/shlib-install -O $(host_os) -V $(host_vendor) -d $(DESTDIR)$(libdir) -b $(DESTDIR)$(bindir) -U $(SHARED_HISTORY)
	$(SHELL) $(topdir)/support/shlib-install -O $(host_os) -V $(host_vendor) -d $(DESTDIR)$(libdir) -b $(DESTDIR)$(bindir) -U $(SHARED_READLINE)
	@echo uninstall: you may need to run ldconfig

uninstall-unsupported:
	@echo uninstall: shared libraries not supported

uninstall: uninstall-$(SHLIB_STATUS)

clean mostlyclean:	force
	$(RM) $(SHARED_OBJ) $(SHARED_LIBS)

distclean maintainer-clean: clean
	$(RM) Makefile

force:

# Tell versions [3.59,3.63) of GNU make not to export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:

# Dependencies
bind.so: $(topdir)/ansi_stdlib.h $(topdir)/posixstat.h
bind.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
bind.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
bind.so: $(topdir)/rltypedefs.h
bind.so: $(topdir)/tilde.h $(topdir)/history.h
compat.so: ${BUILD_DIR}/config.h
compat.so: $(topdir)/rlstdc.h $(topdir)/rltypedefs.h
callback.so: $(topdir)/rlconf.h
callback.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h
callback.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
callback.so: $(topdir)/rltypedefs.h
callback.so: $(topdir)/tilde.h
complete.so: $(topdir)/ansi_stdlib.h $(topdir)/posixdir.h $(topdir)/posixstat.h
complete.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
complete.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
complete.so: $(topdir)/rltypedefs.h
complete.so: $(topdir)/tilde.h
display.so: $(topdir)/ansi_stdlib.h $(topdir)/posixstat.h
display.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
display.so: $(topdir)/tcap.h
display.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
display.so: $(topdir)/rltypedefs.h
display.so: $(topdir)/tilde.h $(topdir)/history.h
funmap.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
funmap.so: $(topdir)/rltypedefs.h
funmap.so: $(topdir)/rlconf.h $(topdir)/ansi_stdlib.h
funmap.so: ${BUILD_DIR}/config.h $(topdir)/tilde.h
histexpand.so: $(topdir)/ansi_stdlib.h
histexpand.so: $(topdir)/history.h $(topdir)/histlib.h $(topdir)/rltypedefs.h
histexpand.so: ${BUILD_DIR}/config.h
histfile.so: $(topdir)/ansi_stdlib.h
histfile.so: $(topdir)/history.h $(topdir)/histlib.h $(topdir)/rltypedefs.h
histfile.so: ${BUILD_DIR}/config.h
history.so: $(topdir)/ansi_stdlib.h
history.so: $(topdir)/history.h $(topdir)/histlib.h $(topdir)/rltypedefs.h
history.so: ${BUILD_DIR}/config.h
histsearch.so: $(topdir)/ansi_stdlib.h
histsearch.so: $(topdir)/history.h $(topdir)/histlib.h $(topdir)/rltypedefs.h
histsearch.so: ${BUILD_DIR}/config.h
input.so: $(topdir)/ansi_stdlib.h
input.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
input.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
input.so: $(topdir)/rltypedefs.h
input.so: $(topdir)/tilde.h
isearch.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
isearch.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
isearch.so: $(topdir)/rltypedefs.h
isearch.so: $(topdir)/ansi_stdlib.h $(topdir)/history.h $(topdir)/tilde.h
keymaps.so: $(topdir)/keymaps.h $(topdir)/chardefs.h $(topdir)/rlconf.h
keymaps.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
keymaps.so: $(topdir)/rltypedefs.h
keymaps.so: ${BUILD_DIR}/config.h $(topdir)/ansi_stdlib.h $(topdir)/tilde.h
kill.so: $(topdir)/ansi_stdlib.h
kill.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
kill.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
kill.so: $(topdir)/tilde.h $(topdir)/history.h  $(topdir)/rltypedefs.h
macro.so: $(topdir)/ansi_stdlib.h
macro.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
macro.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
macro.so: $(topdir)/tilde.h $(topdir)/history.h $(topdir)/rltypedefs.h
mbutil.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
mbutil.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/rltypedefs.h
mbutil.so: $(topdir)/chardefs.h $(topdir)/rlstdc.h
misc.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
misc.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
misc.so: $(topdir)/rltypedefs.h
misc.so: $(topdir)/history.h $(topdir)/tilde.h $(topdir)/ansi_stdlib.h
nls.so: $(topdir)/ansi_stdlib.h
nls.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
nls.o: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
nls.o: $(topdir)/rltypedefs.h
nls.o: $(topdir)/tilde.h $(topdir)/history.h $(topdir)/rlstdc.h  
parens.so: $(topdir)/rlconf.h ${BUILD_DIR}/config.h
parens.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
parens.so: $(topdir)/rltypedefs.h
parens.so: $(topdir)/tilde.h
rltty.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
rltty.so: $(topdir)/rltty.h $(topdir)/tilde.h
rltty.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
rltty.so: $(topdir)/rltypedefs.h
savestring.so: ${BUILD_DIR}/config.h
search.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
search.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
search.so: $(topdir)/ansi_stdlib.h $(topdir)/history.h $(topdir)/tilde.h
search.so: $(topdir)/rltypedefs.h
signals.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
signals.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
signals.so: $(topdir)/history.h $(topdir)/tilde.h
signals.so: $(topdir)/rltypedefs.h
terminal.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
terminal.so: $(topdir)/tcap.h
terminal.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
terminal.so: $(topdir)/tilde.h $(topdir)/history.h
terminal.so: $(topdir)/rltypedefs.h
text.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
text.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
text.so: $(topdir)/rltypedefs.h
text.so: $(topdir)/history.h $(topdir)/tilde.h $(topdir)/ansi_stdlib.h
tilde.so: $(topdir)/ansi_stdlib.h ${BUILD_DIR}/config.h $(topdir)/tilde.h
undo.so: $(topdir)/ansi_stdlib.h
undo.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
undo.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
undo.so: $(topdir)/rltypedefs.h
undo.so: $(topdir)/tilde.h $(topdir)/history.h
util.so: $(topdir)/posixjmp.h $(topdir)/ansi_stdlib.h
util.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
util.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
util.so: $(topdir)/rltypedefs.h $(topdir)/tilde.h
vi_mode.so: $(topdir)/rldefs.h ${BUILD_DIR}/config.h $(topdir)/rlconf.h
vi_mode.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/chardefs.h
vi_mode.so: $(topdir)/history.h $(topdir)/ansi_stdlib.h $(topdir)/tilde.h
vi_mode.so: $(topdir)/rltypedefs.h
xfree.so: ${BUILD_DIR}/config.h
xfree.so: $(topdir)/ansi_stdlib.h
xmalloc.so: ${BUILD_DIR}/config.h
xmalloc.so: $(topdir)/ansi_stdlib.h

bind.so: $(topdir)/rlshell.h
histfile.so: $(topdir)/rlshell.h
nls.so: $(topdir)/rlshell.h
readline.so: $(topdir)/rlshell.h
shell.so: $(topdir)/rlshell.h
terminal.so: $(topdir)/rlshell.h
histexpand.so: $(topdir)/rlshell.h

colors.so: $(BUILD_DIR)/config.h $(topdir)/colors.h
colors.so: $(topdir)/rlconf.h 
colors.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/rltypedefs.h
colors.so: $(topdir)/chardefs.h $(topdir)/tilde.h $(topdir)/rlstdc.h
colors.so: $(topdir)/ansi_stdlib.h $(topdir)/posixstat.h
parse-colors.so: $(BUILD_DIR)/config.h $(topdir)/colors.h $(topdir)/parse-colors.h
parse-colors.so: $(topdir)/rldefs.h $(topdir)/rlconf.h 
parse-colors.so: $(topdir)/readline.h $(topdir)/keymaps.h $(topdir)/rltypedefs.h
parse-colors.so: $(topdir)/chardefs.h $(topdir)/tilde.h $(topdir)/rlstdc.h

bind.so: $(topdir)/rlprivate.h
callback.so: $(topdir)/rlprivate.h
complete.so: $(topdir)/rlprivate.h
display.so: $(topdir)/rlprivate.h
input.so: $(topdir)/rlprivate.h
isearch.so: $(topdir)/rlprivate.h
kill.so: $(topdir)/rlprivate.h
macro.so: $(topdir)/rlprivate.h
mbutil.so: $(topdir)/rlprivate.h
misc.so: $(topdir)/rlprivate.h
nls.so: $(topdir)/rlprivate.h   
parens.so: $(topdir)/rlprivate.h
readline.so: $(topdir)/rlprivate.h
rltty.so: $(topdir)/rlprivate.h 
search.so: $(topdir)/rlprivate.h
signals.so: $(topdir)/rlprivate.h
terminal.so: $(topdir)/rlprivate.h
text.so: $(topdir)/rlprivate.h
undo.so: $(topdir)/rlprivate.h
util.so: $(topdir)/rlprivate.h
vi_mode.so: $(topdir)/rlprivate.h
colors.so: $(topdir)/rlprivate.h
parse-colors.so: $(topdir)/rlprivate.h

bind.so: $(topdir)/xmalloc.h
callback.so: $(topdir)/xmalloc.h
complete.so: $(topdir)/xmalloc.h
display.so: $(topdir)/xmalloc.h
funmap.so: $(topdir)/xmalloc.h
histexpand.so: $(topdir)/xmalloc.h
histfile.so: $(topdir)/xmalloc.h
history.so: $(topdir)/xmalloc.h
input.so: $(topdir)/xmalloc.h
isearch.so: $(topdir)/xmalloc.h
keymaps.so: $(topdir)/xmalloc.h
kill.so: $(topdir)/xmalloc.h
macro.so: $(topdir)/xmalloc.h
mbutil.so: $(topdir)/xmalloc.h
misc.so: $(topdir)/xmalloc.h
readline.so: $(topdir)/xmalloc.h
savestring.so: $(topdir)/xmalloc.h
search.so: $(topdir)/xmalloc.h
shell.so: $(topdir)/xmalloc.h
terminal.so: $(topdir)/xmalloc.h
text.so: $(topdir)/xmalloc.h
tilde.so: $(topdir)/xmalloc.h
undo.so: $(topdir)/xmalloc.h
util.so: $(topdir)/xmalloc.h
vi_mode.so: $(topdir)/xmalloc.h
xfree.so: $(topdir)/xmalloc.h
xmalloc.so: $(topdir)/xmalloc.h
colors.so: $(topdir)/xmalloc.h
parse-colors.so: $(topdir)/xmalloc.h

complete.so: $(topdir)/rlmbutil.h
display.so: $(topdir)/rlmbutil.h
histexpand.so: $(topdir)/rlmbutil.h
input.so: $(topdir)/rlmbutil.h
isearch.so: $(topdir)/rlmbutil.h
mbutil.so: $(topdir)/rlmbutil.h
misc.so: $(topdir)/rlmbutil.h
readline.so: $(topdir)/rlmbutil.h
search.so: $(topdir)/rlmbutil.h
text.so: $(topdir)/rlmbutil.h
vi_mode.so: $(topdir)/rlmbutil.h
colors.so: $(topdir)/rlmbutil.h
parse-colors.so: $(topdir)/rlmbutil.h

bind.so: $(topdir)/bind.c
callback.so: $(topdir)/callback.c
compat.so: $(topdir)/compat.c
complete.so: $(topdir)/complete.c
display.so: $(topdir)/display.c
funmap.so: $(topdir)/funmap.c
input.so: $(topdir)/input.c
isearch.so: $(topdir)/isearch.c
keymaps.so: $(topdir)/keymaps.c $(topdir)/emacs_keymap.c $(topdir)/vi_keymap.c
kill.so: $(topdir)/kill.c
macro.so: $(topdir)/macro.c
mbutil.so: $(topdir)/mbutil.c
misc.so: $(topdir)/mbutil.c
nls.so: $(topdir)/nls.c
parens.so: $(topdir)/parens.c
readline.so: $(topdir)/readline.c
rltty.so: $(topdir)/rltty.c
savestring.so: $(topdir)/savestring.c
search.so: $(topdir)/search.c
shell.so: $(topdir)/shell.c
signals.so: $(topdir)/signals.c
terminal.so: $(topdir)/terminal.c
text.so: $(topdir)/text.c
tilde.so: $(topdir)/tilde.c
undo.so: $(topdir)/undo.c
util.so: $(topdir)/util.c
vi_mode.so: $(topdir)/vi_mode.c
xfree.so: $(topdir)/xfree.c
xmalloc.so: $(topdir)/xmalloc.c

histexpand.so: $(topdir)/histexpand.c
histfile.so: $(topdir)/histfile.c
history.so: $(topdir)/history.c
histsearch.so: $(topdir)/histsearch.c

bind.so: bind.c
callback.so: callback.c
comapt.so: compat.c
complete.so: complete.c
display.so: display.c
funmap.so: funmap.c
input.so: input.c
isearch.so: isearch.c
keymaps.so: keymaps.c emacs_keymap.c vi_keymap.c
kill.so: kill.c
macro.so: macro.c
mbutil.so: mbutil.c
misc.so: misc.c
nls.so: nls.c
parens.so: parens.c
readline.so: readline.c
rltty.so: rltty.c
savestring.so: savestring.c
search.so: search.c
signals.so: signals.c
shell.so: shell.c
terminal.so: terminal.c
text.so: text.c
tilde.so: tilde.c
undo.so: undo.c
util.so: util.c
vi_mode.so: vi_mode.c
xfree.so: xfree.c
xmalloc.so: xmalloc.c

colors.so: colors.c
parse-colors.so: parse-colors.c

histexpand.so: histexpand.c
histfile.so: histfile.c
history.so: history.c
histsearch.so: histsearch.c
