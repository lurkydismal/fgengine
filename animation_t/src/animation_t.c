#include "animation_t.h"

#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>

#include "stdfunc.h"

animation_t animation_t$load( SDL_Renderer* const* _renderer,
                              const char* _path,
                              const char* _pattern ) {
    animation_t l_returnValue = DEFAULT_ANIMATION;

    int l_fileCount = 0;

    const char* l_basePath = SDL_GetBasePath();
    char* l_path = duplicateString( _path );

    concatBeforeAndAfterString( &l_path, l_basePath, "/." );

    char** l_files = SDL_GlobDirectory(
        l_path, _pattern, SDL_GLOB_CASEINSENSITIVE, &l_fileCount );

    {
        l_returnValue.keyFrames =
            ( SDL_Texture** )createArray( sizeof( SDL_Texture* ) );
        l_returnValue.frames = ( Uint16** )createArray( sizeof( Uint16* ) );

        char* const* l_filesEnd = ( l_files + l_fileCount );

        preallocateArray( ( void*** )( &( l_returnValue.keyFrames ) ),
                          l_fileCount );

        for ( char** l_file = l_files; l_file != l_filesEnd; l_file++ ) {
            SDL_Log( "Loading file: \"%s\" as BMP\n", *l_file );

            const size_t l_indexInTextureArray = ( l_filesEnd - l_file );

            SDL_Surface* l_fileSufrace = SDL_LoadBMP( *l_file );

            SDL_Texture* l_fileTexture =
                SDL_CreateTextureFromSurface( *_renderer, l_fileSufrace );

            SDL_DestroySurface( l_fileSufrace );

            insertIntoArrayByIndex( ( void*** )( &( l_returnValue.keyFrames ) ),
                                    l_indexInTextureArray, l_fileTexture );

            // Trim filename and extension
            trim( *l_file, ( findLastSymbolInString( *l_file, '_' ) + 1 ),
                  findSymbolInString( *l_file, '.' ) );

            char** l_indexStartAndEndAsString =
                splitStringIntoArray( *l_file, "-" );

            const size_t l_indexStart =
                SDL_atoi( l_indexStartAndEndAsString[ 1 ] );
            const size_t l_indexEnd =
                SDL_atoi( l_indexStartAndEndAsString[ 2 ] );

            // Free 2 elements and l_indexStartAndEndAsString
            {
                SDL_free( l_indexStartAndEndAsString[ 1 ] );
                SDL_free( l_indexStartAndEndAsString[ 2 ] );

                SDL_free( l_indexStartAndEndAsString );
            }

            SDL_Log( "Frames from %d to %d\n", l_indexStart, l_indexEnd );

            preallocateArray( ( void*** )( &( l_returnValue.frames ) ),
                              ( l_indexEnd - l_indexStart ) );

            for ( size_t _index = l_indexStart; _index < l_indexEnd;
                  _index++ ) {
                size_t* l_indexInTextureArrayDuplicate =
                    ( size_t* )SDL_malloc( sizeof( size_t ) );
                *l_indexInTextureArrayDuplicate = l_indexInTextureArray;

                insertIntoArrayByIndex(
                    ( void*** )( &( l_returnValue.frames ) ), _index,
                    l_indexInTextureArrayDuplicate );
            }
        }
    }

    SDL_Log( "Loaded %u files from directory \"%s\"\n", l_fileCount, l_path );

EXIT:
    SDL_free( l_path );

    return ( l_returnValue );
}

void animation_t$unload( animation_t* _animation ) {}

void animation_t$step( animation_t* _animation, bool _canLoop ) {
    if ( arrayLength( _animation->frames ) > 1 ) {
        if ( _animation->currentFrame != arrayLength( _animation->frames ) ) {
            _animation->currentFrame++;

        } else {
            if ( _canLoop ) {
                _animation->currentFrame = 1;
            }
        }
    }
}
