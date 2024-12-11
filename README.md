# Proyecto: Árbol de Navidad Interactivo

Este proyecto utiliza una placa ESP32 y varios componentes electrónicos para crear un árbol de Navidad interactivo. El sistema incluye LEDs, un buzzer para reproducir villancicos, y un receptor de infrarrojos para recibir comandos desde un mando a distancia.

## Características

- **Control Remoto Infrarrojo:** El sistema permite seleccionar secuencias de luces y activar o desactivar la reproducción de canciones utilizando un mando infrarrojo compatible con la librería `DIYables_IRcontroller`.
- **Reproducción de Villancicos:** Incluye la melodía "We Wish You a Merry Christmas" con notas y duraciones predefinidas.
- **Efectos de Luces LED:** Cuatro LEDs controlados individualmente permiten diferentes patrones de iluminación sincronizados con la música.
- **Diseño Modular:** Fácil de extender y modificar, con funciones separadas para reproducir canciones y gestionar las luces.

## Componentes

- ESP32
- LEDs x4
- Buzzer
- Mando infrarrojo compatible con la librería `DIYables_IRcontroller`
- Receptor de infrarrojos

## Configuración de Pines

| Componente          | Pin ESP32 |
|---------------------|-----------|
| Buzzer             | 18        |
| LED 1              | 23        |
| LED 2              | 22        |
| LED 3              | 21        |
| LED 4              | 19        |
| Receptor Infrarrojo| 13        |

## Funcionalidad del Código

1. **Inicialización:**
   - Configura los pines de salida para el buzzer y los LEDs.
   - Inicializa el receptor infrarrojo.

2. **Gestor de Comandos:**
   - Utiliza el mando a distancia para seleccionar diferentes secuencias de luces y reproducir la música.

3. **Reproducción de Melodía:**
   - La canción "We Wish You a Merry Christmas" está definida en un arreglo de notas y duraciones.
   - Las luces se sincronizan con la música para crear un efecto visual.

4. **Secuencias de Luces:**
   - Cuatro patrones predefinidos de iluminación:
     - Secuencia 1: Encendido y apagado secuencial de LEDs.
     - Secuencia 2: Alternancia entre LEDs pares e impares.
     - Secuencia 3: Ciclo rápido de encendido y apagado.
     - Secuencia 4: Patrón aleatorio.
     - Todas las luces encendidas.

## Uso del Proyecto

1. Conecta los componentes según la configuración de pines.
2. Sube el código a la placa ESP32 utilizando el IDE de Arduino.
3. Alimenta el sistema y utiliza el mando a distancia para interactuar con el árbol de Navidad.

## Requisitos de Software

- IDE de Arduino
- Librería `DIYables_IRcontroller` (instalable desde el gestor de librerías de Arduino)

## Futuras Mejores

- Agregar más patrones de luces.
- Integrar sensores adicionales para detección de movimiento o control por voz.
- Crear una aplicación móvil para controlar las funciones.

## Licencia

Este proyecto se distribuye bajo la licencia MIT. Si deseas utilizarlo o modificarlo, por favor, atribuye el trabajo original.
