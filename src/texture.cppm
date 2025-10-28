module;
#include <glad/glad.h>
#include <SDL3/SDL_surface.h>
export module texture;
import std;
export namespace texture
{
    struct image_data
    {
        int width = 0;
        int height = 0;
        GLuint texture = 0;
    };

    // Simple helper function to load an image into a OpenGL texture with common settings
    void texture_from_surface(SDL_Surface *surface, image_data &image)
    {
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexImage2D(GL_TEXTURE_2D,
                     0,       // mipmap level
                     GL_RGBA, // internal format
                     surface->w, surface->h,
                     0,                // border
                     GL_RGBA,          // format of pixel data
                     GL_UNSIGNED_BYTE, // type of pixel data
                     surface->pixels);
        glGenerateMipmap(GL_TEXTURE_2D);
        image.texture = texture;
        image.height = surface->h;
        image.width = surface->w;
    }
}
