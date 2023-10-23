#include "TextureManager.h"

#include <iostream>

#include "Texture.h"

static const std::string s_textureDirectoryPath = "data/images/";

void TextureManager::UnloadResources()
{
	std::cout << "Unloading textures\n";
	std::cout << "--------------------------------------------------------\n";
	for (auto& it : m_textureMap)
	{
		delete it.second;
		std::cout << "Unloaded texture: " << it.first << "\n";
	}
	std::cout << "--------------------------------------------------------\n\n";
}

bool TextureManager::LoadTexture(std::string name)
{
	std::string path = s_textureDirectoryPath + name + ".png";

	Texture* texture = new Texture();
	bool ret = texture->LoadFromFile(path.c_str());

	m_textureMap[name] = texture;

	return ret;
}

Texture* TextureManager::GetTexture(std::string name)
{
	Texture* temp = m_textureMap[name];
	if (!temp)
	{
		std::cerr << "ERROR: missing texture: " << name << "\n";
		abort();
	}

	return temp;
}