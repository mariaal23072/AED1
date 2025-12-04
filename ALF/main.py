import sys
import procesamiento


def normalizar_fichero(fichero, formato_fecha=2, formato_coord=1):
   #Opción -n: Lee, valida y muestra normalizado
   try:
       f = open(fichero, "r", encoding="utf-8")
       for linea in f:
           if not linea.strip(): continue

           # Vamos a usar usamos la validación completa de la Sesión 7
           datos = procesamiento.validar_entrada(linea)

           if datos:
               # Si es válido, formateamos la salida
               f_str = procesamiento.mostrar_fecha(datos['fecha'], formato_fecha)
               c_str = procesamiento.mostrar_coordenada(datos['coordenadas'], formato_coord)

               # Formato de salida: campos separados por "; "
               # El enunciado dice: tlf normalizado, NIF igual, fecha fmt, coord fmt, prod igual, precio igual
               print(f"{datos['telefono']}; {datos['nif']}; {f_str}; {c_str}; {datos['producto']}; {datos['precio']}")

           # Si no es válido, el enunciado dice que se ignora silenciosamente
       f.close()
   except FileNotFoundError:
       print("Error: Fichero no encontrado")


def filtrar_telefono(telefono_buscado, fichero):
   """Opción -sphone: Muestra líneas originales que coincidan en teléfono"""
   try:
       f = open(fichero, "r", encoding="utf-8")
       for linea in f:
           if not linea.strip(): continue

           # Validamos para extraer el teléfono normalizado y comparar
           datos = procesamiento.validar_entrada(linea)

           if datos:
               # Comparamos el teléfono normalizado
               if telefono_buscado in datos['telefono']:
                   print(linea.strip())  # Se muestra la línea original
       f.close()
   except FileNotFoundError:
       print("Error: Fichero no encontrado")


def main():
   args = sys.argv
   if len(args) < 3:
       print("Uso incorrecto. Ejemplos:")
       print("  python main.py -n log.txt 2 1")
       print("  python main.py -sphone +34666777888 log.txt")
       # Modo prueba si no hay argumentos
       print("\n--- EJECUTANDO PRUEBA POR DEFECTO (Normalizar log.txt) ---")
       normalizar_fichero("log.txt", 2, 1)
       return

   opcion = args[1]

   if opcion == "-n":
       # Sintaxis: -n fichero [f1 f2]
       fichero = args[2]
       fmt_fecha = 2  # Por defecto Anexo
       fmt_coord = 1  # Por defecto Anexo

       if len(args) == 5:
           fmt_fecha = int(args[3])
           fmt_coord = int(args[4])

       normalizar_fichero(fichero, fmt_fecha, fmt_coord)

   elif opcion == "-sphone":
       # Sintaxis: -sphone telefono fichero
       if len(args) == 4:
           telefono = args[2]
           fichero = args[3]
           filtrar_telefono(telefono, fichero)
       else:
           print("Faltan argumentos para -sphone")

   # Añadir -snif, -stime, etc. siguiendo el mismo patrón


main()
