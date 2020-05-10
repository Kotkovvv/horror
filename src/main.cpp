#include "glut.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <ctime>
#include <SOIL.h> // библиотека для тектур
#pragma comment (lib,"SOIL.lib")




int width = 1600; // высота окна
int height = 800; // ширина окна
int H = height;
int W = width;
int cube_size = 1;
float angle = 0; // угол поворота
const int quantity_cubes_z = 20;// количество невидимых кубов по z
const int quantity_cubes_x = 20;//количество невидимых кубов по x
float lz = 1.0f;
float lx = 0.0f;
float speedX = 0;
float speedZ = 0;
float speedX_side = 0;
float speedZ_side = 0;
float speedZ_front = 0;
float speedX_front = 0;
float move_front = 0;
float move_side = 0;
float angleY = 0;
float mouseXOld = 0;// вспомогательные фукнции, которые ппозволяют двигать камеру, фиксирует старое положение камеры
float mouseYOld = 0;// вспомогательные фукнции, которые ппозволяют двигать камеру, фиксирует старое положение камеры
float ly = 0;//координаты вектора, определяющее, куда смотрит камера

float PlayerX = 0;
float PlayerZ = 0;
GLuint wall;//переменная для текстуры стены
GLuint screamer;//переменная для текстуры скримера
GLuint floor1;//переменная для текстуры пола
GLuint flash;//переменная для текстуры фонарика
GLuint texture[3];
bool   gp;                              // G Нажата? ( Новое )

time_t oldtime = 1;
time_t newtime = 1;




#include "textures.hpp"
#include "Labyrinth.hpp"
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
		PlayerX = x0; PlayerY = y0; PlayerZ = z0;
		dx = 0;  dz = 0;
		dSideX = 0; dSideZ = 0;
		dFrontX = 0; dFrontZ = 0;
		w = 0.2f; h = 1.9f; d = 0.2f; speed = 0.1;
		onGround = false;
		View = 90; // угол обзора
	}
	bool check(int x,  int z) {
		if ((x < 0) || (x > quantity_cubes_x) ||
			(z < 0) || (z > quantity_cubes_z)) return false;
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
		for (int X = (PlayerX - w); X < (PlayerX + w) ; X++)
		for (int Z = (PlayerZ - d); Z < (PlayerZ + d) ; Z++)
					if (check(X, Z))
					{
						if (Dx > 0) PlayerX = X * cube_size - w - 0.001;
						if (Dx < 0) PlayerX = X * cube_size + cube_size + w + 0.001;

						if (Dz > 0) PlayerZ = Z * cube_size - d - 0.001;
						if (Dz < 0) PlayerZ = Z * cube_size + cube_size + d + 0.001;

					}
	}
};
Player man(1.5, -0.8, 1.5);



void Reshape(int w, int h)
{
	float ratio = w * 1.0 / h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	gluPerspective(60, ratio, 0.1f, 10.0f); //задаем перспективную проекцию
	//(60 -угол обзора) (ratio- соотношщение сторон) (0.1f- минимальное видимое расстояние в float) ( 360.0f- максимальная дальность видимости)
	glMatrixMode(GL_MODELVIEW);
}




void flashlight()
{
	glBindTexture(GL_TEXTURE_2D, flash);
	glBegin(GL_QUADS);// говорим, что начинаем рисовать скример
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.05, -0.05, -0.1);// его координаты
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.05, -0.05, -0.1);// его координаты
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.05, 0.05, -0.1);// его координаты
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.05, 0.05, -0.1);// его координаты
	glEnd(); // говорим, что заканчиваем рисовать
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






void Draw() {
	double times;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // чистим цвет и глубину
	glClearColor(0, 0, 0, 0); // задаем цвет фона в режиме RGB
	glPushMatrix(); // сохраняем систему координат
	if (angle > 360)
		angle = 0;
	
	//flashlight();
	//boo();//возможно скример(картинка перед нами, нужно привязать время?)

	gluLookAt(man.PlayerX,			man.PlayerY + man.h / 2 , man.PlayerZ,
		      man.PlayerX + lx,		man.PlayerY + ly + man.h / 2 , man.PlayerZ + lz,
		      0.0f, 1.0f, 0.0f);
	//=================================начало основного цикла===================================================================================
	newtime = clock();
	times = newtime - oldtime;
	oldtime = clock();
	std::cout << 1000 / times << std::endl;
	
	floor();
	fogg();




	glBindTexture(GL_TEXTURE_2D, wall);
	for(int x = 0; x < quantity_cubes_x; x++)
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
	glutKeyboardUpFunc(keyboard_up);
	glutPassiveMotionFunc(mouseMove);//когда мышка дыигается
	glutMotionFunc(mouseMove); //когда двигаешь при нажатии
	load_textures_smooth("textures_game/floor1.jpg", &floor1,0);//текстура пола
	load_textures_smooth("textures_game/screamer.png", &screamer,0);//текстура скримера
	load_textures_smooth("textures_game/wall1.jpg", &wall,0);//текстура стен
	load_textures_smooth("textures_game/flashlight.png", &flash, 0 );//текстура фонарика
	//PlaySound("music_game/qw", NULL, SND_SYNC);  // Играем звук смерти
	glutSetCursor(GLUT_CURSOR_NONE);//убирает курсор с экрана
	glutMainLoop(); // говорим, что запускаем непрерывный цикл рисования. с этого момента циклично будет проигрываться функция draw

}