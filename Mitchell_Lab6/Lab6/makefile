all: lab6 time
lab6: Mitchell_Lab6.o
	g++ Mitchell_Lab6.o -o lab6
time: Timing.o
	g++ Timing.o -o time
Mitchell_Lab6.o: Mitchell_Lab6.cpp
	g++ -c Mitchell_Lab6.cpp
Timing.o: Timing.cpp
	g++ Timing.cpp
clean:
	rm -f *o *~ lab* time
