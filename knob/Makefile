NAME=knob
CSYM=knob

# !!!
# change these two
PD_DIR=../../../pd
PREFIX=	/usr/local
LOCALBASE=	/usr/local
INSTALL_EXAMPLES=	no
PDEXTERNALSDIR=	${STAGEDIR}${PREFIX}/lib/pd-externals
FOOTILS_DESTDIR=	${PDEXTERNALSDIR}/footils
FOOTILS_EXAMPLESPATH=	${STAGEDIR}${PREFIX}/share/examples/footils
#current: pd_nt pd_linux pd_freebsd
current: pd_freebsd

# ----------------------- NT -----------------------

pd_nt: $(NAME).dll

.SUFFIXES: .dll

PDNTCFLAGS = /W3 /WX /O2 /G6 /DNT /DPD /nologo

# where is VC++ ???
VC="C:\Programme\Microsoft Visual Studio\VC98"

# where is your m_pd.h ???
PDNTINCLUDE = /I. /Ic:\pd\tcl\include /Ic:\pd\src /I$(VC)\include /Iinclude

PDNTLDIR = $(VC)\Lib
PDNTLIB = $(PDNTLDIR)\libc.lib \
	$(PDNTLDIR)\oldnames.lib \
	$(PDNTLDIR)\kernel32.lib \
	$(PDNTLDIR)\user32.lib \
	$(PDNTLDIR)\uuid.lib \
	$(PDNTLDIR)\ws2_32.lib \
	c:\pd\bin\pd.lib

.c.dll:
	cl $(PDNTCFLAGS) $(PDNTINCLUDE) /c $*.c
	link /dll /export:$(CSYM)_setup $*.obj $(PDNTLIB)

# ----------------------- IRIX 5.x -----------------------

pd_irix5: $(NAME).pd_irix5

.SUFFIXES: .pd_irix5

SGICFLAGS5 = -o32 -DPD -DUNIX -DIRIX -O2

SGIINCLUDE =  -I../../src

.c.pd_irix5:
	cc $(SGICFLAGS5) $(SGIINCLUDE) -o $*.o -c $*.c
	ld -elf -shared -rdata_shared -o $*.pd_irix5 $*.o
	rm $*.o

# ----------------------- IRIX 6.x -----------------------

pd_irix6: $(NAME).pd_irix6

.SUFFIXES: .pd_irix6

SGICFLAGS6 = -n32 -DPD -DUNIX -DIRIX -DN32 -woff 1080,1064,1185 \
	-OPT:roundoff=3 -OPT:IEEE_arithmetic=3 -OPT:cray_ivdep=true \
	-Ofast=ip32

.c.pd_irix6:
	cc $(SGICFLAGS6) $(SGIINCLUDE) -o $*.o -c $*.c
	ld -n32 -IPA -shared -rdata_shared -o $*.pd_irix6 $*.o
	rm $*.o

# ------------------------- LINUX --------------------------

pd_linux: $(NAME).pd_linux

.SUFFIXES: .pd_linux

LINUXCFLAGS = -DPD -DUNIX -O2 -funroll-loops -fomit-frame-pointer \
    -Wall -W -Wshadow -Wstrict-prototypes -Werror \
    -Wno-unused -Wno-parentheses -Wno-switch

# where is your m_pd.h ???
LINUXINCLUDE =  -I../../src -I$(PD_DIR)/src

.c.pd_linux:
	cc -O2 -Wall -DPD -fPIC $(LINUXINCLUDE) -c $*.c 
	ld --export-dynamic  -shared -o $*.pd_linux $*.o -lc 
	strip $*.pd_linux

# ------------------------ FreeBSD -------------------------

pd_freebsd: $(NAME).pd_freebsd

.SUFFIXES: .pd_freebsd

FreeBSDCFLAGS = -DPD -DUNIX -DFreeBSD -O2 -funroll-loops \
	-fomit-frame-pointer -Wall -W -Wshadow \
	-Wstrict-prototypes -Wno-unused -Wno-parentheses -Wno-switch

# where is your m_pd.h ???
FreeBSDINCLUDE=	-I${LOCALBASE}/include/pd -I${PD_DIR}/src
FreeBSDLDFLAGS=	-L${LOCALBASE}/lib -L/usr/lib -lc

.c.pd_freebsd:
	cc -O2 -Wall -DPD -fPIC ${FreeBSDINCLUDE} -c $*.c
	ld ${FreeBSDLDFLAGS} --export-dynamic -shared -o $*.pd_freebsd \
		$*.o -lc
	strip -s $*.pd_freebsd

# ----------------------------------------------------------

install:
	mkdir -p ${FOOTILS_DESTDIR}
	cp -p ${NAME}*.pd_* ${FOOTILS_DESTDIR}
	cp -p ${NAME}-help.pd ${FOOTILS_DESTDIR}
	cp -p README ${FOOTILS_DESTDIR}/README-knob.txt
	(test "${INSTALL_EXAMPLES}" = "yes") && \
		(mkdir -p ${FOOTILS_EXAMPLESPATH}) || (echo "do not install examples")
	(test "${INSTALL_EXAMPLES}" = "yes") && \
		(cp -p clock.pd ${FOOTILS_EXAMPLESPATH}/knob-clock.pd) || \
		(echo "do not install examples")


clean:
	rm -f *.o *.pd_*
