# Módulo: herramientas_fecha.py (sesión 1)

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