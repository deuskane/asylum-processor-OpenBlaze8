VPATH        = /home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/sdas/asranlib
srcdir       = /home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/pbccv2-src-20110901/sdcc3/sdas/asranlib
top_builddir = ../..

include $(top_builddir)/Makefile.common

CFLAGS          += -I$(srcdir)/../linksrc

OBJECTS         = asranlib.o

SOURCES         = $(patsubst %.o,%.c,$(OBJECTS))

TARGET          = $(top_builddir)/bin/asranlib$(EXEEXT)

all: $(TARGET)

install: all installdirs
	$(INSTALL) $(TARGET) `echo $(DESTDIR)$(bindir)/asranlib$(EXEEXT)|sed '$(transform)'`
	$(STRIP) `echo $(DESTDIR)$(bindir)/asranlib$(EXEEXT)|sed '$(transform)'`

# Deleting all the installed files
# --------------------------------
uninstall:
	rm -f $(DESTDIR)$(bindir)/asranlib$(EXEEXT)

# Performing self-test
# --------------------
check:


# Performing installation test
# ----------------------------
installcheck:


# Creating installation directories
# ---------------------------------
installdirs:
	$(INSTALL) -d $(DESTDIR)$(bindir)


# Creating dependencies
# ---------------------
dep:

$(TARGET): $(OBJECTS) dbuf.o dbuf_string.o
	$(CC) $(LDFLAGS) -o $@ $(OBJECTS) dbuf.o dbuf_string.o

dbuf.o: $(srcdir)/../../support/Util/dbuf.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

dbuf_string.o: $(srcdir)/../../support/Util/dbuf_string.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@


checkconf:

clean:
	rm -f *core *[%~] *.[oa] *.output
	rm -f .[a-z]*~ \#*
	rm -f $(top_builddir)/bin/asranlib$(EXEEXT)

distclean realclean: clean
	rm -f Makefile
