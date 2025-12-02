# Makefile del ejercicio 300

a.out: main.o Diccionario.o Cuac.o Fecha.o TablaHash.o Arbol.o
	g++ main.o Diccionario.o Cuac.o Fecha.o TablaHash.o Arbol.o -o a.out

main.o: main.cpp Diccionario.h TablaHash.h Arbol.h Fecha.h
	g++ -c main.cpp

Diccionario.o: Diccionario.cpp Diccionario.h Cuac.h TablaHash.h Arbol.h Fecha.h
	g++ -c Diccionario.cpp

Cuac.o: Cuac.cpp Cuac.h Fecha.h
	g++ -c Cuac.cpp

Fecha.o: Fecha.cpp Fecha.h
	g++ -c Fecha.cpp

TablaHash.o: TablaHash.cpp TablaHash.h Cuac.h Fecha.h
	g++ -c TablaHash.cpp

Arbol.o: Arbol.cpp Arbol.h Nodo.h Cuac.h Fecha.h
	g++ -c Arbol.cpp

# Limpieza
clean:
	rm -f *.o a.out