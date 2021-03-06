OMGWTF2A
========

OMGWTF2 contest entry.

MANIFEST
========

README.txt     This file.
coinFlip.c     Source code for application.
Makefile       Makefile for application.
ode-0.12/      Open Dynamics Engine library and include files.
coinFlip       64 bit Linux executable.
coinFlip32     32 bit Linux executable.
drawstuff.cpp,
drawstuff.h,
internal.h,
version.h,
x11.cpp        Source code for ode's drawstuff support code, hacked^H^H^H^H^H^H
               customized.

RUNNING THE APPLICATION
=======================

"coinFlip" is a 64 bit Linux executable that does OpenGL graphics, so a remote
virtual machine will probably not be a satisfying experience. It should
compile correctly on a 32 bit machine. "coinFlip32" is a 32 bit Linux
executable.

The application requires that the GL, GLU and X11 libraries be installed.

Git the executable "coinFlip" or "coinFlip32" and the textures/ subdirectory
from github. Run it:

   ./coinFlip
 or
   ./coinFlip32

The program will flip a coin and tell you the results.

NB: There are some missing constraints in the model, and the simulation 
will sometimes explode.


ABOUT THE APPLICATION
=====================

The application flips a coin, using the ode physics simulation package
(http://www.ode.org). 



