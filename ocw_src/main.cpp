/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 23:16:32 by mikim             #+#    #+#             */
/*   Updated: 2019/04/19 09:30:45 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                              Mingyun Kim   */
/*                                           https://www.github.com/mikim42   */
/* ************************************************************************** */

#include <ocw.hpp>

std::vector<std::string>	MAP;
Player	PLAYERS[5];
int		PLAYER_NUM;
int		WIDTH;
int		HEIGHT;

int		GET_PLAYER_NUMBER(std::string name)
{
	for (int i = 1; i < 5; i++)
	{
		if (PLAYERS[i].name == name)
			return (i);
	}
	return (0);
}

void	GET_POS(int n, int &y, int &x)
{
	y = PLAYERS[n].y;
	x = PLAYERS[n].x;
}

void	ac_player(int &res, Pthread &pt, int n)
{
	pt.id = std::this_thread::get_id();
	pt.done = false;
	pt.t = clock();

	if (n == 1)
		res = player1();
	else if (n == 2)
		res = player2();
	else if (n == 3)
		res = player3();
	else if (n == 4)
		res = player4();
	pt.done = true;
}

int		main(int ac, char **av)
{
	OCW		ocw;

	/* Input validation */
	std::cout << "Validating the input..." << std::endl;
	if (ac < 4 || ac > 6)
	{
		std::cout << "Usage: " << av[0]
			<< " <map file> <player 1> <player 2> <player 3> <player 4>"
			<< std::endl
			<< "       Need at least 2 players to start"
			<< std::endl;
		return (0);
	}

	/* map validation */
	std::cout << "Validating the map..." << std::endl;
	if (!ocw.read_map(av[1]))
	{
		std::cout << "Error: Invalid Map!" << std::endl;
		return (0);
	}

	/* set players */
	std::cout << "Setting players..." << std::endl;
	for (int i = 2; i < ac; i++)
	{
		if (!ocw.set_player(av[i]))
		{
			std::cout << "Error: Too many players" << std::endl;
			return (0);
		}
	}

	/* parse the game */
	std::cout << "Setting the game..." << std::endl;
	ocw.set();

	/* run the game */
	for (int i = 0; i < ocw.get_turn(); i++)
	{
		ocw.run();
		ocw.move();
	}

	/* result */
	ocw.end();
	return (0);
}
