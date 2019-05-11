/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocw.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 23:16:25 by mikim             #+#    #+#             */
/*   Updated: 2019/05/09 19:58:53 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                              Mingyun Kim   */
/*                                           https://www.github.com/mikim42   */
/* ************************************************************************** */

#ifndef _OCW_HPP_
# define _OCW_HPP_

# include <iostream>
# include <fstream>
# include <vector>
# include <thread>
# include <chrono>
# include <utility>
# include <map>
# include <cmath>
# include <algorithm>

# define UP 1
# define DOWN 2
# define LEFT 3
# define RIGHT 4
# define COLL 5
# define TIMEOUT 6

struct	Player
{
	std::string	name;
	int			y;
	int			x;
};

struct	Pthread
{
	clock_t			t;
	std::thread::id	id;
	bool			done;
};

class	OCW
{
	public:
		OCW();
		~OCW();
		bool	read_map(char *m);
		bool	set_player(char *s);
		void	set(void);
		void	randomize(int r[]);
		void	update(void);
		void	run(void);
		void	move(void);
		void	end(void);

		int		get_turn(void);

	private:
		int							_turn;
		int							_cturn;
		std::vector<std::string>	_map;
		size_t						_width;
		size_t						_height;
		Player						_player[4];
		int							_pn;
		int							_ct;
		int							_at[4];
		std::vector<int>			_hist[4];
		std::string					_moves[6];
};

void	ac_player(int &res, Pthread &pt, int n);

int		player1(void);
int		player2(void);
int		player3(void);
int		player4(void);

int		GET_PLAYER_NUMBER(std::string name);
void	GET_POS(int, int &y, int &x);

extern	int		WIDTH;
extern	int		HEIGHT;
extern	Player	PLAYERS[5];
extern	int		PLAYER_NUM;
extern	std::vector<std::string>	MAP;

#endif
