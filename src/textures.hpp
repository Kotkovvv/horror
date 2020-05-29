GLuint wall;///<Переменная для текстуры стены психушки
GLuint wall2;///<Переменная для текстуры стены замка
GLuint screamer;///<Переменная для текстуры скримера
GLuint floor1;///<Переменная для текстуры пола психушки
GLuint floor2;///<Переменная для текстуры пола
GLuint flash;///<Переменная для текстуры фонарика
GLuint texture[3];
GLuint backg;///<Переменная для текстуры заднего фона меню
GLuint exi;///<Переменная для текстуры кнопки выхода
GLuint cont;///<Переменная для текстуры кнопки продолжить
GLuint more; ///<Переменная для текстуры больше тумана
GLuint lesss;///<Переменная для текстуры меньше тумана

/**
    \brief Загрузка текстур

    Эта функция отвечает за загрузку текстур с помощью библиотеки SOIL без учета прозрачного фона
*/
void load_textures(const char* image, GLuint* texturesy) //функция, загружающая текстуры
{
    unsigned char* top = SOIL_load_image(image, &W, &H, 0, SOIL_LOAD_RGB); // загружаем текстуру в soil
    glGenTextures(1, texturesy); // говорим, что начинаем работать с переменной Dirt, чтобы дальше записать в нее текстуру soil
    glBindTexture(GL_TEXTURE_2D, *texturesy); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, top); // загружаем текстуру soil в перменную dirt
    SOIL_free_image_data(top); // освобождаем текстуру из soil
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

/**
    \brief Загрузка текстур

    Эта функция отвечает за загрузку текстур с помощью библиотеки SOIL с учетом прозрачного фона
*/

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
/**
    \brief Сокращение текста

    Эта функция сделана для удобства восприятия функции main
*/
void textures_in_main() {
    load_textures_smooth("textures_game/floor1.jpg", &floor1, 0);//текстура пола психушки
    load_textures_smooth("textures_game/wall1.jpg", &wall, 0);//текстура стен психушки
    load_textures_smooth("textures_game/floor.png", &floor2, 0);//текстура пола замка
    load_textures_smooth("textures_game/wall.png", &wall2, 0);//текстура стен замка
    load_textures_smooth("textures_game/screamer.png", &screamer, 0);//текстура скримера
    load_textures_smooth("textures_game/flashlight.png", &flash, 1);//текстура фонарика
    load_textures_smooth("textures_game/backg.png", &backg, 0);//текстура заднего фона меню
    load_textures_smooth("textures_game/exit.jpg", &exi, 0);//текстура кнопки
    load_textures_smooth("textures_game/continue.jpg", &cont, 0);//текстура кнопки
    load_textures_smooth("textures_game/MFog.jpg", &more, 0);//текстура кнопки
    load_textures_smooth("textures_game/LFog.jpg", &lesss, 0);//текстура кнопки
}