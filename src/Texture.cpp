//#include "Texture.h"
//
//#include <cassert>
//#include <iostream>
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"
//
//Texture::~Texture()
//{
//    glBindTexture(GL_TEXTURE_2D, 0);
//    glDeleteTextures(1, &m_textureId);
//}
//
//bool Texture::LoadFromFile(const char *path, bool useMipMaps)
//{
//    int width, height, numChannels;
//    unsigned char *data = stbi_load(path, &width, &height, &numChannels, 0);
//    if (data == nullptr)
//    {
//        std::cout << stbi_failure_reason() << "\n";
//        assert(false);
//    }
//
//    // create and bind texture
//    glGenTextures(1, &m_textureId);
//    glBindTexture(GL_TEXTURE_2D, m_textureId);
//
//    // set the texture data
//    GLint format;
//    switch(numChannels)
//    {
//        case 3:
//            format = GL_RGB;
//            break;
//        case 4:
//            format = GL_RGBA;
//            break;
//        default:
//            assert(false);
//    }
//    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//    stbi_image_free(data);
//
//    // set params
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//    if (useMipMaps)
//    {
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//
//    // unbind
//    glBindTexture(GL_TEXTURE_2D, 0);
//
//    return true;
//}
//
//void Texture::Bind() const
//{
//    glBindTexture(GL_TEXTURE_2D, m_textureId);
//}
