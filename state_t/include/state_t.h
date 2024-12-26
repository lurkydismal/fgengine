#pragma once

#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>

#include "animation_t.h"

#define DEFAULT_STATE \
    { .animation = DEFAULT_ANIMATION, .isActionable = true, .renderer = NULL }

typedef struct {
    SDL_Renderer* const* renderer;
    animation_t animation;
    bool isActionable;
    bool isLooping;
} state_t;

state_t state_t$create( SDL_Renderer* const* _renderer,
                        const char* _path,
                        const char* _name,
                        bool _isActionable,
                        bool _isLooping );
void state_t$destroy( state_t* _state );
void state_t$step( state_t* _state );
