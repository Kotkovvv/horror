#include <glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <ctime>
#include <SOIL.h> // библиотека для тектур
#pragma comment (lib,"SOIL.lib")



int width = 1600; // высота окна
int height = 800; // ширина окна
int W = width;
int H = height;
float angle = 0; // угол поворота
int cube_size = 1;
const int quantity_cubes_x = 20;//количество невидимых кубов по x
const int quantity_cubes_z = 20;// количество невидимых кубов по z
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
GLuint wall;//переменная для текстуры стены
GLuint screamer;//переменная для текстуры скримера
GLuint floor1;//переменная для текстуры пола
GLuint flash;//переменная для текстуры фонарика

int cubes[quantity_cubes_x][quantity_cubes_z] = { {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},//сюда z
												  {1, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
												  {1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1},
								/*		|	*/	  {1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1},
								/*перед	|	*/	  {1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 1},
								/*		V	*/	  {1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1},
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


#include "textures.hpp"

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
		w = 0.2f; h = 1.9f; d = 0.2f; speed = 0.2;
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
	gluPerspective(60, ratio, 0.1f, 20.0f); //задаем перспективную проекцию
	//(60 -угол обзора) (ratio- соотношщение сторон) (0.1f- минимальное видимое расстояние в float) ( 360.0f- максимальная дальность видимости)
	glMatrixMode(GL_MODELVIEW);
}


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
		

		break;
	case 'a':
	case 'A':
	case 'd':
	case 'D':
		move_side = 0;
		

		break;
	}
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

void draw_wall_new(int x, int z) {
	glBegin(GL_QUADS);
	if (cubes[x][z] != cubes[x - 1][z] and  x != 0) {
		// задняя стена
		glColor3f(0.6,0.6,0.6);
		glTexCoord2f(1.0f, 1.0f);  glVertex3f(0, -1, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(0, 1, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(0, 1, 1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0, -1, 1);
	}
	// правая
	if (cubes[x][z] != cubes[x ][z+1] and z != 20) {
		glColor3f(0.5, 0.5, 0.5);
		glTexCoord2f(1.0f, 1.0f);  glVertex3f(0, -1, 1);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1, -1, 1);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1, 1, 1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 1, 1);
	}
	// передняя
	if (cubes[x][z] != cubes[x + 1][z] and x != 20) {
		glColor3f(0.6, 0.6, 0.6);
		glTexCoord2f(1.0f, 1.0f);  glVertex3f(1, -1, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1, 1, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1, 1, 1);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, 1);
	}
	// задняя
	if (cubes[x][z] != cubes[x][z - 1] and z != 0) {
		glColor3f(0.5, 0.5, 0.5);
		glTexCoord2f(1.0f, 1.0f);  glVertex3f(0, -1, 0);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(1, -1, 0);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(1, 1, 0);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(0, 1, 0);
	}

	glEnd();
}
void Draw() {

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
	glBindTexture(GL_TEXTURE_2D, floor1);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(1, -1, 19);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(19, -1, 19);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(19, -1, 1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, -1, 1);
	glEnd();

	glBindTexture(GL_TEXTURE_2D, wall);
	for(int x = 0; x < quantity_cubes_x; x++)
		for (int z = 0; z < quantity_cubes_z; z++) {
			if (!cubes[x][z]) continue;
			glTranslatef(x, 0, z);
			draw_wall_new(x, z);
			glTranslatef(-x, 0, -z);
			
		}
	


	man.update(1);
	//=================================конец основного цикла===================================================================================
	glPopMatrix(); // загружаем систему кординат
	glutPostRedisplay(); // Обновляем картинку в окне
	glFinish(); // заканчиваем рисование
}

void load_textures_blocks(const char* image, GLuint* texturesy) //функция, загружающая текстуры
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
	glutKeyboardUpFunc(keyboard_up);
	glutPassiveMotionFunc(mouseMove);//когда мышка дыигается
	glutMotionFunc(mouseMove); //когда двигаешь при нажатии
	load_textures_smooth("textures_game/floor1.jpg", &floor1,0);//текстура пола
	load_textures_smooth("textures_game/screamer.png", &screamer,0);//текстура скримера
	load_textures_smooth("textures_game/wall1.jpg", &wall,0);//текстура стен
	load_textures_smooth("textures_game/flashlight.jpg", &flash, 0);//текстура фонарика
	glutMainLoop(); // говорим, что запускаем непрерывный цикл рисования. с этого момента циклично будет проигрываться функция draw
}