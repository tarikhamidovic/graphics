make:
	g++ -Wl,--no-as-needed -lGLU -lGL -lglut -c *.cpp
	g++ -Wl,--no-as-needed -lGLU -lGL -lglut -o clock *.o
	./clock

clean:
	rm -rf *.o
	rm -rf clock
