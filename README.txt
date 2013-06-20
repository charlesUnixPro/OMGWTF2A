OMGWTF2A
========

OMGWTF2 contest entry.

MANIFEST
========

README.txt     This file.
coinFlip.c     Source code for application.
Makefile       Makefile for application.
ode-0.12/      Open Dynamics Engine source code, with hacked^H^H^H^H^H^H
               customized drawstuff library.

SPECIAL NOTE ABOUT ode-0.12/
============================

The standard ode library distributions don't include the "drawstuff" library,
which is intended as a development tool rather then an application framework.
But the purposes of this contest (looming deadlines), I need the drawstuff
code.

RUNNING THE APPLICATION
=======================

This is a 64 bit Linux executable that does OpenGL graphics, so a remote
virtual machine will probably not be a satisfying experience. It should
compile fine correctly on a 32 bit machine.

Git the executable "coinFlip" from github. Run it:

   ./coinFlip

The program will flip a coin and tell you the results.

However, the are some missing constraints in the model, and the simulation 
will sometimes explode.


ABOUT THE APPLICATION
=====================

The application flips a coin, using a physics simulation package. 



