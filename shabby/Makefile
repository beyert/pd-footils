# change this!!!
# CXX=g++ # -3.2
CXX=	c++
#CFLAGS=-O6  -g -march=athlon
#CFLAGS=-O2 -mcpu=pentium -g
CFLAGS=	-O2 -g
FLAGS=	-DPD

#EXTENSION=	pd_linux
EXTENSION=	pd_freebsd

LOCALBASE=	/usr/local
PREFIX=	/usr/local

INSTALL_DATA=	install -m 0644
INSTALL_LIB=	install -s -m 0644

INSTALL_EXAMPLES=	no

FLEXTLIBPATH=	${LOCALBASE}/lib

INCPATH=	${LOCALBASE}/include
PDINCPATH=	${LOCALBASE}/include/pd
FLEXTINCPATH=	${LOCALBASE}/include/flext
INCLUDES=	${INCPATH} ${FLEXTINCPATH} ${PDINCPATH}
#FLEXTLIB=	${FLEXTLIBPATH}/flext.a
FLEXTLIB=	flext.a
LIBS=	m

#PDEXTRA=	$(DESTDIR)${LOCALBASE}/lib/pd/extra
FOOTILS_PDEXTERNALSDIR=	${STAGEDIR}${PREFIX}/lib/pd-externals/footils
#FOOTILS_EXAMPLESPATH=	${STAGEDIR}${PREFIX}/share/examples/footils

TARGDIR=	./
TARGET=	$(TARGDIR)/shabby~.${EXTENSION} $(TARGDIR)/shaffy~.${EXTENSION}
SRCS=	shabby.cpp shaffy.cpp

all: $(TARGDIR) $(TARGET)

$(TARGDIR):
	mkdir $(TARGDIR)

${FLEXTLIB}:
	cp -pv ${FLEXTLIBPATH}/libflext-pd_s.a ${*}.a

$(TARGDIR)/%.o:	%.cpp
	${CXX} -c ${CFLAGS} -fPIC ${FLAGS} $(patsubst %,-I%,$(INCLUDES)) $< -o $@

$(TARGET):	${FLEXTLIB} $(patsubst %.cpp,$(TARGDIR)/%.o,$(SRCS))
	${CXX} ${LDFLAGS} -Wl,-z,notext -shared \
		${^} $(patsubst %,-l%,$(LIBS)) -o ${@}
	chmod 755 ${@}

install:	$(TARGET)
	mkdir -p ${FOOTILS_PDEXTERNALSDIR}
	${INSTALL_LIB} shabby~.${EXTENSION} ${FOOTILS_PDEXTERNALSDIR}
	${INSTALL_LIB} shaffy~.${EXTENSION} ${FOOTILS_PDEXTERNALSDIR}
	${INSTALL_DATA} shabby~-help.pd ${FOOTILS_PDEXTERNALSDIR}
	${INSTALL_DATA} shaffy~-help.pd ${FOOTILS_PDEXTERNALSDIR}
	${INSTALL_DATA} README ${FOOTILS_PDEXTERNALSDIR}/README-shabby_shaffy.txt
	${INSTALL_DATA} shaffy~-help.pd ${FOOTILS_PDEXTERNALSDIR}
	${INSTALL_DATA} shaffy~-help.pd ${FOOTILS_PDEXTERNALSDIR}
	${INSTALL_DATA} shaffy~-help.pd ${FOOTILS_PDEXTERNALSDIR}
	${INSTALL_DATA} shaffy~-help.pd ${FOOTILS_PDEXTERNALSDIR}
	${INSTALL_DATA} shaffy~-help.pd ${FOOTILS_PDEXTERNALSDIR}
	${INSTALL_DATA} shabby_shaffy-silly ${FOOTILS_PDEXTERNALSDIR}
	${INSTALL_DATA} shabby_shaffy-gadsr.pd ${FOOTILS_PDEXTERNALSDIR}
#	(test "${INSTALL_EXAMPLES}" = "yes") && (mkdir -p ${FOOTILS_EXAMPLESPATH})

.PHONY: clean
clean:
	rm -f $(TARGDIR)/*.o $(TARGET)
