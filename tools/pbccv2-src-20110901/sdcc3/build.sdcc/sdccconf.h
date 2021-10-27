/* sdccconf.h.  Generated from sdccconf_in.h by configure.  */
/* sdccconf_in.h.  Generated from configure.in by autoheader.  */

#ifndef SDCCCONF_HEADER
#define SDCCCONF_HEADER

/* XXX */
#define BIN2DATA_DIR DIR_SEPARATOR_STRING "../share"

/* XXX */
#define BINDIR "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/install/bin"

/* Define to 1 if your processor stores words with the most significant byte
   first (like Motorola and SPARC, unlike Intel and VAX). */
/* #undef BUILD_WORDS_BIGENDIAN */

/* XXX */
#define DATADIR "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/install/share"

/* XXX */
#define DIR_SEPARATOR_CHAR '/'

/* XXX */
#define DIR_SEPARATOR_STRING "/"

/* XXX */
#define EXEC_PREFIX "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/install"

/* Define to 1 if you have the <endian.h> header file. */
#define HAVE_ENDIAN_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `gc' library (-lgc). */
/* #undef HAVE_LIBGC */

/* Define to 1 if you have the <machine/endian.h> header file. */
/* #undef HAVE_MACHINE_ENDIAN_H */

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the `mkstemp' function. */
#define HAVE_MKSTEMP 1

/* Define to 1 if you have the `snprintf' function. */
#define HAVE_SNPRINTF 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the `strerror' function. */
#define HAVE_STRERROR 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/endian.h> header file. */
/* #undef HAVE_SYS_ENDIAN_H */

/* Define to 1 if you have the <sys/isa_defs.h> header file. */
/* #undef HAVE_SYS_ISA_DEFS_H */

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `vsnprintf' function. */
#define HAVE_VSNPRINTF 1

/* Define to 1 if you have the `vsprintf' function. */
#define HAVE_VSPRINTF 1

/* XXX */
#define INCLUDE_DIR_SUFFIX DIR_SEPARATOR_STRING "sdcc/include"

/* XXX */
#define LIB_DIR_SUFFIX DIR_SEPARATOR_STRING "sdcc/lib"

/* XXX */
#define NON_FREE_INCLUDE_DIR_SUFFIX DIR_SEPARATOR_STRING "sdcc/non-free/include"

/* XXX */
#define NON_FREE_LIB_DIR_SUFFIX DIR_SEPARATOR_STRING "sdcc/non-free/lib"

/* XXX */
#define OPT_DISABLE_AVR 1

/* XXX */
#define OPT_DISABLE_DEVICE_LIB 1

/* XXX */
#define OPT_DISABLE_DS390 1

/* XXX */
#define OPT_DISABLE_DS400 1

/* XXX */
#define OPT_DISABLE_GBZ80 1

/* XXX */
#define OPT_DISABLE_HC08 1

/* XXX */
#define OPT_DISABLE_MCS51 1

/* XXX */
#define OPT_DISABLE_PACKIHX 1

/* XXX */
#define OPT_DISABLE_PIC14 1

/* XXX */
#define OPT_DISABLE_PIC16 1

/* XXX */
#define OPT_DISABLE_SDCDB 1

/* XXX */
#define OPT_DISABLE_SDCPP 0

/* XXX */
#define OPT_DISABLE_TININative 1

/* XXX */
#define OPT_DISABLE_UCSIM 1

/* XXX */
#define OPT_DISABLE_XA51 1

/* XXX */
#define OPT_DISABLE_Z80 1

/* XXX */
#define OPT_ENABLE_DOC 0

/* XXX */
#define OPT_ENABLE_LIBGC 0

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT ""

/* Define to the full name of this package. */
#define PACKAGE_NAME ""

/* Define to the full name and version of this package. */
#define PACKAGE_STRING ""

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME ""

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION ""

/* XXX */
#define PREFIX "/home/semai/Work/REPO_HOME/asylum/OpenBlaze8/tools/install"

/* XXX */
#define PREFIX2BIN_DIR DIR_SEPARATOR_STRING "bin"

/* XXX */
#define PREFIX2DATA_DIR DIR_SEPARATOR_STRING "share"

/* Define as the return type of signal handlers (`int' or `void'). */
#define RETSIGTYPE void

/* XXX */
#define SDCC_DIR_NAME "SDCC_HOME"

/* XXX */
#define SDCC_INCLUDE_NAME "SDCC_INCLUDE"

/* XXX */
#define SDCC_LIB_NAME "SDCC_LIB"

/* XXX */
#define SDCC_VERSION_HI 3

/* XXX */
#define SDCC_VERSION_LO 0

/* XXX */
#define SDCC_VERSION_P 1

/* XXX */
#define SDCC_VERSION_STR "3.0.1"

/* The size of `char', as computed by sizeof. */
#define SIZEOF_CHAR 1

/* The size of `int', as computed by sizeof. */
#define SIZEOF_INT 4

/* The size of `long', as computed by sizeof. */
#define SIZEOF_LONG 8

/* The size of `short', as computed by sizeof. */
#define SIZEOF_SHORT 2

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* XXX */
#define STD_DS390_LIB "libds390"

/* XXX */
#define STD_DS400_LIB "libds400"

/* XXX */
#define STD_FP_LIB "libfloat"

/* XXX */
#define STD_INT_LIB "libint"

/* XXX */
#define STD_LIB "libsdcc"

/* XXX */
#define STD_LONG_LIB "liblong"

/* XXX */
#define STD_XA51_LIB "libxa51"

/* XXX */
#define TYPE_BYTE char

/* XXX */
#define TYPE_DWORD int

/* XXX */
#define TYPE_UBYTE unsigned char

/* XXX */
#define TYPE_UDWORD unsigned int

/* XXX */
#define TYPE_UWORD unsigned short

/* XXX */
#define TYPE_WORD short

/* Define to 1 if type `char' is unsigned and you are not using gcc.  */
#ifndef __CHAR_UNSIGNED__
/* # undef __CHAR_UNSIGNED__ */
#endif

#include "custom.h"
#endif /* SDCCCONF_HEADER */
