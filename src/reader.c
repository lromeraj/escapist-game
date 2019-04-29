/**
 * @brief Main game reader
 *
 * This module is under hard changes, use it with caution
 *
 * @file reader.c
 * @version 1.0
 * @date 07/02/2019
 * @author Javier Romera
 * @copyright GNU Public License
 */

#include "str.h"
#include "reader.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define MAX_BUFF 128
#define MAX_CHECKS 5
#define READER_MAX_ATTRS 20

#define _OBJECT_SYM "@o"
#define _SPACE_SYM "@s"
#define _LINK_SYM "@l"

#define ANSI_RESET   				"\033[0m"
#define ANSI_FG_RED     		"\033[31m"
#define ANSI_FG_GREEN   		"\033[32m"
#define ANSI_FG_YELLOW  		"\033[33m"
#define ANSI_FG_BLUE    		"\033[34m"
#define ANSI_FG_PURPLE 			"\033[35m"
#define ANSI_FG_WHITE 			"\033[97m"
#define ANSI_FG_CYAN    		"\033[36m"

#define ANSI_FG_BRED     		"\033[1;31m"
#define ANSI_FG_BWHITE 			"\033[1;97m"
#define ANSI_FG_BGREEN   		"\033[1;32m"
#define ANSI_FG_BYELLOW  		"\033[1;33m"
#define ANSI_FG_BBLUE    		"\033[1;34m"
#define ANSI_FG_BPURPLE 		"\033[1;35m"
#define ANSI_FG_BCYAN    		"\033[1;36m"

typedef enum {
	_PERROR,
	_PWARN,
	_PSUCCESS,
	_PINFO
} PrintType;

typedef enum {
  _INT,
  _LONG,
  _STR,
  _STR_ARR
} Attr_type;

typedef enum {
	_NULL_CHECK=1,
	_ID_CHECK,
	_LEN_CHECK,
	_END_CHECK
} Attr_check;

enum {
  _NONE=-1 /* !!! important */
};

enum _Obj_attrs {
  _OBJ_ID,
  _OBJ_NAME,
  _OBJ_DESCRP,
	_OBJ_LDESCRP,
  _OBJ_LOC,
	_OBJ_MOVABLE,
	_OBJ_MOVED,
	_OBJ_HIDDEN,
	_OBJ_ILLUMINATE,
	_OBJ_ON,
	_OBJ_LINKS
};

enum _Sp_attrs {
  _SPACE_ID,
  _SPACE_NAME,
  _SPACE_PICTURE,
  _SPACE_LINKS,
  _SPACE_DESCRP,
  _SPACE_LDESCRP
};

enum _Ln_attrs {
  _LINK_ID,
  _LINK_NAME,
  _LINK_FROM,
  _LINK_TO,
  _LINK_STS
};

typedef int (*parse_cb)( Game *game );

Attr_type ATTR_TYPE[ READER_MAX_ATTRS ];
void *ATTR_DATA[ READER_MAX_ATTRS ];
int ATTR_LINE[ READER_MAX_ATTRS ] = {0};
char ATTR_NAME[ READER_MAX_ATTRS ][ MAX_BUFF ] = {{0}};
int LBL = 1; /* last block line */

int rd_get_attr_by_name( const char *_name );
void rd_free_attr_data();
void rd_free_attr( int attr );
void rd_set_attr( int attr, ... );
void* rd_get_attr( int attr, ... );
void rd_alloc_attr( int attr, ... );
int rd_check_attr( int attr, const char *pref, ... );
int _parse( Game *game, const char *f_name, const char *pref, parse_cb cb );

void _prt( PrintType type, const char *frmt, ... );

