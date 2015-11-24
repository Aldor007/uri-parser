all: performance example

example: example.cpp
	g++ -o $@ example.cpp -I ../

performance: performance.cpp
	g++ -o $@ performance.cpp -I ../

clean:
	rm example performance
