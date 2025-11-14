# Alquerque GTK

Este proyecto es una implementación del juego Alquerque usando C y la biblioteca GTK para la interfaz gráfica. Permite a dos jugadores competir en un tablero virtual, gestionando turnos, capturas y mostrando el estado del juego.

## Características
- Juego clásico de Alquerque para dos jugadores.
- Interfaz gráfica con GTK y Glade.
- Ventanas para reglas, créditos, ingreso de nombres y ganador.
- Contador de fichas capturadas y gestión de turnos.
- Imágenes personalizadas para fichas y estados del juego.

## Estructura del proyecto
- `Alquerque.c`: Código fuente principal.
- `Alquerque_Glade.glade`: Archivo de interfaz gráfica.
- Carpeta `IMG/`: Imágenes usadas en el tablero y ventanas.
- Binarios y objetos en `bin/` y `obj/`.

## Requisitos
- Windows con GTK instalado.
- Compilador de C compatible (por ejemplo, MinGW).
- Archivos Glade y recursos gráficos en las rutas indicadas.

## Ejecución
1. Compila el proyecto asegurándote de tener GTK configurado.
2. Ejecuta el binario generado (`Alquerque.exe`).
3. Sigue las instrucciones en pantalla para jugar.

## Créditos
Desarrollado como trabajo práctico para la materia de Lenguaje de Programación 1.
