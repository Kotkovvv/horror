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
using namespace std;

int width = 1280; ///< Высота окна
int height = 720; ///< Ширина окна
int H = height;///<Высота
int W = width;///<Ширина
float angle = 0; ///< угол поворота камеры в плоскости XZ
const int quantity_cubes_z = 20;///< Количество невидимых кубов по z
const int quantity_cubes_x = 20;///<Количество невидимых кубов по x
float lz = 1.0f;///<Координаты вектора, определяющее, куда смотрит камера
float lx = 0.0f;///<Координаты вектора, определяющее, куда смотрит камера
float ly = 0.0f;///<Координаты вектора, определяющее, куда смотрит камера
float angleY = 0;///< угол поворота камеры по оси Y
float move_front = 0;///< ключ к изменению скорости вперед/назад
float move_side = 0;///< ключ к изменению скорости вбок
time_t oldtime = 1;
time_t newtime = 1;
int choice_of_labirynth = 0;///<в дальнейшем поможет с переходом из одной локации в другую
int state_of_game = 0;///<состояние игры в данный момент(игра/меню)
bool mLeft = 0; ///< состояние левой кнопки мыши
float fog_change = 0.7f;///<дальность прорисовки тумана
float sc_s;

enum labyrinth {
	NUM1,
	NUM2,
};

#include "textures.hpp"
#include "Labyrinth.hpp"
#include "Player.hpp"
#include "GUI.hpp"
#include "scene.hpp"

enum game_status {
	GAME,
	GAME_MENU,
};



/**
/brief Функция, отвечающая за изменения параметров при изменении размера окна

Данная функция задает перспектику, вызывается при первом запуске проги и при изменении окна проги
*/

void Reshape(int w, int h)
{
	float ratio = w * 1.0 / h;///< соотношение сторон
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(60, ratio, 0.1f, 20.0f); //задаем перспективную проекцию
	//(60 -угол обзора) (ratio- соотношение сторон) (0.1f- минимальное видимое расстояние в float) ( 360.0f- максимальная дальность видимости)
	glMatrixMode(GL_MODELVIEW);
}



/**
	\brief Главная функция программы

	Циклично вызывается. 1 вызов- 1 кадр. обновляет все, что находится в мире- положение игрока, его угол поворота. так же
	обновляет каждым разом мир - рисует его
*/

void Draw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим цвет и глубину
	glClearColor(0, 0, 0, 0); // задаем цвет фона в режиме RGB
	glPushMatrix(); // сохраняем систему координат
	switch (state_of_game) {
	case GAME:
	game();
	break;
	case GAME_MENU:
		game_menu();
		break;
	}
	//std::cout<< man.PlayerX<<" "<<
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
	glutPassiveMotionFunc(mouseMove);//функция, которая отслеживает мышку в НЕ нажатом состоянии
	glutMotionFunc(mouseMove); // функция, которая отслеживает мышку в нажатом состоянии
	glutMouseFunc(mouseButton); // Обрабатываем нажатие мыши
	textures_in_main();//сокращение для текстур, вся суть в textures.hpp
	glutMainLoop(); // говорим, что запускаем непрерывный цикл рисования. с этого момента циклично будет проигрываться функция draw

}