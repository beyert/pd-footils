# flext tutorial examples
# Copyright (c) 2001-2003 Thomas Grill (xovo@gmx.net)
#
# Makefile for Linux / FreeBSD
#
# usage: make -f makefile
#
# -----------------------------------------------------

# just feed top-level variables
CXX=	c++

CC=	echo test

#EXTENSION=	pd_linux
EXTENSION=	pd_freebsd

LOCALBASE=	/usr/local
PREFIX=	/usr/local

INSTALL_DATA=	install -m 0644
INSTALL_LIB=	install -s -m 0644

# no more using these files, just feed variables here
#include config-pd-linux.txt
#include config-pd-freebsd.txt

OUTPATH=	./${EXTENSION}
INSTALL_EXAMPLES=	no

#PDPATH=${LOCALBASE}/include/pd
#PDPATH=${LOCALBASE}

FLEXTLIBPATH=	${LOCALBASE}/lib
SNDOBJLIBPATH=	${LOCALBASE}/lib

INCPATH=	${LOCALBASE}/include
PDINCPATH=	${LOCALBASE}/include/pd
FLEXTINCPATH=	${LOCALBASE}/include/flext

FOOTILS_PDEXTERNALSDIR=	${STAGEDIR}${PREFIX}/lib/pd-externals/footils
FOOTILS_EXAMPLESPATH=	${STAGEDIR}${PREFIX}/share/examples/footils

#FLEXTLIB=	${FLEXTLIBPATH}/flext.a  # take normal library 
FLEXTLIB=	flext.a  # take normal library 
#SNDOBJLIB=	${LOCALBASE}/lib/libsndobj.a
SNDOBJLIB=	libsndobj.a
SNDOBJINCPATH=	${LOCALBASE}/include/SndObj

# compiler+linker stuff	### EDIT! ###
INCLUDES=	${PDINCPATH} ${SNDOBJINCPATH} ${FLEXTINC} ${SNDOBJINCPATH}
LIBPATH=
FLAGS=	-DFLEXT_SYS=2 -DFLEXT_ATTRIBUTES
#CFLAGS=	-O6 -fno-rtti 
CFLAGS=	-O2 -fno-rtti -fPIC -DFLEXT_USE_CMEM -DFLEXT_NOGLOBALNEW
#CFLAGS+=	-mcpu=pentiumpro  # gcc 2.95
## CFLAGS+=-mcpu=pentium3 -msse  # gcc 3.2
LDFLAGS+=	-Wl,-z,notext
#LIBS=	m sndobj
LIBS=	m
#LIBS+=sndobj
# need OS conditional
STRIP=	strip -s
#STRIP=	strip --strip-unneeded -R .note -R .comment

# the rest can stay untouched
# ----------------------------------------------

# all the source files from the package

EXAMPLES=	syncgrain~
#EXAMPLES=	syncgrain
SRCS=	buftable.cpp BufSyncGrain.cpp main.cpp

#O_FILES=	$(patsubst %,$(OUTPATH)/%.o,$(EXAMPLES)/$(SRCS))

TARGETS=	$(patsubst %,$(OUTPATH)/%.${EXTENSION},$(EXAMPLES))
#TARGETS=	$(patsubst %,$(TARGDIR)/%.${EXTENSION},$(EXAMPLES))

TARGDIR=	./
# default target
#all: ${OUTPATH} ${TARGETS}
#all: ${TARGDIR} ${TARGETS}
#all: ${OUTPATH}/${TARGETS}
all: ${TARGETS}

${FLEXTLIB}:
	cp -pv ${FLEXTLIBPATH}/libflext-pd.a ${FLEXTLIB}

${SNDOBJLIB}:
	cp -pv ${SNDOBJLIBPATH}/libsndobj.a ${SNDOBJLIB}


$(OUTPATH)/%~.${EXTENSION}:	$(OUTPATH)/%.${EXTENSION}
	mv $^ $@

