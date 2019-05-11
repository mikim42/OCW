/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 15:58:55 by mikim             #+#    #+#             */
/*   Updated: 2019/05/11 10:27:14 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                              Mingyun Kim   */
/*                                           https://www.github.com/mikim42   */
/* ************************************************************************** */

#include <ocw.hpp>

// Michael
bool	movable(char b, int n)
{
	char c = 'a' + n - 1;
	return (b != '*' && b != c);
}

int minDist(int p1, int p2)
{
	int y1, x1;
	GET_POS(p1, y1, x1);

	int y2, x2;
	GET_POS(p2, y2, x2);

	return static_cast<int>(floor(sqrt(pow(static_cast<double>(x2 - x1), 2) + pow(static_cast<double>(y2 - y1), 2))));
}

std::vector<int> getEnemies(int myId)
{
	std::vector<int> enemies;

	for (int p = 1; p <= PLAYER_NUM; ++p)
	{
		if (p == myId)
			continue;

		enemies.emplace_back(p);
	}

	return enemies;
}

int closestPlayer(int myId)
{
	int closestPlayer = 0, dist = 0, tmp;

	std::vector<int> enemies = getEnemies(myId);

	for (int p = 0; p < static_cast<int>(enemies.size()); ++p)
	{
		int enemy = enemies[p];

		tmp = minDist(myId, enemy);

		if (!closestPlayer || tmp < dist)
		{
			closestPlayer = enemy;
			dist = tmp;
		}
	}

	return closestPlayer;
}

// Michael
bool inBounds(int x, int y)
{
	return (x >= 0 && y >= 0 &&  x < WIDTH && y < HEIGHT);
}

