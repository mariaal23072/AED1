import re
import patrones
import herramientas


# 1) Teléfono
def procesar_telefono(cadena):
   cadena = cadena.strip()
   match = re.fullmatch(patrones.patron_telefono, cadena)
   if match:
       limpio = re.sub(r"[-\s]", "", cadena)
       if len(limpio) == 9:
           return "+34" + limpio
       return limpio
   return None


# 2) NIF
def procesar_nif(cadena):
   cadena = cadena.strip()
   if re.fullmatch(patrones.patron_nif, cadena):
       if herramientas.es_valido_nif(cadena):
           return cadena
   return None



# 3) Fecha (Diccionarios + Formateo)
def procesar_fecha(cadena):
   cadena = cadena.strip()
   anio, mes, dia, hora, minuto, segundo = 0, 0, 0, 0, 0, 0
   encontrado = False

   # Intento F1
   match = re.fullmatch(patrones.patron_fecha_f1, cadena)
   if match:
       d = match.groupdict()
       anio, mes, dia = int(d['anio']), int(d['mes']), int(d['dia'])
       hora, minuto = int(d['hora']), int(d['minuto'])
       encontrado = True

   # Intento F2
   if not encontrado:
       match = re.fullmatch(patrones.patron_fecha_f2, cadena)
       if match:
           d = match.groupdict()
           mes = herramientas.meses(d['mesStr'])
           dia, anio = int(d['dia']), int(d['anio'])
           h, m = int(d['hora']), int(d['minuto'])
           if d['ampm'].upper() == "PM" and h < 12:
               h += 12
           elif d['ampm'].upper() == "AM" and h == 12:
               h = 0
           hora, minuto = h, m
           encontrado = True

   # Intento F3
   if not encontrado:
       match = re.fullmatch(patrones.patron_fecha_f3, cadena)
       if match:
           d = match.groupdict()
           hora, minuto, segundo = int(d['hora']), int(d['minuto']), int(d['segundo'])
           dia, mes, anio = int(d['dia']), int(d['mes']), int(d['anio'])
           encontrado = True

   if encontrado and herramientas.validar_fecha(anio, mes, dia):
       if 0 <= hora <= 23 and 0 <= minuto <= 59 and 0 <= segundo <= 59:
           # Este es uno de los cambios de la sesión 7 en el que devolvemos diccionario
           return {
               "anio": anio, "mes": mes, "dia": dia,
               "hora": hora, "minuto": minuto, "segundo": segundo
           }
   return None


def mostrar_fecha(fecha_dict, formato):
   #Recibe el diccionario de fecha y un número (1, 2, 3) indicando el formato de salida.

   if not fecha_dict: return ""

   # Extraemos variables para no escribir tanto
   y, m, d = fecha_dict["anio"], fecha_dict["mes"], fecha_dict["dia"]
   h, minu, s = fecha_dict["hora"], fecha_dict["minuto"], fecha_dict["segundo"]

   if formato == 1:  # YYYY-MM-DD HH:MM
       return f"{y:04d}-{m:02d}-{d:02d} {h:02d}:{minu:02d}"

   elif formato == 2:  # Month D, Y HH:MM AM/PM
       nombres_mes = ['', 'January', 'February', 'March', 'April', 'May', 'June',
                      'July', 'August', 'September', 'October', 'November', 'December']
       mes_str = nombres_mes[m]
       ampm = "AM"
       h_12 = h
       if h >= 12:
           ampm = "PM"
           if h > 12: h_12 -= 12
       if h == 0: h_12 = 12

       return f"{mes_str} {d}, {y} {h_12}:{minu:02d} {ampm}"

   elif formato == 3:  # HH:MM:SS DD/MM/YYYY
       return f"{h:02d}:{minu:02d}:{s:02d} {d:02d}/{m:02d}/{y:04d}"

   return "FORMATO_DESCONOCIDO"



# 4) Coordenadas (Diccionarios + Formateo)
def sexagesimal_a_decimal(g, m, s, orient):
   val = float(g) + float(m) / 60 + float(s) / 3600
   if orient in ['S', 'W']: val = -val
   return val


def procesar_coordenadas(cadena):
   cadena = cadena.strip()
   lat, lon = 0.0, 0.0
   encontrado = False

   match = re.fullmatch(patrones.patron_coord_f1, cadena)
   if match:
       d = match.groupdict()
       lat, lon = float(d['lat']), float(d['lon'])
       encontrado = True

   if not encontrado:
       match = re.fullmatch(patrones.patron_coord_f2, cadena) or re.fullmatch(patrones.patron_coord_f3, cadena)
       if match:
           d = match.groupdict()
           lat = sexagesimal_a_decimal(d['lat_deg'], d['lat_min'], d['lat_sec'], d['lat_orient'])
           lon = sexagesimal_a_decimal(d['lon_deg'], d['lon_min'], d['lon_sec'], d['lon_orient'])
           encontrado = True

   if encontrado and -90 <= lat <= 90 and -180 <= lon <= 180:
       return {"lat": lat, "lon": lon}
   return None


def mostrar_coordenada(coord_dict, formato):
   if not coord_dict: return ""
   lat, lon = coord_dict["lat"], coord_dict["lon"]

   if formato == 1:  # Decimal
       return f"{lat},{lon}"  # Simplificado

   # Convertir de decimal a sexagesimal (formatos 2 y 3) es muy dificil.
   # Preguntarle al profe si exige conversión inversa estricta.
   # Aquí devolvemos formato 1 siempre para que no se nos complique.
   return f"{lat},{lon}"



# 5) Validación entera de una linea de compra
def validar_entrada(linea):
   """Recibe una línea cruda del fichero.
   Devuelve un diccionario con TODOS los campos procesados si es válida.
   Devuelve None si algún campo falla."""

   campos = herramientas.quitar_espacios(linea)
   if len(campos) != 6:
       return None

   # Vamos procesando uno a uno
   tlf = procesar_telefono(campos[0])
   nif = procesar_nif(campos[1])
   fecha = procesar_fecha(campos[2])
   coord = procesar_coordenadas(campos[3])
   producto = campos[4]  # Texto libre
   precio = campos[5]  # Validar formato precio

   # Validar precio
   if not re.fullmatch(patrones.patron_precio, precio):
       return None

   if tlf and nif and fecha and coord:
       return {
           "telefono": tlf,
           "nif": nif,
           "fecha": fecha,
           "coordenadas": coord,
           "producto": producto,
           "precio": precio
       }

   return None

