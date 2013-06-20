all : coinFlip

coinFlip : coinFlip.c
	c++ coinFlip.c -o coinFlip -Wall \
		-I./ode-0.12/include/ \
		-DdSINGLE \
		./ode-0.12/ode/src/.libs/libode.a \
		./ode-0.12/drawstuff/src/.libs/libdrawstuff.a \
		-lGL -lGLU  -lX11
