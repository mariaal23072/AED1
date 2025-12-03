from herramientas import quitar_espacios, es_valido_nif
import sys
import re
import patrones

# Función para probar patrones
def comprobar(dato, lista_patrones):
   for patron in lista_patrones:
       if re.fullmatch(patron, dato):
           return True
   return False

def procesar_fichero(nombre_fichero):
   try:
       f = open(nombre_fichero, "r", encoding="utf-8")

       for linea in f:
           linea = linea.strip()

           # Si la línea está vacía, saltar a la siguiente
           if not linea:
               continue

           lista_campos = quitar_espacios(linea)

           # Solo seguir si tiene los 6 campos
           if len(lista_campos) == 6:
               telefono = lista_campos[0]
               nif = lista_campos[1]
               fecha = lista_campos[2]
               coords = lista_campos[3]
               precio = lista_campos[5]

               # Comprobar TELÉFONO
               if re.fullmatch(patrones.patron_telefono, telefono):
                   res_tlf = "BIEN"
               else:
                   res_tlf = "MAL"

               # Comprobar NIF
               if re.fullmatch(patrones.patron_nif, nif) and es_valido_nif(nif):
                   res_nif = "BIEN"
               else:
                   res_nif = "MAL"

               # Comprobar FECHA
               lista_fechas = [patrones.patron_fecha_f1, patrones.patron_fecha_f2, patrones.patron_fecha_f3]
               if comprobar(fecha, lista_fechas):
                   res_fecha = "BIEN"
               else:
                   res_fecha = "MAL"

               # Comprobar COORDENADAS
               lista_coords = [patrones.patron_coord_f1, patrones.patron_coord_f2, patrones.patron_coord_f3]
               if comprobar(coords, lista_coords):
                   res_coord = "BIEN"
               else:
                   res_coord = "MAL"

               # Comprobar PRECIO
               if re.fullmatch(patrones.patron_precio, precio):
                   res_precio = "BIEN"
               else:
                   res_precio = "MAL"

               print(f"Tlf:{res_tlf} | NIF:{res_nif} | Fecha:{res_fecha} | Coord:{res_coord} | Precio:{res_precio}")
       f.close()


   except FileNotFoundError:
       print("Ha ocurrido un error al leer el fichero")

def main():
   if len(sys.argv) > 1:
       procesar_fichero(sys.argv[1])
   else:
       procesar_fichero("log.txt")

main()
