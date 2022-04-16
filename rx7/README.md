# rx7~ - DX7 emulator external for PD based on RX/Saturno

This PD external was written by Frank Barknecht <barknech@ph-cip.uni-koeln.de>,
and RX/Saturno was written by Juan Linietsky.  rx7~ and RX/Saturno were
restored by Timothy Beyer for usage with modern versions of Pure Data.

Usage
-----

If you start "pd help-rx7~.pd" in this directory, the rx7~ object should be
created. Don't bother if [dsp] has no patch cords, it's part of IEMLIB and the
help-patch works anyway.

To install the external system-wide, type "make install".  Note that depending
on your operating system, you may need to override the values of various
variables in the Makefile as arguments to make.

rx7~ needs to load a bank file, before operation. Just send it a message "load
/path/to/bank.bnk".

After that you can select which bank to use with programm change messages:
"prog bank channel".
Example: "prog 28 2" loads programm 28 into channel 2

Play note with note-messages. Syntax: "note midinote velocity channel". 
Example: "note 60 64 1" plays a C (midi number "60") with velocity "64" on
channel 1

How do I compile rx7~.pd_[NAME_OF_OS]?
--------------------------------------

The RX tarball obtained from the previously suggested URL
http://www.reduz.com.ar/rx_saturno/rx-saturno-0.0.1.tar.gz is now part of the
distribution in the path rx-saturno (it has it's own copyright terms), with
modifications to build on modern machines.

Then run "make" on Linux, FreeBSD, or one of the other BSDs.  So far, only
CLANG++ and GNU Make on FreeBSD have been tested, but it appears likely that
BSD Make will work perfectly on this external as well.

Note that the help abstraction requires [dsp], which is available in the IEMLIB
external.  If you don't have it available, just adjust the help file
accordingly.
