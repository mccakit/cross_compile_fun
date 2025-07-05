#include "sdl_load.hpp"
#include "SDL3/SDL_iostream.h"
#include "SDL3/SDL_filesystem.h"
#include <string>
void* SDL_LoadFileWrapper(const char* file, size_t* datasize)
{
    std::string full_path = std::string(SDL_GetBasePath()) + file;
    return SDL_LoadFile(full_path.c_str(), datasize);
}
