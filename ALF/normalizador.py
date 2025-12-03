import re
import patrones
from herramientas import es_valido_nif, meses, validar_fecha

# TELÉFONO
def normalizar_telefono(telefono_sucio):
    match = re.fullmatch(patrones.patron_telefono, telefono_sucio)
    if match:
        # número sin guiones
        tlf_limpio = match.group("p1") + match.group("p2") + match.group("p3")
        return "+34" + tlf_limpio
    return None


# NIF
def normalizar_nif(nif_sucio):
    match = re.fullmatch(patrones.patron_nif, nif_sucio)
    if match:
        # Comprobar letra
        if es_valido_nif(nif_sucio):
            return nif_sucio
    return None

# FECHA
def normalizar_fecha(fecha_sucia):
    a, m, d, h, minu, s = 0, 0, 0, 0, 0, 0
    encontrado = False

    # FORMATO 1
    match = re.fullmatch(patrones.patron_fecha_f1, fecha_sucia)
    if match:
        a = int(match.group("anio"))
        m = int(match.group("mes"))
        d = int(match.group("dia"))
        h = int(match.group("hora"))
        minu = int(match.group("minuto"))
        s = 0
        encontrado = True

    # FORMATO 2
    if not encontrado:
        match = re.fullmatch(patrones.patron_fecha_f2, fecha_sucia)
        if match:
            nombre_mes = match.group("mesStr")
            m = meses(nombre_mes.capitalize())
            d = int(match.group("dia"))
            a = int(match.group("anio"))
            h = int(match.group("hora"))
            minu = int(match.group("minuto"))
            s = 0
            ampm = match.group("ampm").upper()

            if ampm == "PM" and h < 12:
                h += 12
            elif ampm == "AM" and h == 12:
                h = 0
            encontrado = True

    # FORMATO 3
    if not encontrado:
        match = re.fullmatch(patrones.patron_fecha_f3, fecha_sucia)
        if match:
            h = int(match.group("hora"))
            minu = int(match.group("minuto"))
            s = int(match.group("segundo"))
            d = int(match.group("dia"))
            m = int(match.group("mes"))
            a = int(match.group("anio"))
            encontrado = True

    if encontrado:
        if validar_fecha(a, m, d):
            return [a, m, d, h, minu, s]

    return None

# COORDENADAS
def sexagesimal_a_decimal(grados, minutos, segundos, orientacion):
    decimal = float(grados) + float(minutos) / 60 + float(segundos) / 3600
    if orientacion in ['S', 'W']:
        decimal = -decimal
    return decimal


def normalizar_coordenada(coord_sucia):
    lat = 0.0
    lon = 0.0
    encontrado = False

    # FORMATO 1 (Decimal)
    match = re.fullmatch(patrones.patron_coord_f1, coord_sucia)
    if match:
        lat = float(match.group("lat"))
        lon = float(match.group("lon"))
        encontrado = True

    # FORMATO 2 (Sexagesimal)
    if not encontrado:
        match = re.fullmatch(patrones.patron_coord_f2, coord_sucia)
        if match:
            lat = sexagesimal_a_decimal(match.group("lat_deg"), match.group("lat_min"), match.group("lat_sec"),
                                        match.group("lat_orient"))
            lon = sexagesimal_a_decimal(match.group("lon_deg"), match.group("lon_min"), match.group("lon_sec"),
                                        match.group("lon_orient"))
            encontrado = True

    # FORMATO 3 (GPS)
    if not encontrado:
        match = re.fullmatch(patrones.patron_coord_f3, coord_sucia)
        if match:
            lat = sexagesimal_a_decimal(match.group("lat_deg"), match.group("lat_min"), match.group("lat_sec"),
                                        match.group("lat_orient"))
            lon = sexagesimal_a_decimal(match.group("lon_deg"), match.group("lon_min"), match.group("lon_sec"),
                                        match.group("lon_orient"))
            encontrado = True

    # Validar rangos
    if encontrado:
        if -90 <= lat <= 90 and -180 <= lon <= 180:
            return [lat, lon]

    return None