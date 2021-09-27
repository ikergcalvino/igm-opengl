todo: test hellotriangle helloviewport adaptviewport movingtriangle spinningcube

LDLIBS=-lGL -lGLEW -lglfw -lm

clean:
	rm -f *.o *~

cleanall: clean
	rm -f test hellotriangle helloviewport adaptviewport movingtriangle spinningcube
