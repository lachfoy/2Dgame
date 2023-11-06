#pragma once

#include <glad/glad.h>
#include "Texture.h"

#include <unordered_map>

// Order matters because we are reading contiguous memory into these structs
struct CharInfo
{
	unsigned int id;
	unsigned short x;
	unsigned short y;
	unsigned short width;
	unsigned short height;
	short xoffset;
	short yoffset;
	short xadvance;
	unsigned char page;
	unsigned char chnl;
};

struct KerningPair
{
	unsigned int first;
	unsigned int second;
	short amount;
};

class Font
{
public:
	Font() = default;
	~Font();

	CharInfo GetInfo(const char c) { return m_charInfos[c]; }

	Texture* GetTexture() { return m_texture; }

	void Load(const char* path);

private:
	Texture* m_texture;

	int m_lineHeight;
	std::unordered_map<unsigned int, CharInfo> m_charInfos;

	std::vector<KerningPair> m_kerningPairs;

};
