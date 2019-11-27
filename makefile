cachesim.out: main.o processor.o core.o
	g++ -o cachesim.out main.o processor.o core.o -I include/

main.o: main/main.cpp processor.o
	g++ -c main/main.cpp -I include/

core.o: source/core.cpp
	g++ -c source/core.cpp -I include/

processor.o: source/processor.cpp core.o
	g++ -c source/processor.cpp -I include/

clean:
	rm *.o