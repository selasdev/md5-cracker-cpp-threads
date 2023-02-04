## Crackeador de MD5

Este ejemplo reutiliza la siguiente función para usar la funcionalidad de MD5: http://www.zedwood.com/article/cpp-md5-function

Este proyecto está creado con la finalidad de demostrar el aprendizaje
de aplicaciones multi-plataforma (específicamente múltiples sistemas operativos), utilizando hilos del sistema
a través de la API del S.O. Para acceder a variables globales y modificar su valor
de manera segura usando semáforos.

### Enunciado

Una compañía de seguridad informática está buscando futuros hackers para desarrollar un conjunto de herramientas de auditoría de seguridad.

Para ser parte del equipo, solicitan el desarrollo de una herramienta para crackear contraseñas
cifradas bajo el algoritmo MD5. Esta herramienta recibe un archivo de entrada llamado users.txt,
donde cada línea representa una cuenta de usuario y la información esta almacenada bajo el
siguiente formato:

```
usuario::contraseña_cifrada
```

Su programa debe leer cada línea del archivo de entrada, crackear la contraseña y
mostrar por pantalla el nombre del usuario junto a la contraseña, separados por una tabulación.
Debido a la gran cantidad de cálculos matemático que requiere para crackear las contraseñas, debe resolver el problema utilizando hilos
para aprovechar al máximo el hardware.

### Limitaciones

Para facilitar el desarrollo, se han agregado las siguientes restricciones:

- Las contraseñas poseen un tamaño máximo de 4 caracteres, compuesto de letras minúsculas o mayúsculas (a-zA-z).
- La cantidad máxima de usuarios a procesar es 50 y la cantidad máxima de hilos a ejecutar simultáneamente son 6.
- El programa permite seleccionar la ubicación del archivo y la cantidad de hilos a usar, se usarán parámetros de entrada para esto.
- Los formatos de salida han sido respetados pues se supone serán utilizados como datos de entrada para otro programa.
- El programa imprimirá en consola una salida del archivo, sin embargo, estos cambios pueden ser encontrados en un archivo de salida users_out.txt

### Uso

## 1

Para comenzar, se debe compilar el programa corriendo el siguiente comando en la raíz de la carpeta contenedora:

```
g++ -lpthread main.cpp -o <nombre del programa de salida>.out

```

Por ejemplo

```
g++ -lpthread main.cpp -o programa.out
```

## 2

Ejecute el programa de salida anterior con los parámetros de entrada como argumentos:

```
./<nombre del programa de salida>.out <ruta_del_archivo> <cantidad_de_hilos a utilizar>
./practica3.out users.txt 4
```

Por ejemplo

```
./practica3.out users.txt 4
```
