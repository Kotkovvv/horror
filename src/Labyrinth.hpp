int cubes[quantity_cubes_x][quantity_cubes_z] = { {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},//сюда z
												  {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
												  {1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
	/*		|	*/								  {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1},
	/*перед	|	*/								  {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1},
	/*		V	*/								  {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1},
												  {1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1},
												  {1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1},
												  {1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1},
												  {1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1},
												  {1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1},
												  {1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
												  {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1},
												  {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1},
												  {1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1},
												  {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1},
												  {1, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
												  {1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1},
												  {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	/*сюда x*/									  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0 }, }; //дает невидимые стены

	/**
		\brief определяет поведение при столкновении с колизией
		эта функция принимает на вход скорости по осям игрока, и при столкновении с клизией определяет, как должен вести себя игрок
	*/

void draw_wall_new(int x, int z) {//определяет, адо ли рисовать стены(если несколько накладываются, то не рисуется ни одна)
	glBegin(GL_QUADS);
	if (cubes[x][z] != cubes[x - 1][z] && x != 0) {
		// задняя стена
		glColor3f(0.5, 0.5, 0.5);
		glTexCoord2f(1.0f, 1.0f);  glVertex3f(0, -1, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 1, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 1, 1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0, -1, 1);
	}
	// правая
	if (cubes[x][z] != cubes[x][z + 1] && z != 20) {
		glColor3f(0.5, 0.5, 0.5);
		glTexCoord2f(1.0f, 1.0f);  glVertex3f(0, -1, 1);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1, -1, 1);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1, 1, 1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 1, 1);
	}
	// передняя
	if (cubes[x][z] != cubes[x + 1][z] && x != 20) {
		glColor3f(0.6, 0.6, 0.6);
		glTexCoord2f(1.0f, 1.0f);  glVertex3f(1, -1, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1, 1, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1, 1, 1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, 1);
	}
	// задняя
	if (cubes[x][z] != cubes[x][z - 1] && z != 0) {
		glColor3f(0.5, 0.5, 0.5);
		glTexCoord2f(1.0f, 1.0f);  glVertex3f(0, -1, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1, -1, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1, 1, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 1, 0);
	}
	glEnd();
}

void floor() {
	glBindTexture(GL_TEXTURE_2D, floor1);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(1, -1, 19);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(19, -1, 19);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(19, -1, 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, 1);
	glEnd();
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);      // Будем очищать экран, заполняя его цветом тумана. ( Изменено )

	
}

void fogg() {
	//GLuint filter;                          // Используемый фильтр для текстур
	GLuint fogMode[] = { GL_EXP, GL_EXP2, GL_LINEAR }; // Хранит три типа тумана
	GLuint fogfilter = 0;                    // Тип используемого тумана
	GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f }; // Цвет тумана
	glEnable(GL_FOG);                       // Включает туман (GL_FOG)
	glFogi(GL_FOG_MODE, fogMode[fogfilter]);// Выбираем тип тумана
	glFogfv(GL_FOG_COLOR, fogColor);        // Устанавливаем цвет тумана
	glFogf(GL_FOG_DENSITY, 0.7f);          // Насколько густым будет туман
	glHint(GL_FOG_HINT, GL_DONT_CARE);      // Вспомогательная установка тумана
	glFogf(GL_FOG_START, 1.0f);             // Глубина, с которой начинается туман
	glFogf(GL_FOG_END, 5.0f);               // Глубина, где туман заканчивается.
}

void flashlight()
{
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, flash);
	glRotatef(0, 0, 0, 1);
	glBegin(GL_QUADS);// говорим, что начинаем рисовать фонари
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.105, -0.125, -0.15);// его координаты
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.195, -0.125, -0.15);// его координаты
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.195, -0.035, -0.15);// его координаты
	glTexCoord2f(1.0f, 0.0f); glVertex3f(0.105, -0.035, -0.15);// его координаты
	glEnd(); // говорим, что заканчиваем рисовать
	glPopMatrix();
}

void boo()
{
	glBindTexture(GL_TEXTURE_2D, screamer);
	glBegin(GL_QUADS);// говорим, что начинаем рисовать скример
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.05, -0.05, -0.1);// его координаты
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.05, -0.05, -0.1);// его координаты
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.05, 0.05, -0.1);// его координаты
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.05, 0.05, -0.1);// его координаты
	glEnd(); // говорим, что заканчиваем рисовать
}
