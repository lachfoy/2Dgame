#pragma once

#include <map>
#include <string>

class Texture;

typedef std::map<std::string, Texture*> tTextureMap;

class TextureManager
{
public:
	TextureManager() {}
	~TextureManager() {}

	void UnloadResources();
	bool LoadTexture(std::string name);

	Texture* GetTexture(std::string name);

private:
	tTextureMap m_textureMap;

};