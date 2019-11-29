all:
	g++ -std=c++11 main.cpp -o VraxapsaIII -lglut -lGLU -lGL -lm
run:
	./VraxapsaIII

clean:
	rm -f VraxapsaIII
