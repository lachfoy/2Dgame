//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include "Game.h"

constexpr int kScreenWidth = 800;
constexpr int kScreenHeight = 600;

int main(int argc, char* argv[])
{
    //srand(time(NULL));

    //// Load texture
    //int imageWidth, imageHeight, nChannels;
    //unsigned char* imageData = stbi_load("../data/sprites.png", &imageWidth, &imageHeight, &nChannels, 0);
    //const char* failureReason = stbi_failure_reason();
    //if (failureReason)
    //{
    //    std::cout << failureReason << "\n";
    //}

    //GLuint textureID;
    //glGenTextures(1, &textureID);
    //glBindTexture(GL_TEXTURE_2D, textureID);

    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // Minification filter
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST); // Magnification filter
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // Wrapping mode for S coordinate
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Wrapping mode for T coordinate

    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    //glBindTexture(GL_TEXTURE_2D, 0);
    //stbi_image_free(imageData);



    //glDeleteTextures(1, &textureID);

    Game game;
    if (game.Init(kScreenWidth, kScreenHeight, false, "test"))
        game.Run();

	return 0;
}