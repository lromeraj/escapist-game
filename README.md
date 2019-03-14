# Goose Game

El juego ha sido diseñado para ser compilado en un entorno de Linux. Para facilitar el proceso de compilación/enlazado/ejecución del juego se ha desarrollado un script, más abajo está la guía de su uso. En caso de tener cualquier problema a la hora de compilar o cualquier otro fallo puede enviar un correo a javier.romeral@estudiante.uam.es"  o "lromerajdev@gmail.com".

## Notas:

* El archivo "target.conf" es un archivo de configuración utilizado por el script "target", es recomendable no editarlo. En caso de ser eliminado el script dará un error indicando que no se ha encontrado un archivo de configuración.

* El archivo `CHANGELOG`, contiene un historial de cambios.
* El archivo `target` contine el script encargado de simplificar el proceso de compilación/enlazado.

* El archivo `data.dat` contiene la información necesaria para inicializar/cargar el juego.
* El archivo oculto `.clang_complete` puede ser ignorado, no ofrece ningún tipo de información relevante. En general todos los archivos ocultos deberían ser ignorados.

 ## Makefile

 Hacer una limpieza completa y después genera todos los ejecutables:

`$ make`

dGenerar el ejecutable del juego:

`$ make goose`

 Generar el ejecutable que testea el módulo `set`:

`$ make set_tb`

Hacer una limpieza completa:

`$ make clean`

Para generar el paquete de distribución:

`$ make dist`

## Target script

`$ ./target [-e <env>] [options] ...`


`-e, --env` - establece el entorno con el que se va a trabajar, en este caso un entorno sería    por ejemplo [goose], si no se especifica ningún entorno, el script 		usará el primero que esté definido en el archivo de configuración. 		Si el entorno especificado no se encuentra en el archivo de configuración 		se saltarán todos las acciones solicitadas para dicho entorno y se pasará 		al siguiente (en el caso de que se hayan solicitado acciones para varios 		entornos)

 `-c, --comp` compila un entorno.

`-r, --run` - ejecuta el archivo ejecutable generado para dicho entorno. También acepta argumentos adicionales que serán pasados al ejecutable.

`--clean` - limpia los archivos objeto y ejecutables generados en un entorno.

 `-m, --cmem` - hacer chequeo de memoria con valgrind.

`-d, --dist` - genera un archivo comprimido para ser distribuido.
		Cuando se ejecuta la instrucción `-d, --dist` el script buscará un archivo llamado `CHANGELOG`, si encuentra una definición de versión dentro de éste (por ejemplo `v1.0.0`), actualizará el archivo `ASCII_VERSION` y generará un nombre con la fecha y la versión en caso de encontrarla.

### Ejemplos de uso:

Para compilar, por ejemplo, el entorno `[goose]`:

  `$ ./target -e goose -c`

 Para ejecutarlo:

`$ ./target -e goose -r`

 Para limpiarlo:

`$ ./target -e goose --clean`

 Si se desea hacer todo de una vez, (limpiar -> compilar -> ejecutar):

`$ ./target -e goose --clean -c -r`

 Si se desea chequear el uso de la memoria:

`$ ./target -e goose -m`

 Si se desea pasar argumentos adicionales al ejecutar el ejecutable:

`$ ./target -e goose -r arg1 arg2 arg3 ...`

 Si se desea compilar varios entornos de una vez:

`$ ./target -e goose -c -e set_tb -c ...`

 ## `target.conf`

Para definnir un entorno en el archivo de configuración, debe usar la siguiente nomenclatura `[<env_name>]` donde **<env_name>** es el nombre del entorno.

| PARÁMETRO | DESCRIPCIÓN |
|--|--|
| TARGET | nombre del ejecutable |
| TARGET_ARGS | argumentos por defecto que se pasarán al ejecutable |
| DISTDIR | directorio de distribución, en el cual se guardarán los archivos de distribución. |
| OBJDIR | directorio donde se guardarán los archivos objeto |
| SRCDIR | el directorio donde se encuentran los recursos del ejecutable |
| SRCS | el nombre de los múdulos que se necesitan para generar el ejecutable |
| LDFLAGS | parámetros que se deben de tener en cuenta a la hora de enlazar |
| CFLAGS | parámetros que se deben de tener en cuenta a la hora de compilar |
| ASCII_TITLE | archivo que contiene un título con decoración ASCII |
| ASCII_VERSION | archivo que contiene una versión con decoración ASCII |
