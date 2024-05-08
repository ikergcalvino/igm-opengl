CXXFLAGS=-Wall
LDLIBS=-losg -losgViewer -losgDB

all: spinningcube

spinningcube: spinningcube.cpp
	g++ -o $@ $< $(CXXFLAGS) $(LDLIBS)

clean:
	rm -f *.o *~

cleanall: clean
	rm -f spinningcube
