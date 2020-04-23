#include <glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <ctime>
#include <SOIL.h> // библиотека для тектур. пока не нужна
#pragma comment (lib,"SOIL.lib")



int width = 1600; // высота окна
int height = 800; // ширина окна
int W = width;
int H = height;
float angle = 0; // угол поворота
int cube_size = 1;
const int quantity_cubes_x = 20;
const int quantity_cubes_z = 20;
float lx = 0.0f;
float lz = 1.0f;
float speedX = 0;
float speedZ = 0;
float speedX_side = 0;
float speedZ_side = 0;
float speedX_front = 0;
float speedZ_front = 0;
float move_front = 0;
float move_side = 0;
float angleY = 0;
float mouseXOld = 0;// вспомогательные фукнции, которые ппозволяют двигать камеру, фиксирует старое положение камеры
float mouseYOld = 0;// вспомогательные фукнции, которые ппозволяют двигать камеру, фиксирует старое положение камеры
float ly = 0;//координаты вектора, определяющее, куда смотрит камера

float PlayerX = 0;
float PlayerZ = 0;
GLuint wall;
GLuint screamer;
GLuint pol;

int cubes[quantity_cubes_x][quantity_cubes_z] = { {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 },//сюда z
												  {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1 },
												  {1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
												  {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1},
												  {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1},
												  {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1},
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
									  /*сюда x*/  {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0 }, }; //дает невидимые стены


#include "src\textures.hpp"

class Player {
public:
	float PlayerX, PlayerY, PlayerZ;
	float dx, dz;
	float dSideX, dSideZ;
	float dFrontX, dFrontZ;
	float w, h, d;
	bool onGround;
	float speed;
	float View; // угол обзора

	Player(float x0, float y0, float z0) {
		PlayerX = x0+1.5; PlayerY = y0; PlayerZ = z0+1.5;
		dx = 0;  dz = 0;
		dSideX = 0; dSideZ = 0;
		dFrontX = 0; dFrontZ = 0;
		w = 0.5f; h = 1.9f; d = 0.5f; speed = 0.1;
		onGround = false;
		View = 90; // угол обзора
	}
	bool check(int x,  int z) {
		if ((x < 0) or (x > quantity_cubes_x) or
			(z < 0) or (z > quantity_cubes_z)) return false;
		return cubes[x][z];

	}
	void update(float time) {




		if (move_front) {
			dFrontX = lx * speed * move_front * time / 50;
			dFrontZ = lz * speed * move_front * time / 50;
		}
		if (move_side) {
			dSideX = -lz * speed * move_side * time / 50;
			dSideZ = lx * speed * move_side * time / 50;
		}



		dx = dSideX + dFrontX;
		PlayerX += dx;
		collision(dx, 0);
		dz = dSideZ + dFrontZ;
		PlayerZ += dz;
		collision(0, dz);


		dx = dz = dSideX = dSideZ = dFrontX = dFrontZ = 0;
	}

	void collision(float Dx, float Dz) {
		for (int X = (PlayerX - w) / cube_size; X < (PlayerX + w) / cube_size; X++)
				for (int Z = (PlayerZ - d) / cube_size; Z < (PlayerZ + d) / cube_size; Z++)
					if (check(X, Z))
					{
						if (Dx > 0) PlayerX = X * cube_size - w;
						if (Dx < 0) PlayerX = X * cube_size + cube_size + w;

						if (Dz > 0) PlayerZ = Z * cube_size - d;
						if (Dz < 0) PlayerZ = Z * cube_size + cube_size + d;

					}
	}
};
Player man(0, 0, 0);

void keyboard_special(int key, int x, int y) 
{
	if (key == GLUT_KEY_LEFT)
		angle += 0.1;
	if (key == GLUT_KEY_RIGHT)
		angle -= 0.1;

}

void Reshape(int w, int h)
{
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(60, ratio, 0.1f, 180.0f); //задаем перспективную проекцию
	//(60 -угол обзора) (ratio- соотношщение сторон) (0.1f- минимальное видимое расстояние в float) ( 360.0f- максимальная дальность видимости)
	glMatrixMode(GL_MODELVIEW);
}

//void move()
//{
//	if (move_front)
//	{
//		speedX_front = lx * move_front * 0.01;
//		speedZ_front = lz * move_front * 0.01;
//	}
//	else {
//		speedX_front = 0;
//		speedZ_front = 0;
//	}
//	if (move_side)
//	{
//		speedX_side = -lz * move_side * 0.01;
//		speedZ_side = lx * move_side * 0.01;
//	}
//	else {
//		speedX_side = 0;
//		speedZ_side = 0;
//	}
//	speedX = speedX_side + speedX_front;
//	speedZ = speedZ_side + speedZ_front;
//
//	PlayerX += speedX;
//	PlayerZ += speedZ;
//}
void mouseMove(int x, int y) 
{
	if (mouseXOld != 0 or mouseYOld != 0) {
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

	//glutPostRedisplay();

}


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

void keyboard_up(unsigned char key, int x, int y)
{

	switch (key) 
	{
	case 'w':
	case 'W':
	case 's':
	case 'S':
		move_front = 0;
		//speedX = 0;

		break;
	case 'a':
	case 'A':
	case 'd':
	case 'D':
		move_side = 0;
		//speedZ = 0;

		break;
	}
}

void cube() 
{ //может не понадобиться
	glColor3f(0.5, 1.0, 1.0); // задаем цвет грани
	///задняя
	glBegin(GL_QUADS); // говорим, что начинаем рисовать куб
	glVertex3f(1, -1, 1); // его координаты
	glVertex3f(-1, -1, 1);// его координаты
	glVertex3f(-1, 1, 1);// его координаты
	glVertex3f(1, 1, 1);// его координаты
	glEnd(); // говорим, что заканчиваем рисовать


	//передняя
	glColor3f(1.0, 0.5, 1.0);// задаем цвет грани
	glBegin(GL_QUADS);// говорим, что начинаем рисовать куб
	glVertex3f(-1, -1, -1);// его координаты
	glVertex3f(1, -1, -1);// его координаты
	glVertex3f(1, 1, -1);// его координаты
	glVertex3f(-1, 1, -1);// его координаты
	glEnd(); // говорим, что заканчиваем рисовать


	//ПРАВАЯ
	glColor3f(1.0, 1.0, 0.5);
	glBegin(GL_QUADS);
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);
	glEnd();


	//ЛЕВАЯ
	glColor3f(0.5, 0.5, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, 1);
	glEnd();


	//НИЖНЯЯ
	glColor3f(1.0, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex3f(-1, -1, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(1, -1, -1);
	glVertex3f(-1, -1, -1);
	glEnd();


	//ВЕРХНЯЯ
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);
	glEnd();
}

void labirynth1()
{

	//пол комнаты
	glBindTexture(GL_TEXTURE_2D, pol);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(1, -1, 19);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(19, -1, 19);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(19, -1, 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, 1);
	glEnd();


	//задняя стена
	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);// говорим, что начинаем рисовать куб
	glTexCoord2f(1.0f, 1.0f); glVertex3f(19, -1, 1);// его координаты
	glTexCoord2f(0.0f, 1.0f);  glVertex3f(19, 1, 1);// его координаты
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1, 1, 1);// его координаты
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, 1);// его координаты
	glEnd(); // говорим, что заканчиваем рисовать

	//правая стена
	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1, -1, 19);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1, -1, 1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1, 1, 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, 1, 19);
	glEnd();

	//левая стенка
	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(19, -1, 1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(19, -1, 19);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(19, 1, 19);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(19, 1, 1);
	glEnd();

	//передняя стена
	glBindTexture(GL_TEXTURE_2D, wall);
	glBegin(GL_QUADS); // говорим, что начинаем рисовать куб
	glTexCoord2f(1.0f, 1.0f); glVertex3f(19, -1, 19); // его координаты
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1, -1, 19);// его координаты
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1, 1, 19);// его координаты
	glTexCoord2f(1.0f, 0.0f); glVertex3f(19, 1, 19);// его координаты
	glEnd(); // говорим, что заканчиваем рисовать



	



}

