


//void wallTextures() {
//    unsigned char* top = SOIL_load_image("textures_game/stone-bricks.png", &W, &H, 0, SOIL_LOAD_RGB); // загружаем текстуру в soil
//    glGenTextures(1, &wall[0]); // говорим, что начинаем работать с переменной Dirt, чтобы дальше записать в нее текстуру soil
//    glBindTexture(GL_TEXTURE_2D, wall[0]); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, top); // загружаем текстуру soil в перменную dirt
//    SOIL_free_image_data(top); // освобождаем текстуру из soil
//    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
//}
//
//void screamerTextures() {
//    unsigned char* top = SOIL_load_image("textures_game/screamer.png", &W, &H, 0, SOIL_LOAD_RGB); // загружаем текстуру в soil
//    glGenTextures(1, &screamer[0]); // говорим, что начинаем работать с переменной Dirt, чтобы дальше записать в нее текстуру soil
//    glBindTexture(GL_TEXTURE_2D, screamer[0]); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, top); // загружаем текстуру soil в перменную dirt
//    SOIL_free_image_data(top); // освобождаем текстуру из soil
//    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
//}
//
//void polTextures() {
//    unsigned char* top = SOIL_load_image("textures_game/floor.png", &W, &H, 0, SOIL_LOAD_RGB); // загружаем текстуру в soil
//    glGenTextures(1, &pol[0]); // говорим, что начинаем работать с переменной Dirt, чтобы дальше записать в нее текстуру soil
//    glBindTexture(GL_TEXTURE_2D, pol[0]); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object
//
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, top); // загружаем текстуру soil в перменную dirt
//    SOIL_free_image_data(top); // освобождаем текстуру из soil
//    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
//}

void load_textures(const char* image, GLuint* texturesy, bool type) {
    unsigned char* top = SOIL_load_image(image, &W, &H, 0, SOIL_LOAD_RGBA); // загружаем текстуру в soil
    glGenTextures(1, texturesy); // говорим, что начинаем работать с переменной Dirt, чтобы дальше записать в нее текстуру soil
    glBindTexture(GL_TEXTURE_2D, *texturesy); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    if (type) {
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.8f);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, top); // загружаем текстуру soil в перменную dirt
    SOIL_free_image_data(top); // освобождаем текстуру из soil
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void load_textures_smooth(const char* image, GLuint* texturesy, bool type) {
    unsigned char* top = SOIL_load_image(image, &W, &H, 0, SOIL_LOAD_RGBA); // загружаем текстуру в soil
    glGenTextures(1, texturesy); // говорим, что начинаем работать с переменной Dirt, чтобы дальше записать в нее текстуру soil
    glBindTexture(GL_TEXTURE_2D, *texturesy); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (type) {
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.8f);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, top); // загружаем текстуру soil в перменную dirt
    SOIL_free_image_data(top); // освобождаем текстуру из soil
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}
