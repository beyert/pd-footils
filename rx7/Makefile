CXX=	c++
CP=	cp -f
LD=	ld
STRIP_CMD=	strip
INSTALL_DATA=	install -m 0644
INSTALL_LIB=	install -s -m 0644
MKDIR=	mkdir -p
PREFIX=	/usr/local
LOCALBASE=	/usr/local
EXTENSION=	pd_freebsd
#STRIP_ARGS=	--strip-unneeded
STRIP_ARGS=	-s
STRIP=	${STRIP_CMD} ${STRIP_ARGS}
#RXDIR=	../rx-saturno
RXDIR=	rx-saturno
CFLAGS=	-I${LOCALBASE}/include/pd -I${LOCALBASE}/include
CXXFLAGS=	-I/usr/include/c++/v1/ext
LDFLAGS=
PDEXTERNALSDIR=	${STAGEDIR}${PREFIX}/lib/pd-externals
FOOTILS_DESTDIR=	${PDEXTERNALSDIR}/footils

OBJECTS=	${RXDIR}/dx7_voice.o \
	${RXDIR}/dx7_voice_data.o \
	${RXDIR}/dx7_voice_envelope.o \
	${RXDIR}/dx7_voice_operator.o \
	${RXDIR}/dxt_voice_algorithm.o \
	${RXDIR}/properties.o ${RXDIR}/tables.o ${RXDIR}/open_bank.o \
	${RXDIR}/midi_event.o ${RXDIR}/mixer.o
SOURCES=	${OBJECTS:.cpp=.o}

all:	${OBJECTS} rx7

.SUFFIXES:	.cpp .o
.cpp.o:
	${CXX} -g -O2 -Wall ${CFLAGS} ${CXXFLAGS} -I${RXDIR} -DHAVE_CONFIG_H \
		-DLT_PATCH -DDEBUG -DPD -fPIC -fpermissive -c -o ${*}.o ${*}.cpp

rx7:
	${CXX} -g -O2 -Wall ${CFLAGS} ${CXXFLAGS} -I${RXDIR} -DHAVE_CONFIG_H \
		-DLT_PATCH -DDEBUG -DPD -fPIC -fpermissive -c -o rx7~.o rx7~.cpp
	${LD} ${LDFLAGS} --export-dynamic --shared -o rx7~.${EXTENSION} \
		${OBJECTS} rx7~.o
	${STRIP} rx7~.${EXTENSION}

install:
	@${MKDIR} ${FOOTILS_DESTDIR}
	@${INSTALL_DATA} README.md ${FOOTILS_DESTDIR}/README-rx7.md
	@${INSTALL_DATA} road1.bnk ${FOOTILS_DESTDIR}/rx7-road1.bnk
	@${INSTALL_DATA} rom1a.bnk ${FOOTILS_DESTDIR}/rx7-rom1a.bnk
	@${INSTALL_DATA} road1.bnk ${FOOTILS_DESTDIR}/rx7-road1.bnk
	@${INSTALL_DATA} rx7~-help.pd ${FOOTILS_DESTDIR}
	@${INSTALL_LIB} rx7~.${EXTENSION} ${FOOTILS_DESTDIR}
