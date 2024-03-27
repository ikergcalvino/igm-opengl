todo: test hellotriangle helloviewport adaptviewport movingtriangle spinningcube

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

clean:
	rm -f *.o *~

cleanall: clean
	rm -f test hellotriangle helloviewport adaptviewport movingtriangle spinningcube
