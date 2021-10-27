#
#
#

VERSION         = 3.0.1
VERSIONHI       = 3
VERSIONLO       = 0
VERSIONP        = 1

SHELL           = /bin/sh
CPP             = gcc -E
INSTALL         = /usr/bin/install -c
CP              = cp

top_builddir    = ../..
top_srcdir      = ../..

prefix          = /usr/local
exec_prefix     = ${prefix}
bindir          = ${exec_prefix}/bin
libdir          = ${exec_prefix}/lib
datadir         = ${datarootdir}
datarootdir     = ${prefix}/share
includedir      = ${prefix}/include
mandir          = ${datarootdir}/man
man1dir         = $(mandir)/man1
man2dir         = $(mandir)/man2
infodir         = ${datarootdir}/info

srcdir          = .

include_dir_suffix = sdcc/include

sdcc_includedir = $(DESTDIR)$(datadir)/$(include_dir_suffix)

CPPFLAGS        =  -I$(top_builddir)


# Compiling entire program or any subproject
# ------------------------------------------
all:

# Compiling and installing everything and running test
# ----------------------------------------------------
install: all installdirs
	$(CP) -r $(srcdir)/asm $(srcdir)/*.h $(sdcc_includedir)
	if [ "`grep mcs51 $(top_builddir)/ports.build`" = mcs51 ]; then \
	  $(CP) $(srcdir)/mcs51/*.h $(sdcc_includedir)/mcs51; \
	fi
	if [ "`grep ds390 $(top_builddir)/ports.build`" = ds390 ]; then \
	  $(CP) $(srcdir)/ds390/*.h $(sdcc_includedir)/ds390; \
	fi
	if [ "`grep ds400 $(top_builddir)/ports.build`" = ds400 ]; then \
	  $(CP) $(srcdir)/ds400/*.h $(sdcc_includedir)/ds400; \
	fi
	if [ "`grep xa51 $(top_builddir)/ports.build`" = xa51 ]; then \
	  $(CP) $(srcdir)/xa51/*.h $(sdcc_includedir)/xa51; \
	fi
	if [ "`grep pblaze $(top_builddir)/ports.build`" = pblaze ]; then \
	  $(CP) $(srcdir)/pblaze/*.h $(sdcc_includedir)/pblaze; \
	fi
	if [ "`grep pic14 $(top_builddir)/ports.build`" = pic14 ]; then \
	  $(CP) $(srcdir)/pic14/*.h   $(sdcc_includedir)/pic14; \
	  $(CP) $(srcdir)/pic14/*.inc $(sdcc_includedir)/pic14; \
	  $(CP) $(srcdir)/pic14/*.txt $(sdcc_includedir)/pic14; \
	  $(CP) $(srcdir)/pic14/pic14devices.txt $(sdcc_includedir)/pic14; \
	fi
	if [ "`grep pic16 $(top_builddir)/ports.build`" = pic16 ]; then \
	  $(CP) $(srcdir)/pic16/*.h $(sdcc_includedir)/pic16; \
	  $(CP) $(srcdir)/pic16/*.txt $(sdcc_includedir)/pic16; \
	fi
	if [ "`grep z80 $(top_builddir)/ports.build`" = z80 ]; then \
	  $(CP) $(srcdir)/z80/*.h $(sdcc_includedir)/z80; \
	fi
	if [ "`grep hc08 $(top_builddir)/ports.build`" = hc08 ]; then \
	  $(CP) $(srcdir)/hc08/*.h $(sdcc_includedir)/hc08; \
	fi
	rm -rf `find $(sdcc_includedir) -type d -name '.svn'`
	# some files in CVS are executable :-(
	find $(sdcc_includedir) -type f -exec chmod 644 {} \;


# Deleting all the installed files
# --------------------------------
uninstall:
	rm -rf $(sdcc_includedir)


# Performing self-test
# --------------------
check:


# Performing installation test
# ----------------------------
installcheck:


# Creating installation directories
# ---------------------------------
installdirs:
	[ -d $(sdcc_includedir) ] || mkdir -p $(sdcc_includedir)
	[ -d $(sdcc_includedir)/mcs51 ] || mkdir -p $(sdcc_includedir)/mcs51
	[ -d $(sdcc_includedir)/ds390 ] || mkdir -p $(sdcc_includedir)/ds390
	[ -d $(sdcc_includedir)/ds400 ] || mkdir -p $(sdcc_includedir)/ds400
	[ -d $(sdcc_includedir)/xa51 ] || mkdir -p $(sdcc_includedir)/xa51
	[ -d $(sdcc_includedir)/pblaze ] || mkdir -p $(sdcc_includedir)/pblaze
	[ -d $(sdcc_includedir)/pic14 ] || mkdir -p $(sdcc_includedir)/pic14
	[ -d $(sdcc_includedir)/pic16 ] || mkdir -p $(sdcc_includedir)/pic16
	[ -d $(sdcc_includedir)/z80 ] || mkdir -p $(sdcc_includedir)/z80
	[ -d $(sdcc_includedir)/hc08 ] || mkdir -p $(sdcc_includedir)/hc08


# Creating dependencies
# ---------------------
dep:

include $(srcdir)/clean.mk

# My rules
# --------


# Remaking configuration
# ----------------------
checkconf:
	@if [ -f $(top_builddir)/devel ]; then \
	  $(MAKE) -f $(srcdir)/conf.mk srcdir="$(srcdir)" top_builddir="$(top_builddir)" \
	  freshconf; \
	fi

# End of main_in.mk/main.mk
