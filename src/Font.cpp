#include "Font.h"

#include <iostream>
#include <fstream>

void Font::Load(const char* path)
{
    std::ifstream myfile(path, std::ios::binary | std::ios::ate);
    if (!myfile.is_open()) {
        std::cerr << "Error opening .fnt file: " << path << "\n";
        return;
    }

    std::streampos size = myfile.tellg();
    myfile.seekg(0, std::ios::beg);

    // Read file identifier and version
    char fileIdentifier[4] = {}; // One extra byte for null terminator
    myfile.read(fileIdentifier, 3);

    if (std::string(fileIdentifier) != "BMF") {
        std::cerr << "Error: Not a valid BMF file.\n";
        return;
    }

    char version;
    myfile.read(&version, 1);
    if (version != 3) {
        std::cerr << "Error loading .fnt file: Unsupported format version " << static_cast<int>(version) << ".\n";
        return;
    }

    char blockType;
    int blockSize;

    // Info Block
    myfile.read(&blockType, 1);
    myfile.read(reinterpret_cast<char*>(&blockSize), 4);

    // Skipping info block content
    myfile.seekg(blockSize, std::ios::cur);

    // Common Block
    myfile.read(&blockType, 1);
    myfile.read(reinterpret_cast<char*>(&blockSize), 4);
    std::vector<char> commonBlock(blockSize);
    myfile.read(commonBlock.data(), blockSize);

    // Extract line height (assuming the line height is at the beginning of the common block)
    m_lineHeight = *reinterpret_cast<unsigned short*>(commonBlock.data());

    // Pages Block
    myfile.read(&blockType, 1);
    myfile.read(reinterpret_cast<char*>(&blockSize), 4);
    std::vector<char> pagesBlock(blockSize);
    myfile.read(pagesBlock.data(), blockSize);

    // Assuming page names are null-terminated strings, not handling multiple pages
    std::string texturePath(pagesBlock.data());
    m_texture = std::make_unique<Texture>();
    m_texture->Load(texturePath.c_str()); // Your Texture class needs a Load function

    // Chars Block
    myfile.read(&blockType, 1);
    myfile.read(reinterpret_cast<char*>(&blockSize), 4);
    int numChars = blockSize / 20;

    for (int i = 0; i < numChars; ++i) {
        CharInfo charInfo;
        myfile.read(reinterpret_cast<char*>(&charInfo), 20);

        // Convert to texture coordinates and store
        charInfo.texx0 /= m_texture->GetWidth();
        charInfo.texy0 /= m_texture->GetHeight();
        charInfo.texx1 = charInfo.texx0 + (charInfo.width / m_texture->GetWidth());
        charInfo.texy1 = charInfo.texy0 + (charInfo.height / m_texture->GetHeight());

        m_chars[charInfo.id] = charInfo;
    }

    // Kerning pairs are not handled in this example

    myfile.close();
}