int _parse_link( Game *game ) {

  Id id, from, to;
  int errc;
  Link *ln;
  LinkState sts;

  char *_id, *_name, *_from, *_to, *_sts;

  errc = 0;

  _id = rd_get_attr( _LINK_ID, 1 );
  _name = rd_get_attr( _LINK_NAME, 1 );
  _from = rd_get_attr( _LINK_FROM, 1 );
  _to = rd_get_attr( _LINK_TO, 1 );
  _sts = rd_get_attr( _LINK_STS, 1 );

	errc+=rd_check_attr( _LINK_ID, _LINK_SYM, _NULL_CHECK, _ID_CHECK, _END_CHECK );
	errc+=rd_check_attr( _LINK_FROM, _LINK_SYM, _NULL_CHECK, _ID_CHECK, _END_CHECK );
	errc+=rd_check_attr( _LINK_TO, _LINK_SYM, _NULL_CHECK, _ID_CHECK, _END_CHECK );
	errc+=rd_check_attr( _LINK_STS, _LINK_SYM, _NULL_CHECK, _END_CHECK );

	if ( !errc ) {

		id = atol( _id );
		from = atol( _from );
		to = atol( _to );
		sts = LINK_CLOSED;

		if ( !strcmptok( _sts, "1,true,opened", "," ) ) {
			sts = LINK_OPENED;
		} else if ( !strcmptok( _sts, "0,false,closed", "," ) ) {
			sts = LINK_CLOSED;
		}

		ln = link_create( id );

		link_set_name( ln, _name );
		link_set_from( ln, from );
		link_set_to( ln, to );
		link_set_state( ln, sts );

		if ( game_add_link( game, ln ) == ERROR ) {
			_prt( _PERROR, "could not add link #%d, block %d (possible id conflict)\n", link_get_id( ln ), LBL );
			link_destroy( ln );
			errc = 1;
		} else {
			errc = 0;
		}

	}

  return errc;
}

int _parse_space( Game *game ) {

  Id id;
  int i, errc;
  Space *sp;
	CardinalPoint cps[6] = {N,E,S,W,U,D}; /* cardinal points */

  char *_id, *_name, *_descrp, *_ldescrp, *_pict, **_links;

  errc = 0;

  _id = rd_get_attr( _SPACE_ID, 1 );
  _name = rd_get_attr( _SPACE_NAME, 1 );
  _descrp = rd_get_attr( _SPACE_DESCRP, 1 );
  _ldescrp = rd_get_attr( _SPACE_LDESCRP, 1 );
  _pict = rd_get_attr( _SPACE_PICTURE, 1 );
  _links = ((char**)ATTR_DATA[ _SPACE_LINKS ]);

	errc+=rd_check_attr( _SPACE_LINKS, _SPACE_SYM, _NULL_CHECK, _LEN_CHECK, 4, _END_CHECK );
	errc+=rd_check_attr( _SPACE_ID, _SPACE_SYM, _NULL_CHECK, _ID_CHECK, _END_CHECK );

	if ( !errc ) {

		id = _id ? atol( _id ) : NO_ID;

		sp = space_create( id );

		space_set_name( sp, _name );
		space_set_descrp( sp, _descrp );
		space_set_ldescrp( sp, _ldescrp );
		space_set_picture( sp, _pict );


		if ( _links ) { /* !!! improve this */

			for ( i=1; _links[i]; i++ ) {
				space_set_link( sp, cps[i-1], atol( _links[ i ] ) );
			}

		}

		if ( game_add_space( game, sp ) == ERROR ) {
			_prt( _PERROR, "could not add space #%d, block %d (possible id conflict)\n", space_get_id( sp ), LBL );
			space_destroy( sp );
			errc = 1;
		} else {
			errc = 0;
		}

	}


  return errc;
}

