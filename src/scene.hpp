/**
/brief �������, � ������� ����������� ��� �������� ������ �������
*/
void Labyrinth1()
{

		glBindTexture(GL_TEXTURE_2D, wall);
		for (int x = 0; x < quantity_cubes_x; x++)
			for (int z = 0; z < quantity_cubes_z; z++) {
				if (!cubes[x][z]) continue;
				glTranslatef(x, 0, z);
				draw_wall_new(x, z);
				glTranslatef(-x, 0, -z);

			}
		if (change.update())
			choice_of_labirynth = NUM2;
		if (scream.update())
			boo();
		glBindTexture(GL_TEXTURE_2D, floor1);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);  glVertex3f(1, -1, 19);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(19, -1, 19);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(19, -1, 1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, 1);
		glEnd();
}
/**
/brief �������, � ������� ����������� ��� �������� ������ �������
*/
void Labyrinth2()
{
		glBindTexture(GL_TEXTURE_2D, wall2);
		for (int x = 0; x < quantity_cubes_x; x++)
			for (int z = 0; z < quantity_cubes_z; z++) {
				if (!cubes1[x][z]) continue;
				glTranslatef(x, 0, z);
				draw_wall_new1(x, z);
				glTranslatef(-x, 0, -z);
			}
		glBindTexture(GL_TEXTURE_2D, floor2);
		glBegin(GL_QUADS);
		glTexCoord2f(1.0f, 1.0f);  glVertex3f(1, -1, 19);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(19, -1, 19);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(19, -1, 1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, 1);
		glEnd();
}


/**
/brief �������, � ������� ����������� ��������� ��� ����
*/
void game() {
	double times;
	//back.update();
	flashl.update();
	//boo();//�������� �������(�������� ����� ����, ����� ��������� �����?)
	gluLookAt(man.PlayerX, man.PlayerY + man.h / 2, man.PlayerZ,
		man.PlayerX + lx, man.PlayerY + ly + man.h / 2, man.PlayerZ + lz,
		0.0f, 1.0f, 0.0f);//���������� �������
	
//=================================������ ��������� �����===================================================================================
	newtime = clock();
	times = newtime - oldtime;
	oldtime = clock();
	fogg();//��������� ������
	switch (choice_of_labirynth) {
	case NUM1:
		Labyrinth1();
		break;
	case NUM2:
		Labyrinth2();
		break;
	}
	man.update(times);
}

/**
/brief �������, � ������� ����������� ��������� � ����
*/

void game_menu() {
	con.update();
	ex.update();
	mor.update();
	les.update();
	back.update();
	gluLookAt(man.PlayerX, man.PlayerY + man.h / 2, man.PlayerZ,
		man.PlayerX + lx, man.PlayerY + ly + man.h / 2, man.PlayerZ + lz,
		0.0f, 1.0f, 0.0f);//���������� �������
//=================================������ ��������� �����===================================================================================
	fogg();//��������� ������
	man.update(0);
}

