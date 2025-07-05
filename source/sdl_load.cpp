#include "sdl_load.hpp"
#include "SDL3/SDL_iostream.h"
#include "SDL3/SDL_filesystem.h"

void* SDL_LoadFileWrapper(const char* file, size_t* datasize)
{
    return SDL_LoadFile(file, datasize);
}