int _parse_object( Game *game ) {

  int i, errc;
  Id id, loc;
  Object *obj;
	char *attrs[ MAX_OBJ_ATTRS ] = {NULL}; /* object attrs */

  char *_id, *_name, *_descrp, *_ldescrp, *_loc, **_links;

  errc = 0;

	errc+= rd_check_attr( _OBJ_ID, _OBJECT_SYM, _NULL_CHECK, _ID_CHECK, _END_CHECK );

	_id = rd_get_attr( _OBJ_ID, 1 );
	_name = rd_get_attr( _OBJ_NAME, 1 );
	_descrp = rd_get_attr( _OBJ_DESCRP, 1 );
	_ldescrp = rd_get_attr( _OBJ_LDESCRP, 1 );
	_loc = rd_get_attr( _OBJ_LOC, 1 );
	_links = ((char**)ATTR_DATA[ _OBJ_LINKS ]);

	attrs[ OBJ_CAN_ILLUMINATE ] = rd_get_attr( _OBJ_ILLUMINATE, 1 );
	attrs[ OBJ_IS_HIDDEN ] = rd_get_attr( _OBJ_HIDDEN, 1 );
	attrs[ OBJ_IS_MOVABLE ] = rd_get_attr( _OBJ_MOVABLE, 1 );
	attrs[ OBJ_IS_MOVED ] = rd_get_attr( _OBJ_MOVED, 1 );
	attrs[ OBJ_IS_ON ] = rd_get_attr( _OBJ_ON, 1 );

	id = _id ? atol( _id ) : NO_ID;
	loc = _loc ? atol( _loc ) : NO_ID;

	if ( !errc ) {

		obj = obj_create( id );

		obj_set_name( obj, _name );
		space_add_object( game_get_space( game, loc ), id );
		obj_set_descrp( obj, _descrp );
		obj_set_ldescrp( obj, _ldescrp );

		if ( _links ) {

			for ( i=0; _links[ i ]; i++ ) {
				id = atol( _links[ i ] );
				if ( obj_add_link( obj, id ) == ERROR ) {
					_prt( _PERROR, "could not add link %d to object '%s', line: %d\n", id, obj_get_name( obj ), ATTR_LINE[ _OBJ_LINKS ] );
				}
			}

		}

		for ( i=0; i<MAX_OBJ_ATTRS; i++ ) {

			if ( !attrs[ i ] ) continue;

			if ( !strcmptok( attrs[ i ], "yes,y,true", "," ) ) {
				obj_set_attr( obj, i, OBJ_YES );
			} else if ( !strcmptok( attrs[ i ], "no,n,false", "," ) ) {
				obj_set_attr( obj, i, OBJ_NO );
			} else {
				obj_set_attr( obj, i, atol( attrs[ i ] ) );
			}

		}

		if ( game_add_object( game, obj ) == ERROR ) {
			_prt( _PERROR, "could not add object #%d (possible id conflict)\n", obj_get_id( obj ) );
			obj_destroy( obj );
			errc = 1;
		} else {
			errc = 0;
		}

	}

  return errc;
}


int reader_load( Game *game, const char *f_name, int it ) {

  int errc;

  if ( !game || !f_name )
    return ERROR;

  errc=1;

  if ( it == _RD_OBJS ) {

    ATTR_TYPE[ _OBJ_NAME ] = _STR_ARR;
    ATTR_TYPE[ _OBJ_DESCRP ] = _STR_ARR;
    ATTR_TYPE[ _OBJ_ID ] = _STR_ARR;
    ATTR_TYPE[ _OBJ_LOC ] = _STR_ARR;
    ATTR_TYPE[ _OBJ_LDESCRP ] = _STR_ARR;
		ATTR_TYPE[ _OBJ_LINKS ] = _STR_ARR;
    ATTR_TYPE[ _OBJ_MOVABLE ] = _STR_ARR;
    ATTR_TYPE[ _OBJ_MOVED ] = _STR_ARR;
    ATTR_TYPE[ _OBJ_HIDDEN ] = _STR_ARR;
    ATTR_TYPE[ _OBJ_ILLUMINATE ] = _STR_ARR;
    ATTR_TYPE[ _OBJ_ON ] = _STR_ARR;

    strcpy( ATTR_NAME[ _OBJ_NAME ], "name" );
    strcpy( ATTR_NAME[ _OBJ_ID ], "id" );
    strcpy( ATTR_NAME[ _OBJ_DESCRP ], "descrp" );
		strcpy( ATTR_NAME[ _OBJ_LDESCRP ], "ldescrp" );
    strcpy( ATTR_NAME[ _OBJ_LOC ], "location" );
    strcpy( ATTR_NAME[ _OBJ_LINKS ], "links" );

		/* enclosed object attrs */
    strcpy( ATTR_NAME[ _OBJ_MOVABLE ], "movable" );
    strcpy( ATTR_NAME[ _OBJ_MOVED ], "moved" );
    strcpy( ATTR_NAME[ _OBJ_HIDDEN ], "hidden" );
    strcpy( ATTR_NAME[ _OBJ_ILLUMINATE ], "illuminate" );
    strcpy( ATTR_NAME[ _OBJ_ON ], "on" );

    errc = _parse( game, f_name,  "@o", (parse_cb)_parse_object );

  }

  if ( it == _RD_SPACES ) {

    ATTR_TYPE[ _SPACE_ID ] = _STR_ARR;
    ATTR_TYPE[ _SPACE_NAME ] = _STR_ARR;
    ATTR_TYPE[ _SPACE_DESCRP ] = _STR_ARR;
    ATTR_TYPE[ _SPACE_LDESCRP ] = _STR_ARR;
    ATTR_TYPE[ _SPACE_LINKS ] = _STR_ARR;
    ATTR_TYPE[ _SPACE_PICTURE ] = _STR_ARR;

    strcpy( ATTR_NAME[ _SPACE_ID ], "id" );
    strcpy( ATTR_NAME[ _SPACE_NAME ], "name" );
    strcpy( ATTR_NAME[ _SPACE_DESCRP ], "descrp" );
    strcpy( ATTR_NAME[ _SPACE_DESCRP ], "descrp" );
    strcpy( ATTR_NAME[ _SPACE_LDESCRP ], "ldescrp" );
    strcpy( ATTR_NAME[ _SPACE_LINKS ], "links" );
    strcpy( ATTR_NAME[ _SPACE_PICTURE ], "picture" );

    errc = _parse( game, f_name, "@s", (parse_cb)_parse_space );
  }

  if ( it == _RD_LINKS ) {

    ATTR_TYPE[ _LINK_ID ] = _STR_ARR;
    ATTR_TYPE[ _LINK_NAME ] = _STR_ARR;
    ATTR_TYPE[ _LINK_FROM ] = _STR_ARR;
    ATTR_TYPE[ _LINK_TO ] = _STR_ARR;
    ATTR_TYPE[ _LINK_STS ] = _STR_ARR;

    strcpy( ATTR_NAME[ _LINK_ID ], "id" );
    strcpy( ATTR_NAME[ _LINK_NAME ], "name" );
    strcpy( ATTR_NAME[ _LINK_FROM ], "from" );
    strcpy( ATTR_NAME[ _LINK_TO ], "to" );
    strcpy( ATTR_NAME[ _LINK_STS ], "state" );

    errc = _parse( game, f_name, "@l", (parse_cb)_parse_link );
  }

  return errc;

}

