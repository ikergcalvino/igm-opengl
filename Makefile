todo: test hellotriangle helloviewport adaptviewport movingtriangle \
	spinningcube hellotexture hellotexture2 multitex multitex2

LDLIBS=-lGL -lGLEW -lglfw -lm

test: test.c
	gcc -o test test.c $(LDLIBS)

hellotriangle: hellotriangle.c
	gcc -o hellotriangle hellotriangle.c $(LDLIBS)

helloviewport: helloviewport.c
	gcc -o helloviewport helloviewport.c $(LDLIBS)

adaptviewport: adaptviewport.c
	gcc -o adaptviewport adaptviewport.c $(LDLIBS)

movingtriangle: movingtriangle.c
	gcc -o movingtriangle movingtriangle.c $(LDLIBS)

spinningcube: spinningcube.cpp
	g++ -o spinningcube spinningcube.cpp $(LDLIBS)

hellotexture: hellotexture.c
	gcc -o hellotexture hellotexture.c $(LDLIBS)

hellotexture2: hellotexture2.c
	gcc -o hellotexture2 hellotexture2.c $(LDLIBS)

multitex: multitex.c
	gcc -o multitex multitex.c $(LDLIBS)

multitex2: multitex2.c
	gcc -o multitex2 multitex2.c $(LDLIBS)

clean:
	rm -f *.o *~

cleanall: clean
	rm -f test hellotriangle helloviewport adaptviewport movingtriangle \
		spinningcube hellotexture hellotexture2 multitex multitex2
