


void wallTextures() {
    unsigned char* top = SOIL_load_image("textures_game/stone-bricks.png", &W, &H, 0, SOIL_LOAD_RGB); // ��������� �������� � soil
    glGenTextures(1, &wall[0]); // �������, ��� �������� �������� � ���������� Dirt, ����� ������ �������� � ��� �������� soil
    glBindTexture(GL_TEXTURE_2D, wall[0]); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, top); // ��������� �������� soil � ��������� dirt
    SOIL_free_image_data(top); // ����������� �������� �� soil
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void screamerTextures() {
    unsigned char* top = SOIL_load_image("textures_game/screamer.png", &W, &H, 0, SOIL_LOAD_RGB); // ��������� �������� � soil
    glGenTextures(1, &screamer[0]); // �������, ��� �������� �������� � ���������� Dirt, ����� ������ �������� � ��� �������� soil
    glBindTexture(GL_TEXTURE_2D, screamer[0]); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, top); // ��������� �������� soil � ��������� dirt
    SOIL_free_image_data(top); // ����������� �������� �� soil
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}

void polTextures() {
    unsigned char* top = SOIL_load_image("textures_game/floor.png", &W, &H, 0, SOIL_LOAD_RGB); // ��������� �������� � soil
    glGenTextures(1, &pol[0]); // �������, ��� �������� �������� � ���������� Dirt, ����� ������ �������� � ��� �������� soil
    glBindTexture(GL_TEXTURE_2D, pol[0]); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, top); // ��������� �������� soil � ��������� dirt
    SOIL_free_image_data(top); // ����������� �������� �� soil
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}