int rd_get_attr_by_name( const char *_name ) {

	int i;
	int _p;

	if ( !_name )
		return _NONE;

	_p = _NONE;

	for ( i=0; i<READER_MAX_ATTRS; i++ ) {
		if ( !strcmp( ATTR_NAME[ i ], _name ) ) {
			_p = i;
			break;
		}
	}

	return _p;
}


void rd_free_attr_data() {
  int i;
	for ( i=0; i<READER_MAX_ATTRS; i++ ) {
		rd_free_attr( i );
	}
}

void* rd_get_attr( int attr, ... ) {

  int i, idx;
	void *vp;
	va_list _list;
  Attr_type type;

	if ( !ATTR_DATA[ attr ] || attr < 0 || attr >= READER_MAX_ATTRS )
		return NULL;

	vp = NULL;
	va_start( _list, attr );

  type = ATTR_TYPE[ attr ];
	if ( type == _STR_ARR ) {

		if ( ATTR_DATA[ attr ] ) {

      i = 0;
			idx = va_arg( _list, int );
			while ( i != idx ) {

				if ( !((char**)ATTR_DATA[ attr ])[ i ] ) {
					break;
				} else {
					i++;
				}
			}

			vp = ((char**)ATTR_DATA[ attr ])[ i ];

		}

	}

	va_end( _list );

	return vp;
}

void rd_set_attr( int attr, ... ) {

  int idx, len;
	char *str;
	va_list _list;
	char **__arr;
  Attr_type type;

	if ( !ATTR_DATA[ attr ] || attr < 0 || attr >= READER_MAX_ATTRS )
		return;

	va_start( _list, attr );

  type = ATTR_TYPE[ attr ];

	if ( type == _STR_ARR ) {

		idx = va_arg( _list, int );
		str = va_arg( _list, char* );

		len = str ? strlen( str ) : 0;

		if ( len ) {

			__arr = ((char**)ATTR_DATA[ attr ]);

			if ( __arr[ idx ] ) {
				free( __arr[ idx ] );
			}

			__arr[ idx ] = (char*)malloc( (len+1)*sizeof( char ) );

			if ( __arr[ idx ] ) {
				strcpy( __arr[ idx ], str );
			}

		}

	}

	va_end( _list );

}

