# Escapist Game :game_die:

El juego ha sido diseñado para ser compilado en un entorno de Linux. Para facilitar el proceso de compilación/enlazado/ejecución del juego se ha desarrollado un script, más abajo está la guía de su uso. En caso de tener cualquier problema a la hora de compilar o cualquier otro tipo de fallo, ir a la sección de `Issues` y pinchar en `New issue`, rellenar el diálogo con la información necesaria y finalmente publicar el fallo.

## Notas

* El archivo `solution.goo` contiene la solucón del juego.
Para usarlo ejecutar: `$ ./ctarget -e escapist -c -r < solution.goo`.

* El archivo `target.conf` es un archivo de configuración utilizado por el script `target`, es recomendable no editarlo. En caso de ser eliminado el script dará un error indicando que no se ha encontrado un archivo de configuración.

* El directorio `meetings/` contiene las actas de reunión y el reparto de trabajo.

* El archivo `CHANGELOG.md`, contiene un historial de cambios.
* El archivo `target` contine el script encargado de simplificar el proceso de compilación/enlazado.

* El archivo `data.dat` contiene la información necesaria para inicializar/cargar el juego.
* El archivo oculto `.clang_complete` puede ser ignorado, no ofrece ningún tipo de información relevante. En general todos los archivos ocultos deberían ser ignorados.

* Los archivos con extensión `.goo`, son archivos que contienen grabaciones de partidas.
  Para reproducir estas partidas usar `./target -e goose -c -r data.dat < rec1.goo`.


## Archivo de configuración
El archivo de configuración usa un formato muy simililar al format `JSON`, lo cual hace que sea mucho más sencillo de configurar.
Para definir elementos en el archivo de configuración se deben usar ciertas nomenclaturas reservadas para cada tipo de definición ...

| Tipo | Valores |
| -----  | ---------- |
| String | " " |
| Number | [ **-x.** , **+x.** ]
| Array | Set of any other type |
| Boolean | **1**, **true** / **0**, **false** |

### Espacios

|  Atributo  | Tipo  | Description | Ejemplo
| ------------ |---------------| -----|------- |
| **id**      | Number     |   Identificación del espacio | 1 |
| **name** | String       | Nombre del espacio  |  "East jungle" |
| **links** | Array        |  [ N, E, S, W, U, D ] |  [ 3, 2, 5, 1, 3, 5 ]  |
| **light** |  Boolean        |  Establece si el espacio está iluminado por defecto |  on  |
| **descrp** | String | Una breve descripción del espacio | "Description ..." |
| **ldescrp** | String | Una descripción más detallada del espacio | "Detailed description ..." |
| **picture** | String | Dibujo de decoración del espacio. Usar `\n` literal  para saltos de línea | " /\_/\ \n( o.o )\n > ^ < "

```
@s { # space example
	id: 2,
	name: "Jungle 1",
	descrp: "look around, something useful might be here",
	inks: [ 2, -1, 3, -1, -1, -1 ],
	picture: " (  )\n(    )\n  ||"
}

```

### Objetos

|  Atributo  | Tipo  | Description | Ejemplo
| :------------ |:---------------| :-----| ------- |
| **id**      | Number     |   Identificación del objeto | 1 |
| **name** | String       | Nombre del objeto  |  "torch" |
| **opens** | Array        |  Esta tabla debe contener las identificaciones de los enlaces que puede abrir el objeto en cuestión |  [ 1, 2, 3 ]  |
| **location** |  Number       |  Identificación del espacio en el cual se deberá encontrar el objeto inicialmente | 2  |
| **descrp** | String | Una breve descripción del espacio | "Description ..." |
| **ldescrp** | String | Una descripción más detallada del espacio | "Detailed description ..." |
| **movable** | Boolean | Establece si el objeto de puede mover o no | true |
| **moved** | Boolean | Establece si el objeto se ha movido inicialmente o no | false |
| **hidden** | Boolean | Establece si el objeto está oculto | true |
| **illuminate** | Boolean | Establece si el objeto es capaz de iluminar o no | yes |
| **on** | Boolean | Establece si el objeto está activado o desactivado | false |
| **max_uses** | Number | Establece el máximo número de usos de dicho objeto | 5 |
| **used** | Number | Establece el número de usos inicial | 0 |

