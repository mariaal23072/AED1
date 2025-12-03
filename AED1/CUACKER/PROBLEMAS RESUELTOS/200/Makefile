# Makefile del ejercicio 006

a.out: main.o Diccionario.o Cuac.o Fecha.o TablaHash.o
	g++ main.o Diccionario.o Cuac.o Fecha.o TablaHash.o -o a.out

main.o: main.cpp Diccionario.h TablaHash.h
	g++ -c main.cpp

Diccionario.o: Diccionario.cpp Diccionario.h Cuac.h TablaHash.h
	g++ -c Diccionario.cpp

Cuac.o: Cuac.cpp Cuac.h Fecha.h
	g++ -c Cuac.cpp

Fecha.o: Fecha.cpp Fecha.h
	g++ -c Fecha.cpp

TablaHash.o: TablaHash.cpp TablaHash.h Cuac.h
	g++ -c TablaHash.cpp

# Limpieza
clean:
	rm -f *.o a.out