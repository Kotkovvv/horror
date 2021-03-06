﻿float mouseXOld = 0;///< вспомогательные функции, которые позволяют двигать камеру, фиксирует старое положение камеры
float mouseYOld = 0;///< вспомогательные функции, которые позволяют двигать камеру, фиксирует старое положение камеры

/**
/brief Функция, отвечающая за связь с мышкой

Данная функция фиксирует иззменение положения компьютерной мыши и передает их программе

*/
void mouseMove(int x, int y)
{
	if (state_of_game == GAME) {
		if (mouseXOld != 0 || mouseYOld != 0) {
			angle -= mouseXOld * 0.001f;
			angleY -= mouseYOld * 0.001f;

			if (angleY > 3.14 / 2) angleY = 3.14 / 2;
			if (angleY < -3.14 / 2) angleY = -3.14 / 2;

			mouseXOld = 0; mouseYOld = 0;

			// обновляют направление камеры
			lx = float(-sin(angle));
			lz = float(cos(angle));
			ly = float(-tan(angleY));

		}
		else
		{

			mouseXOld = (width / 2) - x;
			mouseYOld = (height / 2) - y;
			glutWarpPointer((width / 2), (height / 2));
		}
	}
	else if (state_of_game == GAME_MENU) {
		ex.mouse(x, y, 0);
		con.mouse(x, y, 0);
		les.mouse(x, y, 0);
		mor.mouse(x, y, 0);
	}
}
/**
/brief Функция, отвечающая нажатие кнопок

Данная функция отвечает за фиксирование нажатия клавиш клавиатуры. Управление осуществляется с помощью нажатия нопок WASD

*/

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':
		move_front = 1;
		break;
	case 's':
	case 'S':
		move_front = -1;
		break;
	case 'a':
	case 'A':
		move_side = -1;
		break;
	case 'd':
	case 'D':
		move_side = 1;
		break;
	case 27:
		if (state_of_game == GAME)
		{
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);//
			state_of_game = GAME_MENU;
		}
		else
		{
			glutSetCursor(GLUT_CURSOR_NONE);//убирает курсор с экрана
			state_of_game = GAME;
		}
	}
}

/**
/brief Функция, отвечающая отжатие кнопок

Данная функция отвечает за фиксирование отжатия клавиш клавиатуры. Управление осуществляется с помощью нажатия нопок WASD

*/

void keyboard_up(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
	case 'W':
	case 's':
	case 'S':
		move_front = 0;
		break;
	case 'a':
	case 'A':
	case 'd':
	case 'D':
		move_side = 0;
		break;
	}
}

/**
/brief Функция, отвечающая нажатие ЛКМ

Данная функция отвечает за считывания нажатия на кнопки в меню
*/

void mouseButton(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state_of_game == GAME_MENU) {
				if (ex.mouse(x, y, 1)) {
					exit(0);
			}
				if (con.mouse(x, y, 1)) {
					glutSetCursor(GLUT_CURSOR_NONE);//убирает курсор с экрана
					state_of_game = GAME;
				}
				if (mor.mouse(x, y, 1)) {
					fog_change = fog_change +0.05f;
				}
				if (les.mouse(x, y, 1)) {
					fog_change = fog_change -0.05f;
				}
		}
	}
}