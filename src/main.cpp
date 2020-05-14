#include "glut.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <ctime>
#include <SOIL.h> // Библиотека для тектур
#include "alut.h"
#include "al.h"
#include "alc.h"
#pragma comment (lib,"SOIL.lib")
#pragma comment (lib,"alut.lib")
#pragma comment (lib,"glut.lib")

int width = 1600; ///< Высота окна
int height = 800; ///< Ширина окна
int H = height;///<Высота
int W = width;///<Ширина
float angle = 0; ///< Угол поворота
const int quantity_cubes_z = 20;///< Количество невидимых кубов по z
const int quantity_cubes_x = 20;///<Количество невидимых кубов по x
float lz = 1.0f;///<Координаты вектора, определяющее, куда смотрит камера
float lx = 0.0f;///<Координаты вектора, определяющее, куда смотрит камера
float ly = 0.0f;///<Координаты вектора, определяющее, куда смотрит камера
float angleY = 0;
float move_front = 0;
float move_side = 0;
time_t oldtime = 1;
time_t newtime = 1;

#include "textures.hpp"
#include "Labyrinth.hpp"
#include "Player.hpp"

/**
/brief Функция, отвечающая за изменения параметров при изменении размера окна

Данная функция задает перспектику, вызывается при первом запуске проги и при изменении окна проги
*/

void Reshape(int w, int h)
{
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(60, ratio, 0.1f, 10.0f); //задаем перспективную проекцию
	//(60 -угол обзора) (ratio- соотношение сторон) (0.1f- минимальное видимое расстояние в float) ( 360.0f- максимальная дальность видимости)
	glMatrixMode(GL_MODELVIEW);
}



/**
	\brief Главная функция программы

	Циклично вызывается. 1 вызов- 1 кадр. обновляет все, что находится в мире- положение игрока, его угол поворота. так же
	обновляет каждым разом мир - рисует его
*/

void Draw() {
	double times;
	float PlayerX = 0;
	float PlayerZ = 0;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим цвет и глубину
	glClearColor(0, 0, 0, 0); // задаем цвет фона в режиме RGB
	glPushMatrix(); // сохраняем систему координат
	if (angle > 360)//если обзор больше 360, то обнуляется
		angle = 0;
	flashlight();
	//boo();//возможно скример(картинка перед нами, нужно привязать время?)
	gluLookAt(man.PlayerX, man.PlayerY + man.h / 2, man.PlayerZ,
		man.PlayerX + lx, man.PlayerY + ly + man.h / 2, man.PlayerZ + lz,
		0.0f, 1.0f, 0.0f);//управление камерой
//=================================начало основного цикла===================================================================================
	newtime = clock();
	times = newtime - oldtime;
	oldtime = clock();
	//std::cout << 1000 / times << std::endl;
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
	man.update(times);
	//=================================конец основного цикла===================================================================================
	glPopMatrix(); // загружаем систему кординат
	glutPostRedisplay(); // Обновляем картинку в окне
	glFinish(); // заканчиваем рисование
}

#include "Mouse_and_keyboard.hpp"

/**
	\brief Точка входа в программу

	Устанавливает все настройки библиотеки GLUT, а так же заполняет массив , по которому будет в дальнейшем строиться мир
*/


int main()
{
	//===========================INITIALIZATION===========================================
	glutInitWindowSize(width, height); // инициализируем окно с заданной высотой и шириной
	glutInitDisplayMode(GLUT_RGB); // говорим, что режим цвета в окне будет RGB
	glutCreateWindow("horror game"); // созадем окно с названием horror game
	glEnable(GL_DEPTH_TEST); // включаем режим глубины. это нужно для того, чтобы объекты правильно отображались друг за другом
	glEnable(GL_TEXTURE_2D);// тестуры
	glutDisplayFunc(Draw); // пишем название функции, в которой будем рисовать
	glutReshapeFunc(Reshape); // пишем название функции, которая будет обрабатывать изменение размера окна
	glutKeyboardFunc(keyboard); // пишем название функции, где мы будем смотреть, какие клавиши нажаты на клаве
	glutKeyboardUpFunc(keyboard_up);//функция для отжатия клавиш
	glutPassiveMotionFunc(mouseMove);//когда мышка дыигается
	glutMotionFunc(mouseMove); //когда двигаешь при нажатии
	textures_in_main();//сокращение для текстур, вся суть в textures.hpp
	glutSetCursor(GLUT_CURSOR_NONE);//убирает курсор с экрана
	glutMainLoop(); // говорим, что запускаем непрерывный цикл рисования. с этого момента циклично будет проигрываться функция draw

}