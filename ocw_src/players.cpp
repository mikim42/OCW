/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   players.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 00:58:50 by mikim             #+#    #+#             */
/*   Updated: 2019/04/19 09:09:45 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                              Mingyun Kim   */
/*                                           https://www.github.com/mikim42   */
/* ************************************************************************** */

#include <ocw.hpp>

/*	MOVEMENTS:
**
**	Return a direction to move
**	UP
**	DOWN
**	LEFT
**	RIGHT
**
**	* Other than these, the bot might not move.
**	* Any undefined return value may cause a defeat
*/

/*	API:
**
**	GET_PLAYER_NUMBER("YOUR-BOT-NAME")
**	it returns the player's number
**
**	GET_POS((int)player-number, (int)y, (int)x)
**	it sets x and y to the coordinates of the bot's position
**
**	MAP[y][x]:
**	map is stored in 2D-array
**
**	HEIGHT:
**	the height of the map
**
**	WIDTH:
**	the width of the map
**
**	(std::string)PLAYERS[n].name  (int)PLAYERS[n].y  (int)PLAYERS[n].x
**	the information of n-th player (PLAYERS[1] = the first player)
**
**	(int)PLAYER_NUM
**	the number of players in the game
**
*/

/*	FUNCTION:
**
**	Functions must be named:
**	int player1(void)
**	int player2(void)
**	int player3(void)
**	int player4(void)
**	* return type must be int
**	* if not, it will cause compilation errors
**
**	If ny error occurs in your function, you may lose
**
*/

bool	movable(char b, int n)
{
	char c = 'a' + n - 1;
	return (b != '*' && b != c);
}

/*
**	Randommy-bot
*/

int		player1(void)
{
	int		r;

	r = rand() % 4 + 1;
	if (r == 1)
		return UP;
	if (r == 2)
		return DOWN;
	if (r == 3)
		return LEFT;
	return RIGHT;
}

/*
**	Circler-bot
*/
int		player2(void)
{
	int my_num;
	int x, y;
	int z;


	my_num = GET_PLAYER_NUMBER("Circler-bot");
	GET_POS(my_num, y, x);
	z = my_num;
	if (y > 0 && x > 0 && movable(MAP[y - 1][x], my_num))
		return UP;
	if (y < HEIGHT - 1 && x < WIDTH - 1 && movable(MAP[y + 1][x], my_num))
		return DOWN;
	if (x > 0 && movable(MAP[y][x - 1], my_num))
		return LEFT;
	return RIGHT;
}

/*
**	Chuno-bot
*/
int		player3(void)
{
	int my_num;
	int enemy;
	int x, y;
	int e_x, e_y;
	int diff_x, diff_y;

	my_num = GET_PLAYER_NUMBER("Chuno-bot");
	GET_POS(my_num, y, x);
	if (my_num == 1)
		enemy = 2;
	else
		enemy = 1;
	GET_POS(enemy, e_y, e_x);
	diff_y = e_y - y;
	diff_x = e_x - x;
	if (abs(diff_y) > abs(diff_x))
	{
		if (diff_y > 0)
			return DOWN; 
		else
			return UP;
	}
	else
	{
		if (diff_x > 0)
			return RIGHT;
		else
			return LEFT;
	}
}

/*
**	Stepper-bot
*/
int		player4(void)
{
	int my_num;
	int x, y;

	my_num = GET_PLAYER_NUMBER("Stepper-bot");
	GET_POS(my_num, y, x);
	if (y > 0 && movable(MAP[y - 1][x], my_num))
		return UP;
	else if (y < HEIGHT - 1 && movable(MAP[y + 1][x], my_num))
		return DOWN;
	else if (x > 0 && movable(MAP[y][x - 1], my_num))
		return LEFT;
	else
		return RIGHT;
}

/*
int my_number, y, x;

my_number = GET_PLAYER_NUMBER("My-bot");
GET_POS(my_number, y, x);
if (x < WIDTH - 1 && MAP[y][x + 1] == '.')
	return RIGHT;
if (y < HEIGHT - 1 && MAP[y + 1][x] == '.')
	return DOWN;
*/



