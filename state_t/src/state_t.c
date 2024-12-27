#include "state_t.h"

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_stdinc.h>

#include "stdfunc.h"

state_t state_t$create( SDL_Renderer* const* _renderer,
                        const char* _path,
                        const char* _name,
                        bool _isActionable ) {
    state_t l_returnValue = DEFAULT_STATE;

    l_returnValue.renderer = _renderer;
    l_returnValue.isActionable = _isActionable;

    // Load animation
    {
        char* l_pattern = duplicateString( "_*-*." );

        concatBeforeAndAfterString( &l_pattern, _name, "bmp" );

        l_returnValue.animation =
            animation_t$load( _renderer, _path, l_pattern );

        SDL_free( l_pattern );
    }

    return ( l_returnValue );
}

void state_t$destroy( state_t* _state ) {
    animation_t$unload( &( _state->animation ) );
}

void state_t$step( state_t* _state, bool _canLoop ) {
    animation_t$step( &( _state->animation ), _canLoop );
}
}
