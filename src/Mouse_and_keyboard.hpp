float mouseXOld = 0;///< вспомогательные функции, которые позволяют двигать камеру, фиксирует старое положение камеры
float mouseYOld = 0;///< вспомогательные функции, которые позволяют двигать камеру, фиксирует старое положение камеры
using namespace std;

/**
/brief Функция, отвечающая за связь с мышкой

Данная функция фиксирует иззменение положения компьютерной мыши и передает их программе

*/
void mouseMove(int x, int y)
{
	if (mouseXOld != 0 || mouseYOld != 0) {
		angle -= mouseXOld * 0.001f;
		angleY -= mouseYOld * 0.001f;

		if (angleY > 3.14 / 2) angleY = 3.14 / 2;
		if (angleY < -3.14 / 2) angleY = -3.14 / 2;

		mouseXOld = 0; mouseYOld = 0;

		// update camera's direction
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
/**
/brief Функция, отвечающая нажатие кнопок

Данная функция отвечает за фиксирование нажатия клавиш клавиатуры. Управление осуществляется с помощью нажатия нопок WASD

*/

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // если key = 27(escape), то выходим из программы
		exit(0);
		break;
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
