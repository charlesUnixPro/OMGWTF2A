all : coinFlip coinFlip32

coinFlip : coinFlip.c
	c++ coinFlip.c drawstuff.cpp x11.cpp -o coinFlip -Wall \
		-I./ode-0.12/include/ \
		-DdSINGLE \
		-lode -lGL -lGLU  -lX11

coinFlip32 : coinFlip.c
	c++ coinFlip.c drawstuff.cpp x11.cpp -o coinFlip32 -Wall -m32 \
		-I./ode-0.12/include/ \
		-DdSINGLE \
		-lode -lGL -lGLU  -lX11

