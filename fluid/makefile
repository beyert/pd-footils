# flext tutorial examples
#
# Makefile for Linux / FreeBSD
#
# usage: make -f makefile
#
# -----------------------------------------------------

# just feed top-level variables
CXX=	c++

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

INCPATH=	${LOCALBASE}/include
PDINCPATH=	${LOCALBASE}/include/pd
#FLEXTLIB= -lflext-pd  # take threaded library for all
#FLUIDLIB=	/usr/local/lib/libfluidsynth.a
FLUIDLIB=	-L${LOCALBASE}/lib -lfluidsynth -lreadline
FLEXTINCPATH=	${LOCALBASE}/include/flext

#PDEXTRA=	$(DESTDIR)/usr/lib/pd/extra
FOOTILS_PDEXTERNALSDIR=	${STAGEDIR}${PREFIX}/lib/pd-externals/footils
FOOTILS_EXAMPLESPATH=	${STAGEDIR}${PREFIX}/share/examples/footils

# compiler+linker stuff	### EDIT! ###
#CXX=g++ #-3.2
INCLUDES=	../../../pd/src ../../grill/trunk/flext/source/
LIBPATH=
FLAGS=	-DPD 
#CFLAGS=	-O6 -fPIC
CFLAGS=	-O2 -fPIC
LIBS=m 
# need OS conditional
STRIP=	strip -s
#STRIP=	strip --strip-unneeded -R .note -R .comment

# the rest can stay untouched
# ----------------------------------------------

# all the source files from the package

EXAMPLES=	fluid

TARGETS=$(patsubst %,${OUTPATH}/%~.${EXTENSION},${EXAMPLES})

# default target
all: ${OUTPATH} ${TARGETS}

$(OUTPATH)/%~.${EXTENSION}: $(OUTPATH)/%.${EXTENSION}
	mv $^ $@

$(SRCS): $(HDRS)
	touch $@

$(OUTPATH):
	mkdir $(OUTPATH)

$(OUTPATH)/%.o: %/main.cpp
	${CXX} -c ${CFLAGS} $(FLAGS) $(patsubst %,-I%,${INCLUDES} ${INCPATH} ${FLEXTINCPATH} ${PDINCPATH}) $< -o $@

$(OUTPATH)/%.${EXTENSION}: $(OUTPATH)/%.o 
	${CXX} ${LDFLAGS} -shared $(patsubst %,-L%,${LIBPATH}) $^ $(patsubst %,-l%,${LIBS}) ${FLUIDLIB} -o $@
	${STRIP} $@
	chmod 755 $@

install-externals:
	mkdir -p ${FOOTILS_PDEXTERNALSDIR}
	${INSTALL_LIB} ${EXTENSION}/fluid~.${EXTENSION} ${FOOTILS_PDEXTERNALSDIR}
	${INSTALL_DATA} pd/fluid~-help.pd ${FOOTILS_PDEXTERNALSDIR}
	${INSTALL_DATA} pd/fluid.* ${FOOTILS_PDEXTERNALSDIR}
	(test "${INSTALL_EXAMPLES}" = "yes") && (mkdir -p ${FOOTILS_EXAMPLESPATH})
	(test "${INSTALL_EXAMPLES}" = "yes") && \
		(${INSTALL_DATA} pd/ezdac~.pd ${FOOTILS_EXAMPLESPATH}/fluid-ezdac~.pd)
	(test "${INSTALL_EXAMPLES}" = "yes") && \
		(${INSTALL_DATA} pd/simple_onthego_synth.pd \
			${FOOTILS_EXAMPLESPATH}/fluid-simple_onthego_synth.pd)

install:	install-examples-${INSTALL_EXAMPLES} install-externals

.PHONY: clean
clean:
	rm -f ${OUTPATH}/*.o ${TARGETS}
