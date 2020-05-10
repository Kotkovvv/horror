GLuint wall;//���������� ��� �������� �����
GLuint screamer;//���������� ��� �������� ��������
GLuint floor1;//���������� ��� �������� ����
GLuint flash;//���������� ��� �������� ��������
void load_textures_blocks(const char* image, GLuint* texturesy) //�������, ����������� ��������
{
    unsigned char* top = SOIL_load_image(image, &W, &H, 0, SOIL_LOAD_RGB); // ��������� �������� � soil
    glGenTextures(1, texturesy); // �������, ��� �������� �������� � ���������� Dirt, ����� ������ �������� � ��� �������� soil
    glBindTexture(GL_TEXTURE_2D, *texturesy); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, top); // ��������� �������� soil � ��������� dirt
    SOIL_free_image_data(top); // ����������� �������� �� soil
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void load_textures(const char* image, GLuint* texturesy, bool type) {
    unsigned char* top = SOIL_load_image(image, &W, &H, 0, SOIL_LOAD_RGBA); // ��������� �������� � soil
    glGenTextures(1, texturesy); // �������, ��� �������� �������� � ���������� Dirt, ����� ������ �������� � ��� �������� soil
    glBindTexture(GL_TEXTURE_2D, *texturesy); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    if (type) {
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.8f);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, top); // ��������� �������� soil � ��������� dirt
    SOIL_free_image_data(top); // ����������� �������� �� soil
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void load_textures_smooth(const char* image, GLuint* texturesy, bool type) {
    unsigned char* top = SOIL_load_image(image, &W, &H, 0, SOIL_LOAD_RGBA); // ��������� �������� � soil
    glGenTextures(1, texturesy); // �������, ��� �������� �������� � ���������� Dirt, ����� ������ �������� � ��� �������� soil
    glBindTexture(GL_TEXTURE_2D, *texturesy); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (type) {
        glEnable(GL_ALPHA_TEST);
        glAlphaFunc(GL_GREATER, 0.8f);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, W, H, 0, GL_RGBA, GL_UNSIGNED_BYTE, top); // ��������� �������� soil � ��������� dirt
    SOIL_free_image_data(top); // ����������� �������� �� soil
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void textures_in_main() {
    load_textures_smooth("textures_game/floor1.jpg", &floor1, 0);//�������� ����
    load_textures_smooth("textures_game/screamer.png", &screamer, 0);//�������� ��������
    load_textures_smooth("textures_game/wall1.jpg", &wall, 0);//�������� ����
    load_textures_smooth("textures_game/flashlight.png", &flash, 0);//�������� ��������
}