```
@o { # object example
	id: 2,
	descrp: "this object can destroy walls",
	location: 2,
	name: "tnt",
	opens: [ 5, 6, 7, 8 ],
	hidden: true
}
```

### Enlaces
|  Atributo  | Tipo  | Description | Ejemplo
| :------------ |:---------------| :-----| ------- |
| **id**      | Number     |   Identificación del enlace | 1 |
| **name** | String       | Nombre del enlace |  "door" |
| **from** | Number | Establece el espacio de partida | 3 |
| **to** | Number | Establece el espacio de destino | 4 |
| **state** | Boolean | Establece si el enlace está abierto o cerrado | opened |
```
@l { # link example
	id: 2,
	name: "Spawn point",
	from: 2,
	to: 1,
	state: 1
}
```

### Jugador
|  Atributo  | Tipo  | Description | Ejemplo
| :------------ |:---------------| :-----| --------- |
| **id**      | Number     |   Identificación del jugador | 1 |
| **name** | String       | Nombre del jugador |  "Pepito" |
| **location** | Number | Establece el espacio en el que se encontrará inicialmente el jugador | 3 |
| **bag** | Array | Establece el inventario inicial del jugador| [ "torch", "tnt" ] |

```
@p { # player example
	id: 1,
	name: "Minguito",
	location: 1,
	bag: [ "torch" ]
}
```


## Doxygen
Para que **Doxygen** funcione correctamente se deben seguir ciertas instrucciones
a la hora de comentar.
Procurar hacer **toda la documentación en inglés**.

### Módulos
- Todos los módulos deben de comenzar con un comentario de encabezado básico.
- Incluir este encabezado en todos los archivos tanto en los archivos `.c` y `.h`.
- En vez de poner todos los participantes en el encabezado del módulo, la etiqueta `@author` puede
ser omitida, y añadir mejor un autor por función.

``` c
/**
* @brief Short module description
*
* Detailed information about the module ...
*
* @file File name
* @author Authors
* @version Last version
* @date Last modification date
*/
```

### Macros
- Para comentar una macro usar `/*!< @brief Macro description */`.
``` c
#define MAX_BOXES 100 /*!< @brief Maximum number of boxes */
```

### Funciones

- Por cada parámetro que reciba la función se debe añadir la etiqueta `@param`, **no se deben hacer
ningún tipo de abreviaciones**, de ser así `Doxygen` no será capaz de parsear correctamente los comentarios.
- Si por un casual un parámetro tuviese más de un tipo de definición, por ejemplo `{const char*}`, **la palabra `const`
deberá ser omitida en el comentario**.
- Si una función no devuelve nada no es necesario añadir la etiqueta `@retval`.

``` c
/**
* @brief Sets up a new command and stores it inside a private array
* @author Javier Romera
* @param {Cid} id - Command identification
* @param {char*} b_name - The base name of the command
* @param {char*} s_name - The short name of the command
* @param {cmd_fn} fn - Command callback function
*/
void cmd_set( Cid id, const char* b_name, const char *s_name, cmd_fn fn );
```

``` c
/**
* @brief Reserves memory to alloc a certain quantity of pixels
* @param {int} __len - The quantity of pixels to be allocted
* @retval {Ui_pix**} - Returns a pointer which points to other pixels pointers
*/
Ui_pix **alloc_pixs( int __len );

```

### Estructuras
- En las estructuras se debe comentar cada campo e incluir además una breve descripción.

``` c
/*!
* @brief Main UI structure
*/
struct _Ui {
  Ui_screen scr; /*!< @brief Screen */
  Ui_box *boxes[ MAX_BOXES ]; /*!< @brief Boxes */
  Ui_pix **__pixs; /*!< @brief Pixels buffer */
  int __len; /*!< @brief Number of pixels */
  char __frm[ FRM_LEN ]; /*!< @brief Temporary format */
};
```
- Es importante dejar un salto de línea extra entre la descripción abreviada
y la detallada.

``` c
/*!
* @brief Main UI screen structure
*
* This is a long description of the screen structure,
* which stores data related with a screen, like the screen width,
* screen height, etc ...
*/
struct _Ui_screen {
  int w; /*!< @brief Width */
  int h; /*!< @brief Height */
};

```

### Enumeraciones
- Las enumeraciones se comentan de forma similar a las estrucutas.
- Para comentar un dato usar `/*!< Value description */`.

