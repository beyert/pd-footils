This project consists of Pure Data externals, written by Frank Barknecht,
packaged by different authors, and restored by Timothy Beyer.  RX/Saturno was
written by Juan Linietsky.

This library is an attempt to restore these useful libraries, ensuring that
they build using modern tools, with an extensive reworking of the build system
of each respective project with portability and preservation in mind.

Note that the licenses differ substantially between each project.

Timothy Beyer 2022-04-14

## Description of externals

knob: one of the earliest and best knob externals (Pure Data 0.35 license;
permissive and likely copyfree compatible), similar yet distinct from
flatgui/knob and abctools/abcknob

rx7~: DX7 emulator external for Pure Data based on RX/Saturno 0.0.1 (rx7~
appears to have a permissive license, though rx-saturno's license is GNU GPLv2)

shabby~: Waveshaper using 11 Chebychev polynomials to generate harmonics from
an incoming sinewave.  May be used to make a rudimentary additive synth with
signal rate control over harmonics.

shaffy~: Waveshaper using 9 Chebychev polynomials to generate harmonics from an
incoming sinewave.  Maybe used as an additive synth for wind-like sounds.

syncgrain~: granular synth (GNU GPLv2 license)

fluid~: A fluidsynth soundfont (SF2) player (GNU GPLv2+ license)

## Status of Externals

knob: runs perfectly as far as I can tell, from the first time it was run, and well before the other externals

rx7~: now runs perfectly with sound; initially was missing files from RX-Saturno, and since more object files needed to be built, more patching was required, but the end result is that it builds and runs properly

shabby~: almost working!  The flext runtime errors have been resolved in using the statically-linked non-debug static version, but gives "Too many creation arguments" error at runtime

shaffy~: almost working!  The flext runtime errors have been resolved in using the statically-linked non-debug static version, but gives "Too many creation arguments" error at runtime

syncgrain~: now runs perfectly with sound; required flext runtime errors to be resolved in using the statically-linked non-debug static version

fluid~: now runs perfectly with sound; required flext runtime errors to be resolved in using the statically-linked non-debug static version, but also needed flext to be linked against the generated executable in the build system

## Building

  *  currently GNU Make is required, although I'm trying to support BSD Make as well

### Dependencies

You need to install a modern version of Pure Data, libsndobj (with -fPIC
support), flext (compiled with sndobj support, preferrably also with STK
support, and -fPIC support; for shabby~, shaffy~ and syncgrain~ externals,
which need a C++ binding), fluidsynth (needed for fluidsynth~)

### FreeBSD Port

FreeBSD ports for this port (audio/pd-footils), for audio/pd (I will soon
release modern version with full MIDI support), audio/pd-portmidi-sndio,
audio/pd-flext, audio/sndobj and numerous other PD externals will be
released soon.
