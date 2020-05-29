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
}
/**
/brief �������, � ������� ����������� ��� �������� ������ �������
*/
void Labyrinth2()
{
		glBindTexture(GL_TEXTURE_2D, wall);
		for (int x = 0; x < quantity_cubes_x; x++)
			for (int z = 0; z < quantity_cubes_z; z++) {
				if (!cubes1[x][z]) continue;
				glTranslatef(x, 0, z);
				draw_wall_new1(x, z);
				glTranslatef(-x, 0, -z);
			}
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
	floor();//��������� ����
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
	ex.update();
	back.update();
	gluLookAt(man.PlayerX, man.PlayerY + man.h / 2, man.PlayerZ,
		man.PlayerX + lx, man.PlayerY + ly + man.h / 2, man.PlayerZ + lz,
		0.0f, 1.0f, 0.0f);//���������� �������
//=================================������ ��������� �����===================================================================================
	floor();//��������� ����
	fogg();//��������� ������
	glBindTexture(GL_TEXTURE_2D, wall);
	for (int x = 0; x < quantity_cubes_x; x++)
		for (int z = 0; z < quantity_cubes_z; z++) {
			if (!cubes[x][z]) continue;
			glTranslatef(x, 0, z);
			draw_wall_new(x, z);
			glTranslatef(-x, 0, -z);

		}
	man.update(0);
}

