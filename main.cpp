#include <glut.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <ctime>
#include <SOIL.h> // ���������� ��� ������. ���� �� �����
#pragma comment (lib,"SOIL.lib")



int width = 1600; // ������ ����
int height = 800; // ������ ����
int W = width;
int H = height;
float angle = 0; // ���� ��������
int cube_size = 1;

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
float mouseXOld = 0;
float mouseYOld = 0;
float ly = 0;

float PlayerX = 0;
float PlayerZ = 0;
GLuint wall[1];
GLuint screamer[1];
GLuint pol[1];

int cubes[2][2] = { 1, 0,
				   0, 1 }; //���� ��������� �����


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
	float View; // ���� ������

	Player(float x0, float y0, float z0) {
		PlayerX = x0; PlayerY = y0; PlayerZ = z0;
		dx = 0;  dz = 0;
		dSideX = 0; dSideZ = 0;
		dFrontX = 0; dFrontZ = 0;
		w = 0.5f; h = 1.9f; d = 0.5f; speed = 0.1;
		onGround = false;
		View = 90; // ���� ������
	}
	bool check(int x,  int z) {
		if ((x < 0) or (x > 2) or
			(z < 0) or (z > 2)) return false;
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

void keyboard_special(int key, int x, int y) {
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
	gluPerspective(60, ratio, 0.1f, 180.0f); //������ ������������� ��������
	//(60 -���� ������) (ratio- ������������ ������) (0.1f- ����������� ������� ���������� � float) ( 360.0f- ������������ ��������� ���������)
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
void mouseMove(int x, int y) {
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
	else {

		mouseXOld = (width / 2) - x;
		mouseYOld = (height / 2) - y;
		glutWarpPointer((width / 2), (height / 2));
	}

	//glutPostRedisplay();

}


void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 27: // ���� key = 27(escape), �� ������� �� ���������
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

	switch (key) {
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

void cube() { //����� �� ������������
	glColor3f(0.5, 1.0, 1.0); // ������ ���� �����
	///������
	glBegin(GL_QUADS); // �������, ��� �������� �������� ���
	glVertex3f(1, -1, 1); // ��� ����������
	glVertex3f(-1, -1, 1);// ��� ����������
	glVertex3f(-1, 1, 1);// ��� ����������
	glVertex3f(1, 1, 1);// ��� ����������
	glEnd(); // �������, ��� ����������� ��������


	//��������
	glColor3f(1.0, 0.5, 1.0);// ������ ���� �����
	glBegin(GL_QUADS);// �������, ��� �������� �������� ���
	glVertex3f(-1, -1, -1);// ��� ����������
	glVertex3f(1, -1, -1);// ��� ����������
	glVertex3f(1, 1, -1);// ��� ����������
	glVertex3f(-1, 1, -1);// ��� ����������
	glEnd(); // �������, ��� ����������� ��������


	//������
	glColor3f(1.0, 1.0, 0.5);
	glBegin(GL_QUADS);
	glVertex3f(1, -1, -1);
	glVertex3f(1, -1, 1);
	glVertex3f(1, 1, 1);
	glVertex3f(1, 1, -1);
	glEnd();


	//�����
	glColor3f(0.5, 0.5, 1.0);
	glBegin(GL_QUADS);
	glVertex3f(-1, -1, 1);
	glVertex3f(-1, -1, -1);
	glVertex3f(-1, 1, -1);
	glVertex3f(-1, 1, 1);
	glEnd();


	//������
	glColor3f(1.0, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex3f(-1, -1, 1);
	glVertex3f(1, -1, 1);
	glVertex3f(1, -1, -1);
	glVertex3f(-1, -1, -1);
	glEnd();


	//�������
	glColor3f(0.5, 0.5, 0.5);
	glBegin(GL_QUADS);
	glVertex3f(-1, 1, -1);
	glVertex3f(1, 1, -1);
	glVertex3f(1, 1, 1);
	glVertex3f(-1, 1, 1);
	glEnd();
}

void walls()
{

	//��� �������
	glBindTexture(GL_TEXTURE_2D, pol[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f);  glVertex3f(-4, -1, 7);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(4, -1, 7);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(4, -1, -1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-4, -1, -1);
	glEnd();


	//������ �����
	glBindTexture(GL_TEXTURE_2D, wall[0]);
	glBegin(GL_QUADS);// �������, ��� �������� �������� ���
	glTexCoord2f(1.0f, 1.0f); glVertex3f(4, -1, -1);// ��� ����������
	glTexCoord2f(0.0f, 1.0f);  glVertex3f(4, 1, -1);// ��� ����������
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-4, 1, -1);// ��� ����������
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-4, -1, -1);// ��� ����������
	glEnd(); // �������, ��� ����������� ��������

	//������ �����
	glBindTexture(GL_TEXTURE_2D, wall[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-4, -1, 7);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-4, -1, -1);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-4, 1, -1);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-4, 1, 7);
	glEnd();

	//����� ������
	glBindTexture(GL_TEXTURE_2D, wall[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(4, -1, -1);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(4, -1, 7);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(4, 1, 7);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(4, 1, -1);
	glEnd();

	//�������� �����
	glBindTexture(GL_TEXTURE_2D, wall[0]);
	glBegin(GL_QUADS); // �������, ��� �������� �������� ���
	glTexCoord2f(1.0f, 1.0f); glVertex3f(4, -1, 7); // ��� ����������
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-4, -1, 7);// ��� ����������
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-4, 1, 7);// ��� ����������
	glTexCoord2f(1.0f, 0.0f); glVertex3f(4, 1, 7);// ��� ����������
	glEnd(); // �������, ��� ����������� ��������



	///������ �������
	glBindTexture(GL_TEXTURE_2D, wall[0]);
	glBegin(GL_QUADS); // �������, ��� �������� �������� ���
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1, -1, 4); // ��� ����������
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1, -1, 4);// ��� ����������
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, 1, 4);// ��� ����������
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, 1, 4);// ��� ����������
	glEnd(); // �������, ��� ����������� ��������


	//�������� �������
	glBindTexture(GL_TEXTURE_2D, wall[0]);
	glBegin(GL_QUADS);// �������, ��� �������� �������� ���
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, 1, 2);// ��� ����������
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1, 1, 2);// ��� ����������
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1, -1, 2);// ��� ����������
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, -1, 2);// ��� ����������
	glEnd(); // �������, ��� ����������� ��������


	//����� �������
	glBindTexture(GL_TEXTURE_2D, wall[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(1, -1, 2);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(1, -1, 4);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(1, 1, 4);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(1, 1, 2);
	glEnd();


	//������ �������
	glBindTexture(GL_TEXTURE_2D, wall[0]);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-1, -1, 4);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-1, -1, 2);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-1, 1, 2);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-1, 1, 4);
	glEnd();



}

