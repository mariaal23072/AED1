import re

# TELEFONO
# Formato: 999-999-999
patron_telefono = r"(?P<p1>\d{3})-(?P<p2>\d{3})-(?P<p3>\d{3})"

# NIF
# Formato: 12345678-Z o X1234567-Z
patron_nif = r"(?P<numero>([XYZ]|\d)\d{7})-(?P<letra>[A-Z])"

# FECHAS

# FORMATO 1: YYYY-MM-DD HH:MM
patron_fecha_f1 = (
   r"(?P<anio>\d{4})-"
   r"(?P<mes>0[1-9]|1[0-2])-"
   r"(?P<dia>0[1-9]|[12]\d|3[01])\s+"
   r"(?P<hora>[01]\d|2[0-3]):"
   r"(?P<minuto>[0-5]\d)"
)

# FORMATO 2: Month D, Y HH:MM AM/PM
meses_ingles = r"January|February|March|April|May|June|July|August|September|October|November|December"
patron_fecha_f2 = (
   r"(?i)(?P<mesStr>" + meses_ingles + r")\s+"
   r"(?P<dia>\d{1,2}),\s+"
   r"(?P<anio>\d{1,4})\s+"
   r"(?P<hora>\d{1,2}):"
   r"(?P<minuto>\d{2})\s+"
   r"(?P<ampm>AM|PM)"
)

# FORMATO 3: HH:MM:SS DD/MM/YYYY
patron_fecha_f3 = (
   r"(?P<hora>[01]\d|2[0-3]):"
   r"(?P<minuto>[0-5]\d):"
   r"(?P<segundo>[0-5]\d)\s+"
   r"(?P<dia>0[1-9]|[12]\d|3[01])/"
   r"(?P<mes>0[1-9]|1[0-2])/"
   r"(?P<anio>\d{4})"
)

# COORDENADAS

# FORMATO 1 (DECIMAL): 30.0, -40.5
patron_coord_f1 = r"(?P<lat>[+-]?\d+\.\d+)\s*,\s*(?P<lon>[+-]?\d+\.\d+)"

# FORMATO 2 (Sexagesimal): 30° 0' 0.0000" N, 40° 30' 0.0000" W
patron_coord_f2 = (
   r"(?P<lat_deg>\d+)°\s*(?P<lat_min>\d+)'\s*(?P<lat_sec>\d+\.\d{4})\"\s*(?P<lat_orient>[NS])\s*,\s*"
   r"(?P<lon_deg>\d+)°\s*(?P<lon_min>\d+)'\s*(?P<lon_sec>\d+\.\d{4})\"\s*(?P<lon_orient>[EW])"
)

# FORMATO 3 (GPS): 0300000.0000N0403000.0000W
patron_coord_f3 = (
   r"(?P<lat_deg>\d{3})(?P<lat_min>\d{2})(?P<lat_sec>\d{2}\.\d{4})(?P<lat_orient>[NS])"
   r"(?P<lon_deg>\d{3})(?P<lon_min>\d{2})(?P<lon_sec>\d{2}\.\d{4})(?P<lon_orient>[EW])"
)

# PRECIO
patron_precio = r"(?P<entero>0|[1-9]\d*)(?P<decimal>\.\d+)?(?P<moneda>[€$])"