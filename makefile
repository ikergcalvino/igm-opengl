todo: test hellotriangle

LDLIBS=-lGL -lGLEW -lglfw

clean:
	rm -f *.o *~

cleanall: clean
	rm -f test hellotriangle
