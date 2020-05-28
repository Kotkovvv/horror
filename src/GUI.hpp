class GUI_touch1 {
    int pix = 100;
    float X1 = 0, Y1 = 0;/* .: */ // ��� �������� 
    float x1 = 0, y1 = 0;/* :. */ // ��� ��������������
    float X2 = 0, Y2 = 0;/* :' */ // ��� ��������
    float x2 = 0, y2 = 0;/* ': */ // ��� ��������������
    GLuint* tex; // ��������� �� ��������
    bool light = 0; // ��������� ��������� ������
    bool click = 0; // ��������� ������
public:
    /*
    GLuint* tex - ��������� �� ��������,
    int pix- ������ ��������
    int X - x ���������� ������� ������� ���� ������������� ����� ��������
    int Y - y ���������� ������� ������� ���� ������������� ����� ��������
    float x1, float y1 - ���������� ������� �������� ���� ��������������, ������� ����� ����������
    float x2, float y2 - ���������� ������ ������� ���� ��������������, ������� ����� ����������
    */
    GUI_touch1(GLuint* tex, int pix, float X, float Y, float x1, float y1, float x2, float y2) {
        X2 = X / (width / 2);
        Y2 = Y / (height / 2);


        this->x1 = x1; this->x2 = x2;
        this->y1 = y1; this->y2 = y2;

        this->tex = tex;
        this->pix = pix;
    }
    /**
        /brief ������� ��������� ����

        ���������� � ��������, ��� �������������� �����. � ����������� �� �������(������� ������� ��� ������� �������� ����)
        �� �������� ������ �����. ���� �� �� � ��� ������� �������� ������� ������ �������, �� ��� ���������� 1 �
        ������ �� ��� ����� ����������, ��� ������.

        x - ���������� ���� �� ��� x
        y - ���������� ���� �� ��� y
        click_status - ��������, ������ �� ������ ����

    */
    bool mouse(float x, float y, int click_status) {
        // �������� ���������� ����. ���������� �� ���������� ������������ ��� ������ � ������ � ��������,
        // �� ���������� ������ � ������ ��������� - � ��� � ��������
        x = x / (width/2); 
        y = y / (height/2);
        x = x - 1;
        y = -(y - 1);
        x =x/4.9;
        y = y/8.8;
        std::cout << x << " " << y << std::endl;
        // �������, �������� �� ����� � ������
        if (x > x2 && x < x1 && y > y2 && y < y1) {
            light = 1; // �������� ���������
            click = click_status; // ��������, ������ �� �����
            return click_status; // ���������� ����. ���� �� ������, �� ����� �������� ��� ������� ���, ��� �� �� ��������
            // � ������ ��� �������� ���������. ��� ������� ����� 1 - ���-�� �������� ��� ������
        }
        else {
            light = 0; // �� ������������
            return 0;
        }
    }
    /**
        /brief ������ ������. ��� ������� ���������� �� glulookat � � �������, ���������� �� ���������.
    */
    void update() {
        glBindTexture(GL_TEXTURE_2D, *tex);
        glBegin(GL_QUADS);
        if (!light) {
            glTexCoord2d(X2, Y1); glVertex3f(x1, y1, -0.2);
            glTexCoord2d(X2, Y2); glVertex3f(x1, y2, -0.2);
            glTexCoord2d(X1, Y2); glVertex3f(x2, y2, -0.2);
            glTexCoord2d(X1, Y1); glVertex3f(x2, y1, -0.2);
        }
        else {
            glTexCoord2d(X2, Y1 + Y2); glVertex3f(x1, y1, -0.2);
            glTexCoord2d(X2, Y2 + Y2); glVertex3f(x1, y2, -0.2);
            glTexCoord2d(X1, Y2 + Y2); glVertex3f(x2, y2, -0.2);
            glTexCoord2d(X1, Y1 + Y2); glVertex3f(x2, y1, -0.2);
        }
        glEnd();
    }
};
class GUI_background1 {
    float pix = 500.0f; // ����������� �������� �� ������ � ������ � ��������
    float X1 = 0.0f, Y1 = 0.0f;  /* .: */ // ��� �������� 
    float x1 = 0.0f, y1 = 0.0f;  /* :. */ // ��� ��������������
    float X2 = 0.0f, Y2 = 0.0f;  /* :' */ // ��� ��������
    float x2 = 0.0f, y2 = 0.0f;  /* ': */ // ��� ��������������
    GLuint* tex;
    bool key = 1; // ��������� ��������- ��� ���� ��� ���
public:
    /**
        /brief ����������� ������, ��� �� ����� ������ ��� ������� ��� �������� � ��������������

        GLuint* tex - ��������� �� ��������,
        int pix- ������ ��������
        int X2 - x ���������� ������� ������� ���� ������������� ����� ��������
        int Y2 - y ���������� ������� ������� ���� ������������� ����� ��������
        float x1, float y1 - ���������� ������� �������� ���� ��������������, ������� ����� ����������
        float x2, float y2 - ���������� ������ ������� ���� ��������������, ������� ����� ����������
    */
    GUI_background1(GLuint* tex, int pix, float X2, float Y2, float x1, float y1, float x2, float y2) {
        this->X2 = X2 / pix;
        this->Y2 = Y2 / pix;

        this->x1 = (x1 * 0.2); this->x2 = (x2 * 0.2);
        this->y1 = (y1 * 0.2); this->y2 = (y2 * 0.2);
        this->tex = tex;
        this->pix = pix;
    }
    /**
        /brief ����������� ������, ��� �� ����� ������ ��� ������� ��� �������������� ��� ��������

        float x1, float y1 - ���������� ������� �������� ���� ��������������, ������� ����� ����������
        float x2, float y2 - ���������� ������ ������� ���� ��������������, ������� ����� ����������
    */
    GUI_background1(float x2, float y2, float x1, float y1) {
        this->x1 = (x1 * 0.2); this->x2 = (x2 * 0.2);
        this->y1 = (y1 * 0.2); this->y2 = (y2 * 0.2);
        key = 0; // ���� �������� ���� �����������, �� �������, ��� �� ���������� �������� ��� ������� �������
    }
    void update() {
        if (key)glBindTexture(GL_TEXTURE_2D, *tex);  //  ���� ��� ��������- �� ������ ��
        else glBindTexture(GL_TEXTURE_2D, GLU_NONE); // � ������ ������.�������. ����

        glBegin(GL_QUADS);
        glTexCoord2d(X2, Y1); glVertex3f(x1, y1, -0.2);
        glTexCoord2d(X2, Y2); glVertex3f(x1, y2, -0.2);
        glTexCoord2d(X1, Y2); glVertex3f(x2, y2, -0.2);
        glTexCoord2d(X1, Y1); glVertex3f(x2, y1, -0.2);
        glEnd();

    }
};
//�� ��� x 1,04
GUI_background1 back(&backg, 100, 100, 100, 1.03, 1, -1.03, -1);///<����� ������� ���� ����
GUI_background1 flashl(&flash, 100, -100, 100, 1.05, -0.1, 0.51, -1);///<����� ��������� ��������
GUI_touch1 butt(&but, 100, 100, 50, 0.1, 0.1, -0.1, -0.1);///<����� ������
