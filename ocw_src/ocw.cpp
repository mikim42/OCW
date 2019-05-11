/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocw.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/26 23:17:47 by mikim             #+#    #+#             */
/*   Updated: 2019/05/10 07:26:22 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                              Mingyun Kim   */
/*                                           https://www.github.com/mikim42   */
/* ************************************************************************** */

#include <ocw.hpp>

OCW::OCW(void)
{
	_turn = 0;
	_cturn = 0;
	_pn = 0;
	_ct = 0;
	_moves[0] = "UP";
	_moves[1] = "DOWN";
	_moves[2] = "LEFT";
	_moves[3] = "RIGHT";
	_moves[4] = "COLLISION";
	_moves[5] = "TIME_OUT";
}

OCW::~OCW(void)
{
	;
}

int		OCW::get_turn(void)
{
	return _turn;
}

bool	OCW::read_map(char *m)
{
	std::ifstream	f(m);
	std::string		tmp;

	if (!f.is_open())
		return false;
	getline(f, tmp, '\n');
	if ((_turn = std::stoi(tmp)) <= 0)
		return false;
	while (getline(f, tmp, '\n'))
		_map.push_back(tmp);
	_height = _map.size();
	_width = _map[0].length();
	for (size_t i = 1; i < _height; i++)
	{
		if (_map[i].length() != _width)
			return false;
		for (size_t j = 0; j < _width; j++)
		{
			if (_map[i][j] != '.' && _map[i][j] != '*' && _map[i][j] != 'X')
				return false;
			if (_map[i][j] == 'X')
				_ct++;
		}
	}
	if (_ct < 2 || _ct > 4)
		return false;
	return true;
}

bool	OCW::set_player(char *s)
{
	_player[_pn].name = s;
	_player[_pn].x = 0;
	_player[_pn].y = 0;
	_pn++;
	if (_pn > _ct)
		return false;
	return true;
}

void	OCW::set(void)
{
	int	r[_ct];
	int i = 0;

	randomize(r);
	for (size_t y = 0; y < _height; y++)
	{
		for (size_t x = 0; x < _width; x++)
		{
			if (_map[y][x] == 'X')
			{
				if (r[i] > _pn)
					_map[y][x] = '.';
				else
				{
					_map[y][x] = r[i] + 64;
					_player[r[i] - 1].x = x;
					_player[r[i] - 1].y = y;
				}
				i++;
			}
		}
	}
	/* *************************** GAME INFO ******************************** */
	std::cout << std::endl << "Players: " << _pn << std::endl;
	for (int i = 0; i < _pn; i++)
		std::cout << "Player " << i + 1 << ": " << _player[i].name << std::endl;
	std::cout << "Map: " << _width << " " << _height << std::endl << std::endl;
	/* *************************** GAME INFO ******************************** */
	/* ************************ BEFORE OPERATION **************************** */
	std::cout << "Turn " << _cturn++ << std::endl;
	for (int i = 0; i < _pn; i++)
	{
		std::cout << "Player " << i + 1 << " "
		<< _player[i].name << std::endl;
	}
	/* ************************ BEFORE OPERATION **************************** */
	/* *************************** PRINT MAP ******************************** */
	for (size_t i = 0; i < _height; i++)
		std::cout << _map[i] << std::endl;
	/* *************************** PRINT MAP ******************************** */
	/* ************************** PRINT MOVES ******************************* */
	for (int i = 0; i < _pn; i++)
	{
		std::cout << "Player " << i + 1 << " Stand-By" << std::endl;
	}
	std::cout << std::endl;
	/* ************************** PRINT MOVES ******************************* */
}

void	OCW::randomize(int r[])
{
	int i = 0;

	srand(clock());
	while (i < _ct - 1)
	{
		int		tmp = (rand() % _ct) + 1;
		bool	check = false;

		for (int j = 0; j < 4; j++)
			if (r[j] == tmp)
				check = true;
		if (!check)
			r[i++] = tmp;
	}
}

void	OCW::update(void)
{
	WIDTH = _width;
	HEIGHT = _height;
	MAP.clear();
	for (size_t i = 0; i < _height; i++)
		MAP.push_back(_map[i]);
	bzero(&PLAYERS[0], sizeof(Player));
	for (int i = 0; i < _pn; i++)
		PLAYERS[i + 1] = _player[i];
	PLAYER_NUM = _pn;
}

