todo: test hellotriangle helloviewport adaptviewport

LDLIBS=-lGL -lGLEW -lglfw

test: test.c
	gcc -o test test.c $(LDLIBS)

hellotriangle: hellotriangle.c
	gcc -o hellotriangle hellotriangle.c $(LDLIBS)

helloviewport: helloviewport.c
	gcc -o helloviewport helloviewport.c $(LDLIBS)

adaptviewport: adaptviewport.c
	gcc -o adaptviewport adaptviewport.c $(LDLIBS)

clean:
	rm -f *.o *~

cleanall: clean
	rm -f test hellotriangle helloviewport adaptviewport
