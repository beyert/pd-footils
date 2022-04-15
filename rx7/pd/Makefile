#CXX=	g++
CXX=	c++
CP=	cp -f
INSTALL_DATA=	install -m 0644
INSTALL_LIB=	install -s -m 0644
MKDIR=	mkdir -p
PREFIX=	/usr/local
LOCALBASE=	/usr/local
EXTENSION=	pd_freebsd
#STRIP_ARGS=	--strip-unneeded
STRIP_ARGS=	-s
SRCDIR=	../rx-saturno
CFLAGS=	-I${LOCALBASE}/include/pd -I${LOCALBASE}/include
CXXFLAGS=	-I/usr/include/c++/v1/ext
LDFLAGS=
PDEXTERNALSDIR=	${STAGEDIR}${PREFIX}/lib/pd-externals
FOOTILS_DESTDIR=	${PDEXTERNALSDIR}/footils

#OBJECTS=	dx7_voice.o dx7_voice_data.o dx7_voice_envelope.o \
	dx7_voice_operator.o dxt_voice_algorithm.o properties.o tables.o \
	open_bank.o midi_event.o mixer.o
OBJECTS=

all:
#	g++ -g -O2 -Wall -I../ -DHAVE_CONFIG_H -DLT_PATCH -DDEBUG -DPD -fPIC -c -o voice_init.o voice_init.cpp
	${CXX} -g -O2 -Wall ${CFLAGS} ${CXXFLAGS} -I${SRCDIR} -DHAVE_CONFIG_H -DLT_PATCH \
		-DDEBUG -DPD -fPIC -fpermissive -c -o rx7~.o rx7~.cpp
	ld ${LDFLAGS} -export_dynamic -shared -o rx7~.${EXTENSION} ${OBJECTS} rx7~.o
	strip rx7~.${EXTENSION}

install:
	@${MKDIR} ${FOOTILS_DESTDIR}
	@${INSTALL_DATA} README ${FOOTILS_DESTDIR}/README-rx7.txt
	@${INSTALL_DATA} road1.bnk ${FOOTILS_DESTDIR}/rx7-road1.bnk
	@${INSTALL_DATA} rom1a.bnk ${FOOTILS_DESTDIR}/rx7-rom1a.bnk
	@${INSTALL_DATA} road1.bnk ${FOOTILS_DESTDIR}/rx7-road1.bnk
	@${INSTALL_DATA} rx7~-help.pd ${FOOTILS_DESTDIR}
	@${INSTALL_LIB} rx7~.${EXTENSION} ${FOOTILS_DESTDIR}
