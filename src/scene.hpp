/**
/brief Функция, в которой описывается как строится первая локация
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
		if (qw.update())
			choice_of_labirynth = NUM2;
}
/**
/brief Функция, в которой описывается как строится вторая локация
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
/brief Функция, в которой описывается поведение вне меню
*/
void game() {
	double times;
	//back.update();
	flashl.update();
	//boo();//возможно скример(картинка перед нами, нужно привязать время?)
	gluLookAt(man.PlayerX, man.PlayerY + man.h / 2, man.PlayerZ,
		man.PlayerX + lx, man.PlayerY + ly + man.h / 2, man.PlayerZ + lz,
		0.0f, 1.0f, 0.0f);//управление камерой
	
//=================================начало основного цикла===================================================================================
	newtime = clock();
	times = newtime - oldtime;
	oldtime = clock();
	floor();//рисование пола
	fogg();//рисование тумана
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
/brief Функция, в которой описывается поведение в меню
*/

void game_menu() {
	butt.update();
	back.update();
	gluLookAt(man.PlayerX, man.PlayerY + man.h / 2, man.PlayerZ,
		man.PlayerX + lx, man.PlayerY + ly + man.h / 2, man.PlayerZ + lz,
		0.0f, 1.0f, 0.0f);//управление камерой
//=================================начало основного цикла===================================================================================
	floor();//рисование пола
	fogg();//рисование тумана
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