void boo()
{
	glBindTexture(GL_TEXTURE_2D, screamer[0]);
	glBegin(GL_QUADS);// �������, ��� �������� �������� �������
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.5, -0.5, -1);// ��� ����������
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5, -0.5, -1);// ��� ����������
	glTexCoord2f(0.0f, 0.0f); glVertex3f(0.5, 0.5, -1);// ��� ����������
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5, 0.5, -1);// ��� ����������
	glEnd(); // �������, ��� ����������� ��������
}


void Draw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ���� � �������
	glClearColor(0, 0, 0, 0); // ������ ���� ���� � ������ RGB
	glPushMatrix(); // ��������� ������� ���������

	//lx = sin(angle);
	// lz = cos(angle);
	if (angle > 360)
		angle = 0;

	//move();

	//�������� �������(�������� ����� ����, ����� ��������� �����?)
	//boo();//

	gluLookAt(man.PlayerX, man.PlayerY + man.h / 2 - 0.5, man.PlayerZ,
		man.PlayerX + lx, man.PlayerY + ly + man.h / 2, man.PlayerZ + lz,
		0.0f, 1.0f, 0.0f);




	//glTranslatef(0, 0, 0); // ������� ������� ��������� �� -5 �� z, ����� ��� �� ��������� � ���

	//=================================������ ��������� �����===================================================================================


	walls();
	// ����� 100 ����� ��� ����
	//for (int x = 0; x < 10; x++)
		//for (int z = 0; z < 10; z++) {
		//	glTranslatef(x * 4, 0, z * 4);
		//	cube(); // �������, ������� ������ ���
		//	glTranslatef(-x * 4, 0, -z * 4);
		//}


	man.update(1);
	//=================================����� ��������� �����===================================================================================
	glPopMatrix(); // ��������� ������� ��������
	glutPostRedisplay(); // ��������� �������� � ����
	glFinish(); // ����������� ���������
}



int main() {
	//===========================INITIALIZATION===========================================
	glutInitWindowSize(width, height); // �������������� ���� � �������� ������� � �������
	glutInitDisplayMode(GLUT_RGB); // �������, ��� ����� ����� � ���� ����� RGB
	glutCreateWindow("horror game"); // ������� ���� � ��������� horror game
	glEnable(GL_DEPTH_TEST); // �������� ����� �������. ��� ����� ��� ����, ����� ������� ��������� ������������ ���� �� ������
	glEnable(GL_TEXTURE_2D);// �������
	glutDisplayFunc(Draw); // ����� �������� �������, � ������� ����� ��������
	glutReshapeFunc(Reshape); // ����� �������� �������, ������� ����� ������������ ��������� ������� ����
	glutKeyboardFunc(keyboard); // ����� �������� �������, ��� �� ����� ��������, ����� ������� ������ �� �����
	glutSpecialFunc(keyboard_special);
	glutKeyboardUpFunc(keyboard_up);
	glutPassiveMotionFunc(mouseMove);//����� ����� ���������
	glutMotionFunc(mouseMove); //����� �������� ��� �������
	wallTextures();//������� �����(����)
	screamerTextures();
	polTextures();


	/*for (int x = 0; x < 7; x++)
			for (int z = 0; z < 7; z++) {
				if (x == 0 or x == 6 or z == 0 or z == 6)
					cubes[x][z] = 1;
			}*/
	glutMainLoop(); // �������, ��� ��������� ����������� ���� ���������. � ����� ������� �������� ����� ������������� ������� draw
}//*/