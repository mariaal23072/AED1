# Sesión 1
def es_bisiesto(anio):
    return (anio % 4 == 0 and anio % 100 != 0) or (anio % 400 == 0)


def obtener_dias_del_mes(mes, anio):
    dias_por_mes = [0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]

    if es_bisiesto(anio) and mes == 2:
        return 29

    if 1 <= mes <= 12:
        return dias_por_mes[mes]
    return 0


def validar_fecha(anio, mes, dia):
    if not (1 <= mes <= 12):
        return False
    if anio < 1 or anio > 9999:
        return False

    max_dias = obtener_dias_del_mes(mes, anio)
    if 1 <= dia <= max_dias:
        return True
    return False


def comparar_fechas(anio1, mes1, dia1, hora1, min1, anio2, mes2, dia2, hora2, min2):
    if anio1 < anio2: return -1
    if anio1 > anio2: return 1

    if mes1 < mes2: return -1
    if mes1 > mes2: return 1

    if dia1 < dia2: return -1
    if dia1 > dia2: return 1

    if hora1 < hora2: return -1
    if hora1 > hora2: return 1

    if min1 < min2: return -1
    if min1 > min2: return 1

    # Si es igual:
    return 0

# Sesión 2

def normaliza(fichero):
    print(fichero)

# 1)
def letra_dni(dni):
    resto = dni%23
    letras = ['T','R','W','A','G','M','Y','F','P','D','X','B','N','J','Z','S','Q','V','H','L','C','K','E']
    return letras[resto]

# 2)
def es_valido_nif(nif):
    # Quitamos el guion para anailzarlos
    nif_limpio = nif.replace("-", "")

    if len(nif_limpio) != 9:
        return False

    parte_numerica = nif_limpio[:8].upper()
    letra_usuario = nif_limpio[8].upper()

    # NIE
    if parte_numerica.startswith('X'):
        numero_calculo = parte_numerica.replace('X', '0')
    elif parte_numerica.startswith('Y'):
        numero_calculo = parte_numerica.replace('Y', '1')
    elif parte_numerica.startswith('Z'):
        numero_calculo = parte_numerica.replace('Z', '2')
    else:
        numero_calculo = parte_numerica

    # Lo que queda son dígitos
    try:
        num = int(numero_calculo)
    except ValueError:
        return False

    # Comprobar la letra
    return letra_usuario == letra_dni(num)

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