void rd_free_attr( int attr ) {

	int i;
  Attr_type type;

  if ( attr < 0 || attr >= READER_MAX_ATTRS )
		return;

  type = ATTR_TYPE[ attr ];

	if ( type == _STR_ARR ) {

		if ( ATTR_DATA[ attr ] ) {

			for (i=0; ((char**)ATTR_DATA[attr])[i]; i++) {
				free( ((char**)ATTR_DATA[attr])[i] );
				((char**)ATTR_DATA[attr])[i] = NULL;
			}

			free( ATTR_DATA[ attr ] );

		}

	}

  ATTR_DATA[ attr ] = NULL;

}

void rd_alloc_attr( int attr, ... ) {

  int i, q;
	va_list _list;
  Attr_type type;

	if ( attr < 0 || attr >= READER_MAX_ATTRS )
		return;

	rd_free_attr( attr );
	va_start( _list, attr );

  type = ATTR_TYPE[ attr ];

	if ( type == _STR_ARR ) {

		q = va_arg( _list, int )+1; /* use extra space for NULL end */

		ATTR_DATA[ attr ] = (char**)malloc( q*sizeof(char*) );

		if ( ATTR_DATA[ attr ] ) {
			for (i=0; i<q; i++) {
				((char**)ATTR_DATA[ attr ])[ i ] = NULL;
			}
		}

	}

	va_end( _list );

}

int _parse(
  Game* game,
  const char *f_name,
  const char *pref,
  parse_cb cb
) {

  FILE *_f;

	int i, j,
      _al, /* attr line index */
      _bl, /* block line index */
			sts, /* overall status */
			vi, /* value index */
			len, /* used for string lengths */
      _p, /* conf parameter */
      pref_len; /* prefix length */
  char c;
	char _line[ 1024 ] = "";
	char _vbuff[ 10 ][ 1024 ] = {{0}};
	bool  addChar, /* indicates is a char shold be added to the buffer */
				isArr, /* indicates if the current value is an array */
				isStr, /* indicates if the current value is a string */
        blockEnd, /* indicates the end of a block */
        blockSearch, /* this flags is used to find blocks */
        rs, /* reset */
        attrEnd; /* indicates the end of attribute parse */

	_f = fopen( f_name, "r" );

	if ( !_f )
		return 1;

  pref_len = strlen( pref );

  _al = 0;
  _bl = 0;
  j=0;
	vi=0;
	sts=0;
  rs=false;
	attrEnd=false;
	isArr=false;
	isStr=false;
  blockEnd=false;
  blockSearch=true;
	_p = _NONE;

	while ( fgets( _line, sizeof( _line ), _f ) ) {

    _al++;

		_line[ strlen( _line ) - 1 ] = 0; /* cleans \n */

    /* env search */
		if ( blockSearch ) {

			if ( !strncmp( _line, pref, pref_len ) ) {
        _bl=_al;
				LBL=_bl;
        blockSearch = false;
			} else {
        continue;
      }

		}

		len = strlen( _line ); /* get the length of the line */

		for (i=0; i<=len; i++) {

			c = _line[ i ];
			addChar = true;

			if ( c == '#' && !isStr ) {
				i = len;
				addChar = false;
			}

      if ( c == '}' && !isStr ) {
        blockEnd = true;
        attrEnd=true;
        addChar = false;
      }

      if ( c == '{' && !isStr ) {
        addChar = false;
        rs = true;
      }

			if ( c == ':' && vi == 0 && !isStr ) {
				vi=1;
				j=0;
				addChar = false;
			}

			if ( c == ' ' || c == '\t' ) {
				addChar = false;
			}

			if ( c == '[' ) {
				isArr=true;
				addChar=false;
			}

			if ( c == ']' ) {
				isArr=false;
				addChar=false;
			}

      if ( c == ',' ) {

        if ( isArr && !isStr ) {
          j=0;
          vi++;
          addChar = false;
        }

        if ( !isArr && !isStr ) {
          attrEnd = true;
          addChar = false;
        }

      }

			if ( c == '"' ) {
				isStr = !isStr;
				addChar = false;
			}

			if ( isStr && c != '"' ) addChar = true;

			if ( c == '\0' || c == ' ' || c == '#' || c == ',' ) {

        /* values buffer is not empty */
				if ( _vbuff[ 1 ][ 0 ] != '\0' && vi == 1 && !isStr && !isArr ) {
					attrEnd = true;
					addChar = false;
				}

			}

			if ( addChar && c ) {
				_vbuff[ vi ][ j ] = c;
				_vbuff[ vi ][ j + 1 ] = 0;
				j++;
			}

			if ( attrEnd ) {

        if ( _vbuff[ 1 ][ 0 ] ) {

          vi++;
          _p = rd_get_attr_by_name( _vbuff[ 0 ] );

          if ( _p != _NONE ) {

            rd_alloc_attr( _p, vi );

            ATTR_LINE[ _p ] = _al;

            for ( j=0; j<vi; j++ ) {
              rd_set_attr( _p, j, _vbuff[ j ] );
            }

          }

        }
        rs=true;

			}

      if ( blockEnd ) {

				sts+=cb( game );

        blockEnd = false;
        blockSearch = true;
        rs=true;

				rd_free_attr_data();
      }

      if ( rs ) {

        /* clean buffers */
				for ( j=0; j<vi; j++ ) {
					_vbuff[ j ][ 0 ] = 0;
				}

				/* reset flags */
				j=0;
				vi=0;
				isArr=false;
				isStr=false;
				attrEnd=false;
        blockEnd=false;
				addChar = false;

        rs=false;
      }

		}

	}

	fclose( _f );

  return sts;

}