``` c
/*!
* @brief Text formats
*/
typedef enum {
  S_DEFAULT=0, /*!< Resets text format */
  S_BOLD=1,  /*!< Bold text */
  S_DIM=2,  /*!< Small text */
  S_UNDERLINED=4,  /*!< Underlined text */
  S_BLINK=5,  /*!< Blink text */
  S_REVERSE=7,  /*!< Reversed text format */
  S_HIDDEN=9  /*!< Hidden text */
} Format;
```

## Makefile

Hacer una limpieza completa y después generar todos los ejecutables:

`$ make`

Generar el ejecutable del juego:

`$ make goose`

Generar el ejecutable que testea el módulo `set`:

`$ make set_tb`

Hacer una limpieza completa:

`$ make clean`

Para generar el paquete de distribución:

`$ make dist`

## Target script

`$ ./target [-e <env>] [options] ...`


`-e, --env` - establece el entorno con el que se va a trabajar, en este caso un entorno sería    por ejemplo `[goose]`, si no se especifica ningún entorno, el script 		usará el primero que esté definido en el archivo de configuración. 		Si el entorno especificado no se encuentra en el archivo de configuración 		se saltarán todos las acciones solicitadas para dicho entorno y se pasará 		al siguiente (en el caso de que se hayan solicitado acciones para varios 		entornos)

`-c, --comp` - compila un entorno.

`-r, --run` - ejecuta el archivo ejecutable generado para dicho entorno. También acepta argumentos adicionales que serán pasados al ejecutable.

`--clean` - limpia los archivos objeto y ejecutables generados en un entorno.

`-m, --cmem` - hacer chequeo de memoria con valgrind.

`-d, --dist` - genera un archivo comprimido para ser distribuido.
		Cuando se ejecuta la instrucción `-d, --dist` el script buscará un archivo llamado `CHANGELOG`, si encuentra una definición de versión dentro de éste (por ejemplo `v1.0.0`), actualizará el archivo `ASCII_VERSION` y generará un nombre con la fecha y la versión en caso de encontrarla.

### Ejemplos de uso

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

Si se desea distrubuir el entorno goose:

`$ ./target -e goose -d`

 ## `target.conf`

NOTA: se puden establecer configuraciones comunes a los entornos, es decir,
si se desea utilizar una configuración básica a todos los entornos utilizar
el entorno [GLOBAL], un ejemplo de archivo de configuración sería el siguiente:

``` EditorConfig
[GLOBAL]
SRCDIR="./src" # source dir
INCDIR="./inc" # inlcude dir
OBJDIR="./obj" # object dir
CFLAGS=[ -Wall, -ansi, -pedantic ] # compilation flags
VGR_FLAGS="--leak-check=full -v" # valgrind flags

[set_tb]
TARGET="./set_tb_main"
SRCS=[ set, set_tb ]
# this env is sharing global configuration

[die_tb]
TARGET="./die_tb_main"
SRCS=[ die, die_tb ]
SRCDIR="./src2"
# this env is sharing global configuration
# object dir is overwritten and this
# environment will use ".src2/" as the default source dir.

[link_tb]
TARGET="./link_tb_main"
SRCS=[ link, link_tb ]
# this env is sharing global configuration
```

Para definnir un entorno en el archivo de configuración, debe usar la siguiente nomenclatura `[<env_name>]` donde **<env_name>** es el nombre del entorno.

| PARÁMETRO | DESCRIPCIÓN |
|--|--|
| TARGET | nombre del ejecutable |
| TARGET_ARGS | argumentos por defecto que se pasarán al ejecutable |
| DISTDIR | directorio de distribución, en el cual se guardarán los archivos de distribución. |
| OBJDIR | directorio donde se guardarán los archivos objeto |
| SRCDIR | el directorio donde se encuentran los recursos del ejecutable `*.c` |
| INCDIR | el directorio donde se encuentran los encabezados `*.h` |
| SRCS | el nombre de los múdulos que se necesitan para generar el ejecutable |
| LDFLAGS | parámetros que se deben de tener en cuenta a la hora de enlazar |
| CFLAGS | parámetros que se deben de tener en cuenta a la hora de compilar |
| ASCII_TITLE | archivo que contiene un título con decoración ASCII |
| ASCII_VERSION | archivo que contiene una versión con decoración ASCII |
| CLOG | archivo que contiene el historial de cambios |
