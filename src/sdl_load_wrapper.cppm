module;
#include "SDL3/SDL_filesystem.h"
#include "SDL3/SDL_iostream.h"

export module sdl_load_wrapper;
import std;

#ifndef __APPLE__
export void* SDL_LoadFileWrapper(const char* file, size_t* datasize)
{
    return SDL_LoadFile(file, datasize);
}
#else
export void* SDL_LoadFileWrapper(const char* file, size_t* datasize)
{
    std::string full_path = std::string(SDL_GetBasePath()) + file;
    return SDL_LoadFile(full_path.c_str(), datasize);
}
#endif
