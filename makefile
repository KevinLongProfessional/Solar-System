CC = g++
C++ = g++ 

LDLIBS = -lglut -lGL -lGLU -lX11 -lm 
OPT= -O3  
DEFS= -DLIGHTING -DTEXTURE

HEADERS = 
OBJS = 

solar: solar.o $(HEADERS) $(OBJS)
	$(CC) $(OPT) solar.o -o solar $(OBJS) $(LDLIBS) 

solar.o : solar.cc $(OBJS)
	$(CC) $(OPT) solar.cc -c