int closestDirection(int myId, int enemyId)
{
	int myY, myX, enemyY, enemyX;

	GET_POS(myId, myY, myX);
	GET_POS(enemyId, enemyY, enemyX);

	if (abs(enemyX - myX) > abs(enemyY - myY))
	{
		//Further away on X-axis
		if (enemyX > myX)
		{
			//Move right
			if (inBounds(myX + 1, myY) && movable(MAP[myY][myX + 1], myId))
				return RIGHT;

			//Try to move vertically to avoid obstacles
			if (enemyY > myY)
			{
				if (inBounds(myX, myY + 1) && movable(MAP[myY + 1][myX], myId))
					return DOWN;

				if (inBounds(myX, myY - 1) && movable(MAP[myY - 1][myX], myId))
					return UP;
			}
			else
			{
				if (inBounds(myX, myY - 1) && movable(MAP[myY - 1][myX], myId))
					return UP;

				if (inBounds(myX, myY + 1) && movable(MAP[myY + 1][myX], myId))
					return DOWN;
			}

			//Stuck
			return LEFT;
		}
		else
		{
			//Move left
			if (inBounds(myX - 1, myY) && movable(MAP[myY][myX - 1], myId))
				return LEFT;

			//Try to move vertically to avoid obstacles
			if (enemyY > myY)
			{
				if (inBounds(myX, myY + 1) && movable(MAP[myY + 1][myX], myId))
					return DOWN;

				if (inBounds(myX, myY - 1) && movable(MAP[myY - 1][myX], myId))
					return UP;
			}
			else
			{
				if (inBounds(myX, myY - 1) && movable(MAP[myY - 1][myX], myId))
					return UP;

				if (inBounds(myX, myY + 1) && movable(MAP[myY + 1][myX], myId))
					return DOWN;
			}

			//Stuck
			return RIGHT;
		}

	}
	else if (abs(enemyY - myY) > abs(enemyX - myX))
	{
		//Further away on Y-axis
		if (enemyY > myY)
		{
			//Move down
			if (inBounds(myX, myY + 1) && movable(MAP[myY + 1][myX], myId))
				return DOWN;

			//Try to move horizontally to avoid obstacles
			if (enemyX > myY)
			{
				if (inBounds(myX + 1, myY) && movable(MAP[myY][myX + 1], myId))
					return RIGHT;

				if (inBounds(myX - 1, myY) && movable(MAP[myY][myX - 1], myId))
					return LEFT;
			}
			else
			{
				if (inBounds(myX - 1, myY) && movable(MAP[myY][myX - 1], myId))
					return LEFT;

				if (inBounds(myX + 1, myY) && movable(MAP[myY][myX + 1], myId))
					return RIGHT;
			}

			//Stuck
			return UP;
		}
		else
		{
			//Move up
			if (inBounds(myX, myY - 1) && movable(MAP[myY - 1][myX], myId))
				return UP;

			//Try to move horizontally to avoid obstacles
			if (enemyX > myY)
			{
				if (inBounds(myX + 1, myY) && movable(MAP[myY][myX + 1], myId))
					return RIGHT;

				if (inBounds(myX - 1, myY) && movable(MAP[myY][myX - 1], myId))
					return LEFT;
			}
			else
			{
				if (inBounds(myX - 1, myY) && movable(MAP[myY][myX - 1], myId))
					return LEFT;

				if (inBounds(myX + 1, myY) && movable(MAP[myY][myX + 1], myId))
					return RIGHT;
			}

			//Stuck
			return DOWN;
		}
	}
	else if (abs(enemyX - myX) == abs(enemyY -myY))
	{
		//Equal distance, default to direction map is larger in
		if (WIDTH > HEIGHT)
		{
			//Further away on X-axis
			if (enemyX > myX)
			{
				//Move right
				if (inBounds(myX + 1, myY) && movable(MAP[myY][myX + 1], myId))
					return RIGHT;

				//Try to move vertically to avoid obstacles
				if (enemyY > myY)
				{
					if (inBounds(myX, myY + 1) && movable(MAP[myY + 1][myX], myId))
						return DOWN;

					if (inBounds(myX, myY - 1) && movable(MAP[myY - 1][myX], myId))
						return UP;
				}
				else
				{
					if (inBounds(myX, myY - 1) && movable(MAP[myY - 1][myX], myId))
						return UP;

					if (inBounds(myX, myY + 1) && movable(MAP[myY + 1][myX], myId))
						return DOWN;
				}

				//Stuck
				return LEFT;
			}
			else
			{
				//Move left
				if (inBounds(myX - 1, myY) && movable(MAP[myY][myX - 1], myId))
					return LEFT;

				//Try to move vertically to avoid obstacles
				if (enemyY > myY)
				{
					if (inBounds(myX, myY + 1) && movable(MAP[myY + 1][myX], myId))
						return DOWN;

					if (inBounds(myX, myY - 1) && movable(MAP[myY - 1][myX], myId))
						return UP;
				}
				else
				{
					if (inBounds(myX, myY - 1) && movable(MAP[myY - 1][myX], myId))
						return UP;

					if (inBounds(myX, myY + 1) && movable(MAP[myY + 1][myX], myId))
						return DOWN;
				}

				//Stuck
				return RIGHT;
			}
		}
		else
		{
			//If taller or equal, move on y-axis

			//Further away on Y-axis
			if (enemyY > myY)
			{
				//Move down
				if (inBounds(myX, myY + 1) && movable(MAP[myY + 1][myX], myId))
					return DOWN;

				//Try to move horizontally to avoid obstacles
				if (enemyX > myY)
				{
					if (inBounds(myX + 1, myY) && movable(MAP[myY][myX + 1], myId))
						return RIGHT;

					if (inBounds(myX - 1, myY) && movable(MAP[myY][myX - 1], myId))
						return LEFT;
				}
				else
				{
					if (inBounds(myX - 1, myY) && movable(MAP[myY][myX - 1], myId))
						return LEFT;

					if (inBounds(myX + 1, myY) && movable(MAP[myY][myX + 1], myId))
						return RIGHT;
				}

				//We're stuck
				return UP;
			}
			else
			{
				//Move up
				if (inBounds(myX, myY - 1) && movable(MAP[myY - 1][myX], myId))
					return UP;

				//Try to move horizontally to avoid obstacles
				if (enemyX > myY)
				{
					if (inBounds(myX + 1, myY) && movable(MAP[myY][myX + 1], myId))
						return RIGHT;

					if (inBounds(myX - 1, myY) && movable(MAP[myY][myX - 1], myId))
						return LEFT;
				}
				else
				{
					if (inBounds(myX - 1, myY) && movable(MAP[myY][myX - 1], myId))
						return LEFT;

					if (inBounds(myX + 1, myY) && movable(MAP[myY][myX + 1], myId))
						return RIGHT;
				}

				//Stuck
				return DOWN;
			}
		}
	}

	return rand() % 4 + 1;
}

//PLAYER FUNCTION "dat-boi" Michael
int player1(void)
{
	int myId, closestId;

	myId = GET_PLAYER_NUMBER("dat-boi");
	closestId = closestPlayer(myId);

	if (closestId)
		return closestDirection(myId, closestId);
	return rand() % 4 + 1;
}

