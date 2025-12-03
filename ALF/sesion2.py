
import sys


def normaliza(fichero):
    print(fichero)

# 1)
def letra_dni(dni):
    resto = dni%23
    letras = ['T','R','W','A','G','M','Y','F','P','D','X','B','N','J','Z','S','Q','V','H','L','C','K','E']
    return letras[resto]

# 2)
def es_valido_nif(nif):
    if len(nif) != 9:
        return False

    parte_numerica = nif[:8].upper()
    letra = nif[8].upper()

    # NIE:
    if parte_numerica.startswith('X'):
        numero_calculo = parte_numerica.replace('X', '0')
    elif parte_numerica.startswith('Y'):
        numero_calculo = parte_numerica.replace('Y', '1')
    elif parte_numerica.startswith('Z'):
        numero_calculo = parte_numerica.replace('Z', '2')
    else:
        # Es un DNI normal
        numero_calculo = parte_numerica
    # verificar que lo que queda son números
    try:
        num = int(numero_calculo)
    except ValueError:
        return False  # No eran números
    # Comparamos la letra que nos dio el usuario con la que debería tener ese número
    return letra == letra_dni(num)

# 3)
def meses(mes):
    month = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August', 'September', 'October', 'November', 'December']
    if mes in month:
        return month.index(mes) + 1
    else:
        return 0

# 4)
def quitar_espacios(lista):
    # si lista vacía
    if not lista:
        return []

    productos = lista.split(";")  # lista separada
    lista2 = []
    for p in productos:
        p_limpio = p.strip()
        if p_limpio: # añadir solo si se ha quedado vacío
            lista2.append(p_limpio)  # quita espacios y lo mete
    return lista2


def main():
    print(sys.argv)  # muestra una lista con los argumentos del progarma

    if len(sys.argv) < 2:
        print("Uso: python script.py <opcion> [argumentos]")
        return

    opcion = sys.argv[1]  # Obtenemos la opción desde los argumentos

    if opcion == "letra_dni":
        if len(sys.argv) != 3:
            print("Uso: python script.py letraDNI <dni>")
            return
        dni = int(sys.argv[2])
        print(f"La letra del DNI {dni} es: {letra_dni(dni)}")

    elif opcion == "es_valido_nif":
        if len(sys.argv) != 3:
            print("Uso: python script.py esValidoNIF <nif>")
            return
        nif = sys.argv[2]
        if es_valido_nif(nif):
            print(f"El NIF {nif} es válido.")
        else:
            print(f"El NIF {nif} no es válido.")

    elif opcion == "meses":
        if len(sys.argv) != 3:
            print("Uso: python script.py meses <nombre_mes>")
            return
        mes = sys.argv[2]
        print(f"El mes {mes} corresponde al número {meses(mes)}")

    elif opcion == "quitar_espacios":
        if len(sys.argv) != 3:
            print("Uso: python script.py quitar_espacios <cadena>")
            return
        lista = sys.argv[2]
        print(quitar_espacios(lista))

    else:
        print("Opción no válida. Usa: letra_dni, es_valido_nif, meses o quitar_espacios.")

main()

