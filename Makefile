todo: test hellotriangle

LDLIBS=-lGL -lGLEW -lglfw

test: test.c
	gcc -o test test.c $(LDLIBS)

hellotriangle: hellotriangle.c
	gcc -o hellotriangle hellotriangle.c $(LDLIBS)

clean:
	rm -f *.o *~

cleanall: clean
	rm -f test hellotriangle
