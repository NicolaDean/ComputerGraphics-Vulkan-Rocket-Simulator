//
// Created by nicomane on 02/06/22.
//

#include "Texture.h"


namespace Engine{


    void Texture::load() {
        textureManager.createTextureImage(name);
        textureManager.createTextureImageView();
        textureManager.createTextureSampler();
    }

    void Texture::loadCubic() {
        textureManager.createCubicTexture(name);
        textureManager.createTextureImageViewSkybox();
        textureManager.createTextureSampler();
    }

}