# Makefile del ejercicio 006

a.out: main.o Diccionario.o Cuac.o Fecha.o
	g++ main.o Diccionario.o Cuac.o Fecha.o -o a.out

main.o: main.cpp Diccionario.h
	g++ -c main.cpp

Diccionario.o: Diccionario.cpp Diccionario.h Cuac.h
	g++ -c Diccionario.cpp

Cuac.o: Cuac.cpp Cuac.h Fecha.h
	g++ -c Cuac.cpp

Fecha.o: Fecha.cpp Fecha.h
	g++ -c Fecha.cpp

# Limpieza
clean:
	rm -f *.o a.out