$(SRCS):	$(HDRS)
	touch $@

$(OUTPATH):
	mkdir $(OUTPATH)

#$(OUTPATH)/%.o:	%.cpp
$(OUTPATH)/%.o:	$(EXAMPLES)/%.cpp
	mkdir -p ${EXTENSION}
	${CXX} -c ${CFLAGS} -fPIC ${FLAGS} $(patsubst %,-I%,${INCLUDES} ${INCPATH} ${FLEXTINCPATH} ${PDINCPATH}) $< -o $@

#$(OUTPATH)/%.o:	%/main.cpp
#	echo take the day of friday ${CXX} -c ${CFLAGS} ${FLAGS} $(patsubst %,-I%,${INCLUDES} ${INCPATH} ${FLEXTINCPATH} ${PDINCPATH}) $< -o $@
#$(OUTPATH)/%.o:	%/main.cpp
#	${CXX} -c ${CFLAGS} ${FLAGS} $(patsubst %,-I%,${INCLUDES} ${INCPATH} ${FLEXTINCPATH} ${PDINCPATH}) $< -o $@

#$(OUTPATH)/%.${EXTENSION}:	$(OUTPATH)/buftable.o $(OUTPATH)/BufSyncGrain.o $(OUTPATH)/main.o
$(OUTPATH)/%.${EXTENSION}:	$(OUTPATH)/buftable.o $(OUTPATH)/BufSyncGrain.o $(OUTPATH)/main.o ${FLEXTLIB} $(SNDOBJLIB)
	${CXX} ${LDFLAGS} -shared $(patsubst %,-L%,$(LIBPATH)) $^ $(patsubst %,-l%,$(LIBS)) -o $@
	${STRIP} $@
	chmod 755 $@

$(OUTPATH)/%.${EXTENSION}: $(OUTPATH)/%.o
	${CXX} ${LDFLAGS} -shared $(patsubst %,-L%,${LIBPATH}) $^ $(patsubst %,-l%,${LIBS}) ${FLEXTLIB} -o $@
	${STRIP} $@
	chmod 755 $@

${EXTENSION}/syncgrain~.${EXTENSION}:	$(OUTPATH)/buftable.o $(OUTPATH)/BufSyncGrain.o $(OUTPATH)/main.o ${FLEXTLIB} $(SNDOBJLIB)
	${CXX} ${LDFLAGS} -shared $(patsubst %,-L%,${LIBPATH}) $^ $(patsubst %,-l%,${LIBS}) ${FLEXTLIB} -o $@
	${STRIP} $@
	chmod 755 $@

.PHONY: clean
clean:
	rm -f ${OUTPATH}/*.o ${TARGETS}

#INSTPATH=	${FLEXTPATH}/tutorial

#ifdef INSTPATH
#$(INSTPATH):
#	-mkdir $(INSTPATH)
#
#install:: $(INSTPATH)
#endif

#install:: $(patsubst %,$(OUTPATH)/%.${EXTENSION},$(EXAMPLES))
#	cp $^ $(INSTPATH)
#	chmod 755 $(patsubst %,$(INSTPATH)/%,$(notdir $^))
#	chown root.users $(patsubst %,$(INSTPATH)/%,$(notdir $^))

install:
	mkdir -p ${FOOTILS_PDEXTERNALSDIR}
	${INSTALL_LIB} ${EXTENSION}/syncgrain~.${EXTENSION} ${FOOTILS_PDEXTERNALSDIR}
	${INSTALL_DATA} syncgrain~-help.pd ${FOOTILS_PDEXTERNALSDIR}
	(test "${INSTALL_EXAMPLES}" = "yes") && (mkdir -p ${FOOTILS_EXAMPLESPATH})
	(test "${INSTALL_EXAMPLES}" = "yes") && \
		(${INSTALL_DATA} syncgrain.pd ${FOOTILS_EXAMPLESPATH})
