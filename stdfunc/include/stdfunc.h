#pragma once

#include <SDL3/SDL_stdinc.h>

#define trim( _string, _from, _to ) \
    do {                            \
        ( _string ) += _from;       \
        ( _string )[ _to ] = '\0';  \
    } while ( false );

// TODO: Fix arrayLastElementPointer pointing outside of array
#define arrayLength( _array ) ( ( Uint64 )( _array[ 0 ] ) - 1 )
#define arrayFirstElementPointer( _array ) ( _array + 1 )
#define arrayLastElementPointer( _array ) \
    ( ( arrayFirstElementPointer( _array ) - 1 ) + arrayLength( _array ) )

#define _findStringInArray( _array, _value )                      \
    ( findStringInArray(                                          \
          ( const char** )( arrayFirstElementPointer( _array ) ), \
          arrayLength( _array ), _value ) +                       \
      1 )

#define _findInArray( _array, _value )                                      \
    findInArray( arrayFirstElementPointer( _array ), arrayLength( _array ), \
                 _value )

#define _containsString( _array, _value )                                   \
    containsString( ( const char** )( arrayFirstElementPointer( _array ) ), \
                    arrayLength( _array ), _value )

#define _contains( _array, _value )                                      \
    contains( arrayFirstElementPointer( _array ), arrayLength( _array ), \
              _value )

#define FOR( _type, _array )                                         \
    for ( _type _element = _array;                                   \
          _element <                                                 \
          ( _array + ( sizeof( _array ) / sizeof( _array[ 0 ] ) ) ); \
          _element++ )

// TODO: Fix FOR_ARRAY getting out of range
#define FOR_ARRAY( _type, _array )                             \
    for ( _type _element = arrayFirstElementPointer( _array ); \
          _element != ( arrayLastElementPointer( _array ) + 1 ); _element++ )

// TODO: Fix FREE_ARRAY getting out of range
#define FREE_ARRAY( _type, _array, _elementToFree ) \
    FOR_ARRAY( _type, _array ) {                    \
        /*                                          \
        SDL_Log( "{\n" );                           \
        SDL_Log( "%p\n", _elementToFree );          \
        SDL_Log( "}\n" );                           \
        */                                          \
                                                    \
        SDL_free( _elementToFree );                 \
    }                                               \
    SDL_free( _array )

Uint32 lengthOfNumber( Uint32 _number );
Sint64 power( Sint64 _base, Uint8 _exponent );
char* convertNumberToString( Uint32 _number );
char* duplicateString( const char* _string );
Sint32 findSymbolInString( const char* _string, const char _symbol );
Sint32 findLastSymbolInString( const char* _string, const char _symbol );
Uint32 concatBeforeAndAfterString( char** _string,
                                   const char* _beforeString,
                                   const char* _afterString );
char* sanitizeString( const char* _string );
char** splitStringIntoArray( const char* _string, const char* _delimiter );
void** createArray( const Uint32 _elementSize );
void preallocateArray( void*** _array, const Uint32 _length );
Uint32 insertIntoArray( void*** _array, void* _value );
void insertIntoArrayByIndex( void*** _array,
                             const Uint32 _index,
                             void* _value );
Sint32 findStringInArray( const char** _array,
                          const Uint32 _arrayLength,
                          const char* _value );
Sint32 findInArray( const Uint32* _array,
                    const Uint32 _arrayLength,
                    const Uint32 _value );
bool containsString( const char** _array,
                     const Uint32 _arrayLength,
                     const char* _value );
bool contains( const Uint32* _array,
               const Uint32 _arrayLength,
               const Uint32 _value );

#if 0
void freeSettingsContent( char*** _content );
Sint32 findKeyInSettings( char*** _settings, const char* _key );
Sint32 findValueInSettings( char*** _settings, const char* _value );
char*** getLabelFromSettingsOrDefault( const char* _label,
                                       const char* _default );
char* getKeyFromSettingsOrDefault( const char* _label,
                                   const char* _key,
                                   const char* _default );
#endif
