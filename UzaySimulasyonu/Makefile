hepsi: derle calistir

derle: Time.o Person.o Spacecraft.o Planet.o Simulation.o FileReader.o main.o
	gcc -o ./bin/simulator ./lib/Time.o ./lib/Person.o ./lib/Spacecraft.o ./lib/Planet.o ./lib/Simulation.o ./lib/FileReader.o ./lib/main.o

Time.o: ./src/Time.c ./include/Time.h
	gcc -I ./include -o ./lib/Time.o -c ./src/Time.c

Person.o: ./src/Person.c ./include/Person.h
	gcc -I ./include -o ./lib/Person.o -c ./src/Person.c

Spacecraft.o: ./src/Spacecraft.c ./include/Spacecraft.h
	gcc -I ./include -o ./lib/Spacecraft.o -c ./src/Spacecraft.c

Planet.o: ./src/Planet.c ./include/Planet.h
	gcc -I ./include -o ./lib/Planet.o -c ./src/Planet.c

Simulation.o: ./src/Simulation.c ./include/Simulation.h
	gcc -I ./include -o ./lib/Simulation.o -c ./src/Simulation.c

FileReader.o: ./src/FileReader.c ./include/FileReader.h
	gcc -I ./include -o ./lib/FileReader.o -c ./src/FileReader.c

main.o: main.c ./include/FileReader.h ./include/Simulation.h
	gcc -I ./include -o ./lib/main.o -c main.c

calistir:
	./bin/simulator

temizle:
	del /Q lib\*.o bin\simulator.exe 2>nul || true