void boo()
{
	glBindTexture(GL_TEXTURE_2D, screamer);
	glBegin(GL_QUADS);// говорим, что начинаем рисовать скример
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5, -0.5, -1);// его координаты
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, -0.5, -1);// его координаты
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5, 0.5, -1);// его координаты
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.5, -1);// его координаты
	glEnd(); // говорим, что заканчиваем рисовать
}


void Draw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим цвет и глубину
	glClearColor(0, 0, 0, 0); // задаем цвет фона в режиме RGB
	glPushMatrix(); // сохраняем систему координат
	if (angle > 360)
		angle = 0;
	//move();
	boo();//возможно скример(картинка перед нами, нужно привязать время?)

	gluLookAt(man.PlayerX, man.PlayerY + man.h / 2 - 1.2, man.PlayerZ,
		      man.PlayerX + lx, man.PlayerY + ly + man.h / 2 , man.PlayerZ + lz,
		      0.0f, 1.0f, 0.0f);
	//=================================начало основного цикла===================================================================================


	labirynth1();


	man.update(1);
	//=================================конец основного цикла===================================================================================
	glPopMatrix(); // загружаем систему кординат
	glutPostRedisplay(); // Обновляем картинку в окне
	glFinish(); // заканчиваем рисование
}

void load_textures_blocks(const char* image, GLuint* texturesy) 
{
	unsigned char* top = SOIL_load_image(image, &W, &H, 0, SOIL_LOAD_RGB); // загружаем текстуру в soil
	glGenTextures(1, texturesy); // говорим, что начинаем работать с переменной Dirt, чтобы дальше записать в нее текстуру soil
	glBindTexture(GL_TEXTURE_2D, *texturesy); // All upcoming GL_TEXTURE_2D operations now have effect on this texture object

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, W, H, 0, GL_RGB, GL_UNSIGNED_BYTE, top); // загружаем текстуру soil в перменную dirt
	SOIL_free_image_data(top); // освобождаем текстуру из soil
	glBindTexture(GL_TEXTURE_2D, 0); // Unbind texture when done, so we won't accidentily mess up our texture.
}



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
	glutSpecialFunc(keyboard_special);
	glutKeyboardUpFunc(keyboard_up);
	glutPassiveMotionFunc(mouseMove);//когда мышка дыигается
	glutMotionFunc(mouseMove); //когда двигаешь при нажатии
	load_textures_smooth("textures_game/floor.png", &pol,0);//текстура пола
	load_textures_smooth("textures_game/screamer.png", &screamer,0);//текстура скримера
	load_textures_smooth("textures_game/stone-bricks.png", &wall,0);//текстура стен


	/*for (int x = 0; x < 7; x++)
			for (int z = 0; z < 7; z++) {
				if (x == 0 or x == 6 or z == 0 or z == 6)
					cubes[x][z] = 1;
			}*/
	glutMainLoop(); // говорим, что запускаем непрерывный цикл рисования. с этого момента циклично будет проигрываться функция draw
}