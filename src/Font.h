#pragma once

#include <glad/glad.h>
#include "Texture.h"

#include <unordered_map>

struct CharInfo
{
    unsigned int id; // Add this to store the character ID
    float texx0;
    float texy0;
    float texx1;
    float texy1;
    unsigned short width;
    unsigned short height;
    short xoffset;
    short yoffset;
    short advance;
};

class Font
{
public:
	Font() = default;
	Font(const char* path);
	~Font();

	
    void Load(const char* path);

private:
	Texture* m_texture;

	int m_lineHeight;
	std::unordered_map<unsigned int, CharInfo> m_chars;


};
