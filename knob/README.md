# Pure Data KNOB external

Version: 0.3

"knob" is a gui external for PD based on the IEMGUI-vslider included in PD.

Knob is available at http://footils.org (soon)

It was written by Frank Barknecht with help by Olaf Matthes reusing very much
IEM code by Thomas Musil.

## CHANGELOG

Version: 0.3.1
  *  Restore external on modern versions of Pure Data
  *  Port to FreeBSD

Version: 0.3
  *  Loadbang works
  *  Works with Pd-0.36

Version: 0.02
  *  Olaf Matthes made an external out of the previous patch to the PD sources
  and wrote the makefile.  Still you need the sources of PD in reach, to
  build the external as some non standard headers in the source are used.

  * While moving the knob, the dial line is now in the correct position.

## INSTALLATION

Edit the "Makefile" and put the correct path to the pd-sources at the top.
Then on Linux just issue "make" or on FreeBSD "gmake"

## BUGS

Apart from dirty code, a serious bug is that knob changes inlet values a bit on
the way to the outlet.  So don't expect immutable behaviour for now.

## LICENSE

(Pure Data 0.35 license)

This software is copyrighted by Miller Puckette and others.  The following
terms apply to all files associated with the software unless explicitly
disclaimed in individual files.

The authors hereby grant permission to use, copy, modify, distribute, and
license this software and its documentation for any purpose, provided that
existing copyright notices are retained in all copies and that this notice is
included verbatim in any distributions. No written agreement, license, or
royalty fee is required for any of the authorized uses.  Modifications to this
software may be copyrighted by their authors and need not follow the licensing
terms described here, provided that the new terms are clearly indicated on the
first page of each file where they apply.

IN NO EVENT SHALL THE AUTHORS OR DISTRIBUTORS BE LIABLE TO ANY PARTY FOR
DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES ARISING OUT OF
THE USE OF THIS SOFTWARE, ITS DOCUMENTATION, OR ANY DERIVATIVES THEREOF, EVEN
IF THE AUTHORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

THE AUTHORS AND DISTRIBUTORS SPECIFICALLY DISCLAIM ANY WARRANTIES, INCLUDING,
BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
PARTICULAR PURPOSE, AND NON-INFRINGEMENT.  THIS SOFTWARE IS PROVIDED ON AN "AS
IS" BASIS, AND THE AUTHORS AND DISTRIBUTORS HAVE NO OBLIGATION TO PROVIDE
MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.

RESTRICTED RIGHTS: Use, duplication or disclosure by the government is subject
to the restrictions as set forth in subparagraph (c) (1) (ii) of the Rights in
Technical Data and Computer Software Clause as DFARS 252.227-7013 and FAR
52.227-19.
