# Trabajo_Final_PCSE_PdM
Trabajo Final para la materia PCSE y PdM
Autor: Leandro Díaz diazleandro1012@gmail.com

El proyecto implementa dos drivers portables para sensores que permiten medir variables del aire. Estos son el sensor sunrise (https://senseair.com/products/power-counts/sunrise-hvac/) y el sensor sht4x(https://sensirion.com/media/documents/33FD6951/63E1087C/Datasheet_SHT4x_1.pdf).  
El sensor sunrise permite medir el Co2 del ambiente y el sensor sht4x podemos medir temperatura y humedad. La realización de este driver. La aplicación, no portable desarrollada en la placa NUCLEO-F429ZI, envía los datos de los sensores (Co2, temperatura y humedad) a la PC de forma serial cada X segundos. Se puede pausar o reanudar la adquisición de datos mediante el botón de la placa NUCELO, así como también, entrar a un modo configuración presionando dos veces el botón. En este modo se puede cambiar la frecuencia con la que se adquieren los datos.

Detalle de los módulos:

sht4x.c sht4x.h -> Driver portables del sensor de humedad y temperatura  
sht4x_port.c sht4x_port.h -> Capa de abstracción del driver sht4x  
sunrise.c sunrise.h -> Driver portable del sensor de Co2  
sunrise_port.c sunrise_port.h -> Capa de abstracción del driver sunrise  
API_delay.c API_delay.h  -> Implementa delay no bloqueante  
API_doubonce.c API_doubonce.h  -> Implementa una FSM para el antirebote del botón  
API_doubleclick.c API_doubleclick.h -> Implementa una FSM para agregar la posibilidad de diferenciar 1 click o 2 click mediante el mismo botón  
API_uart.c API_uart.h -> Implementa funciones de UART  
API_measurement.c API_measurement.h -> Implementa una FSM para realizar la lógica de la aplicación  
API_sensors.c API_sensors.h -> Agrupa todos los sensores  


