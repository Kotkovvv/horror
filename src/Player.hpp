﻿class Player {
public:
	float PlayerX, PlayerY, PlayerZ, dx, dz, dSideX, dSideZ, dFrontX, dFrontZ, w, h, d, speed, View;

	Player(float x0, float y0, float z0) {
		PlayerX = x0; PlayerY = y0; PlayerZ = z0;
		dx = 0;  dz = 0;
		dSideX = 0; dSideZ = 0;
		dFrontX = 0; dFrontZ = 0;
		w = 0.3f; h = 1.9f; d = 0.3f; speed = 0.1;
		View = 90; // угол обзора
	}
	/**
	\brief проверяет на столкновение
*/
	bool check(int x, int z) {
		if ((x < 0) || (x > quantity_cubes_x) ||
			(z < 0) || (z > quantity_cubes_z)) return false;
		if (choice_of_labirynth==NUM1)
		return cubes[x][z];
		else 
			return cubes1[x][z];

	}
	/**
	\brief Оснновная функцию обновления игрока
	\param[in] time время 1 кадра
*/
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
	/**
	\brief определяет поведение при столкновении с колизией
	эта функция принимает на вход скорости по осям игрока, и при столкновении с клизией определяет, как должен вести себя игрок
*/

	void collision(float Dx, float Dz) {
		int cube_size = 1;
		for (int X = (PlayerX - w); X < (PlayerX + w); X++)
			for (int Z = (PlayerZ - d); Z < (PlayerZ + d); Z++)
				if (check(X, Z))
				{
					if (Dx > 0) PlayerX = X * cube_size - w - 0.001;
					if (Dx < 0) PlayerX = X * cube_size + cube_size + w + 0.001;
					if (Dz > 0) PlayerZ = Z * cube_size - d - 0.001;
					if (Dz < 0) PlayerZ = Z * cube_size + cube_size + d + 0.001;
				}
	}
};
/**
	\brief Создаем объект

*/
Player man(1.5, -0.8, 1.5);//начальная позиция игрока

class area {
	float x1, x2;
	float y1, y2;
public:
	area(float x1, float y1, float x2, float y2) {
		this->x1 = x1; this->x2 = x2;
		this->y1 = y1; this->y2 = y2;
	}
	//
	// *   ----1 точка
	//   * --------2 точка
	//
	bool update() {
		if (x1 < man.PlayerX && x2 > man.PlayerX && y1 < man.PlayerZ && y2 > man.PlayerZ)
			return true;
		else return false;
	}
};

area change(18, 18, 19, 19);
area scream(2, 2, 3, 3);
area scream1(1, 4, 2, 5);
