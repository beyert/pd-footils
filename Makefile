all:
	${MAKE} -C knob
	${MAKE} -C rx7
	${MAKE} -C fluid
	${MAKE} -C shabby
	${MAKE} -C syncgrain

clean:
	${MAKE} -C knob clean
	${MAKE} -C rx7 clean
	${MAKE} -C fluid clean
	${MAKE} -C shabby clean
	${MAKE} -C syncgrain clean

install: 
	${MAKE} -C knob install
	${MAKE} -C rx7 install
	${MAKE} -C fluid install
	${MAKE} -C shabby install 
	${MAKE} -C syncgrain install 