int rd_check_attr( int attr, const char *pref, ... ) {

	int i, n, sts;
	void *data;
	void *_vp;
	va_list _list;
	Attr_check chk;
	long _id; /* temporary id */

	if ( attr < 0 || attr >= READER_MAX_ATTRS )
		return -1;

	data = ATTR_DATA[ attr ];
	sts = 0;

	va_start( _list, pref );

	chk = va_arg( _list, Attr_check );

	while ( chk != _END_CHECK ) {

		if ( chk == _NULL_CHECK ) {

			if ( !data ) {
				sts = _NULL_CHECK;
				_prt( _PERROR, "\033[1m%s\033[0m { ... } '%s' is required in block %d\n", pref, ATTR_NAME[ attr ], LBL );
				break;
			}

		}

		if ( chk == _ID_CHECK ) {

			_vp = (char*)rd_get_attr( attr, 1 );
			_id = _vp ? atol( _vp ) : NO_ID;

			if ( _id < 0 ) {
				sts = _ID_CHECK;
				_prt( _PERROR, "\033[1m%s\033[0m { ... } invalid '%s', line %d\n", pref, ATTR_NAME[ attr ], ATTR_LINE[ attr ] );
			}

		}

		if ( chk == _LEN_CHECK ) {

			_vp = (char**)ATTR_DATA[ attr ];
			n = va_arg( _list, int );

			for ( i=1; ((void**)_vp)[ i ]; i++ );
			i--;

			if ( i != n ) {
				sts = _LEN_CHECK;
				_prt( _PERROR, "\033[1m%s\033[0m { ... } invalid '%s' list, expected %d, have %d, line: %d\n",
					pref,
					ATTR_NAME[ attr ],
					n, i,
					ATTR_LINE[ attr ]
				);
			}

		}

		chk = va_arg( _list, Attr_check );
	}


	va_end( _list );

	return sts;
}

void _prt( PrintType type, const char *frmt, ... ) {

	va_list _list;
	char _buff[ 1024 ];

	va_start( _list, frmt );
	vsprintf( _buff, frmt, _list );
	va_end( _list );

	switch ( type ) {

		case _PERROR:
			printf( "%serror%s: %s", ANSI_FG_BRED, ANSI_RESET, _buff );
			break;
		case _PSUCCESS:
			printf( "%ssuccess%s: %s", ANSI_FG_BGREEN, ANSI_RESET, _buff );
			break;
		case _PINFO:
			printf( "%sinfo%s: %s", ANSI_FG_BCYAN, ANSI_RESET, _buff );
			break;
		case _PWARN:
			printf( "%swarn%s: %s", ANSI_FG_BYELLOW, ANSI_RESET, _buff );
			break;
	}

	fflush( stdout );

}
