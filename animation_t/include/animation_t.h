#pragma once

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>

#define DEFAULT_ANIMATION \
    { .keyFrames = NULL, .frames = NULL, .currentFrame = 0 }

typedef struct {
    SDL_Texture** keyFrames;
    Uint16** frames;
    Uint16 currentFrame;
} animation_t;

animation_t animation_t$load( SDL_Renderer* const* _renderer,
                              const char* _path,
                              const char* _pattern );
void animation_t$unload( animation_t* _animation );
void animation_t$step( animation_t* _animation, bool _canLoop );
