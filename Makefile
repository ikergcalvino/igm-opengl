todo: spinningcube

LDLIBS=-lGL -lGLEW -lglfw -lm

spinningcube: spinningcube.cpp
	g++ -o spinningcube spinningcube.cpp $(LDLIBS)

clean:
	rm -f *.o *~

cleanall: clean
	rm -f spinningcube