void	OCW::run(void)
{
	std::fill(_at, _at + _pn, 0);

	std::cout << "Turn " << _cturn++ << std::endl;
	for (int i = 0; i < _pn; i++)
	{
		Pthread		pt;
		std::thread	th(ac_player, std::ref(_at[i]), std::ref(pt), i + 1);

		/* ***********************BEFORE OPERATION*************************** */
		std::cout << "Player " << i + 1 << " "
		<< _player[i].name << std::endl;
		/* ***********************BEFORE OPERATION*************************** */
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
		while (!pt.done)
		{
			if ((double)(clock() - pt.t) / CLOCKS_PER_SEC > 3)
			{
				pthread_cancel(th.native_handle());
				_at[i] = TIMEOUT;
				break ;
			}
		}
		th.join();
		update();
	}
}

void	OCW::move(void)
{
	std::pair<int, int> m[_pn];

	for (int i = 0; i < _pn; i++)
	{
		size_t x = _player[i].x;
		size_t y = _player[i].y;
		if (_at[i] == UP)
		{
			if (y == 0 || _map[y - 1][x] == '*')
				_at[i] = COLL;
			else
				m[i] = std::make_pair(y - 1, x);
		}
		else if (_at[i] == DOWN)
		{
			if (y == _height - 1 || _map[y + 1][x] == '*')
				_at[i] = COLL;
			else
				m[i] = std::make_pair(y + 1, x);
		}
		else if (_at[i] == LEFT)
		{
			if (x == 0 || _map[y][x - 1] == '*')
				_at[i] = COLL;
			else
				m[i] = std::make_pair(y, x - 1);
		}
		else if (_at[i] == RIGHT)
		{
			if (x == _width - 1 || _map[y][x + 1] == '*')
				_at[i] = COLL;
			else
				m[i] = std::make_pair(y, x + 1);
		}
	}
	for (int i = 0; i < _pn - 1; i++)
	{
		for (int j = i + 1; j < _pn; j++)
		{
			if (m[i].first == m[j].first && m[i].second == m[j].second)
			{
				_at[i] = COLL;
				_at[j] = COLL;
			}
		}
	}
	for (int i = 0; i < _pn; i++)
	{
		if (_at[i] != TIMEOUT && _at[i] != COLL)
		{
			_map[_player[i].y][_player[i].x] = i + 'a';
			_player[i].y = m[i].first;
			_player[i].x = m[i].second;
		}
		_map[_player[i].y][_player[i].x] = i + 'A';
		_hist[i].push_back(_at[i]);
	}

	/* ************** PRINT MAP ****************** */
	for (size_t i = 0; i < _height; i++)
		std::cout << _map[i] << std::endl;
	/* ************** PRINT MAP ****************** */
	/* ************** PRINT MOVES **************** */
	for (int i = 0; i < _pn; i++)
		std::cout << "Player " << i + 1 << " "
		<< _moves[_at[i] - 1] << std::endl;
	std::cout << std::endl;
	/* ************** PRINT MOVES **************** */
}

void	OCW::end(void)
{
	int		count[4] = {0};
	int		winner = 0;

	for (size_t i = 0; i < _height; i++)
	{
		for (size_t j = 0; j < _width; j++)
		{
			if (_map[i][j] == 'a' || _map[i][j] == 'A')
				count[0]++;
			else if (_map[i][j] == 'b' || _map[i][j] == 'B')
				count[1]++;
			else if (_map[i][j] == 'c' || _map[i][j] == 'C')
				count[2]++;
			else if (_map[i][j] == 'd' || _map[i][j] == 'D')
				count[3]++;
		}
	}

	/* *********** PRINT RESULT ************** */
	std::cout << "Final Score: " << std::endl;
	for (int i = 0; i < _pn; i++)
	{
		std::cout << _player[i].name << ": " << count[i] << std::endl;
		if (count[i] > count[winner])
			winner = i;
	}
	std::cout << "Winner: " << _player[winner].name << std::endl;
	/* *********** PRINT RESULT ************** */
}