// Wen clorox
int		player5(void)
{
	int my_num;
	int x,y;
	my_num = GET_PLAYER_NUMBER("clorox");
	GET_POS(my_num, y, x);
	//left bound
	if(x == 0 && y < HEIGHT - 1)
		return DOWN;
	else if(y == 0 && x < WIDTH - 1)
		return RIGHT;
	else if(x == WIDTH - 1 && y < HEIGHT - 1)
		return DOWN;
	else if(y == HEIGHT - 1 && x == 0)
		return RIGHT;
	else if(y == HEIGHT - 1 && x < WIDTH - 1)
		return UP;
	else if(y > 0 && y < HEIGHT - 1 && x > 0 && x < WIDTH - 1)
		return LEFT;
	else
		return UP;
}

//Bhavi bot
int		player4(void)
{
	int my_num;
	int x, y;
	int a=0;

	my_num = GET_PLAYER_NUMBER("bot");
	GET_POS(my_num, y, x);

	if (x==a )
	{
		if(y==a )
			return RIGHT;
		else
			return UP;
	}
	else if(y==a )
	{
		if(x==WIDTH-1 )
			return DOWN;
		else
			return RIGHT;
	}
	else if(x==WIDTH-1 )
	{
		if(y==HEIGHT-1)
			return LEFT;
		else
			return DOWN;
	}
	else
		return LEFT;
}

//	Josh terminator
int		player3(void)
{
	int my_num, y, x;

	bool previous = false;
	my_num = GET_PLAYER_NUMBER("Terminator");
	GET_POS(my_num, y, x);

	if (!previous)
	{
		if (y > 0 && x > 0 && movable(MAP[y - 1][x], my_num))//check boundary
		{
			std::cout << "You're a Seg Fault";
			previous = true;
			return RIGHT;
		}
		if (y < HEIGHT - 1 && x < WIDTH - 1 && movable(MAP[y + 1][x], my_num)) //check boudnary
		{
			std::cout << "You're a Seg Fault";
			previous = true;
			return UP;
		}
		if (x > 0 && movable(MAP[y][x - 1], my_num))
		{
			std::cout << "You're a Seg Fault ";
			return  DOWN;
		}
	}
	std::cout << "You're a Seg Fault";
	return LEFT;
}

//	Anthony
int		player2(void)
{
	int my_num;
	int x, y;
	char my_letter;
	char e_letter;

	//MAP 2d array
	my_num = GET_PLAYER_NUMBER("Anthony");
	// get player letter
	switch(my_num)
	{
		case 1: my_letter = 'A'; break;
		case 2: my_letter = 'B'; break;
		case 3: my_letter = 'C'; break;
		case 4: my_letter = 'D'; break;
	}

	// search players !myself
	for(int i=0; i< WIDTH; i++) {
        for(int j=0; j< HEIGHT; j++) {
			if(MAP[i][j] == 'A' && MAP[i][j] != my_letter)
				e_letter = 'A';
			else if(MAP[i][j] == 'B' && MAP[i][j] != my_letter)
				e_letter = 'B';
			else if(MAP[i][j] == 'C' && MAP[i][j] != my_letter)
				e_letter = 'C';
			else if(MAP[i][j] == 'D' && MAP[i][j] != my_letter)
				e_letter = 'D';
				}
			}

	// get and set current position
	GET_POS(my_num, y, x);

	// search for dots first
	//~ if(y > 0 && MAP[y-1][x] == '.' && movable(MAP[y - 1][x], my_num))
		//~ return UP;
	//~ else if (y < HEIGHT - 1 && movable(MAP[y + 1][x], my_num) && MAP[y + 1][x] == '.')
		//~ return DOWN;
	//~ else if (x > 0 && movable(MAP[y][x - 1], my_num) && MAP[y][x - 1] == '.')
		//~ return LEFT;
	//~ else if (x > 0 && movable(MAP[y][x + 1], my_num) && MAP[y][x + 1] == '.')
		//~ return RIGHT;

	// look for enemy taken spots
	if(y > 0 && MAP[y-1][x] == e_letter && movable(MAP[y - 1][x], my_num))
		return UP;
	else if (y < HEIGHT - 1 && movable(MAP[y + 1][x], my_num) && MAP[y + 1][x] == e_letter)
		return DOWN;
	else if (x > 0 && movable(MAP[y][x - 1], my_num) && MAP[y][x - 1] == e_letter)
		return LEFT;
	else if (x > 0 && movable(MAP[y][x + 1], my_num) && MAP[y][x + 1] == e_letter)
		return RIGHT;

	// default
	if (y > 0 && movable(MAP[y - 1][x], my_num))
		return UP;
	else if (y < HEIGHT - 1 && movable(MAP[y + 1][x], my_num))
		return DOWN;
	else if (x > 0 && movable(MAP[y][x - 1], my_num))
		return LEFT;
	else
		return RIGHT;
}

