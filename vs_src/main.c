/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:49:08 by mikim             #+#    #+#             */
/*   Updated: 2019/05/10 18:07:54 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                              Mingyun Kim   */
/*                                           https://www.github.com/mikim42   */
/* ************************************************************************** */

#include <vs.h>

void	draw_up(double i, double j, double diff, t_data *data)
{
	for (int y = 2; y < diff - 2; y++)
	{
		for (int x = 2; x < diff - 2; x++)
		{
			if (y < diff / 2 && diff / 2 - y <= x && x <= diff / 2 + y)
				mlx_pixel_put(data->mlx, data->win, x + j, y + i, 0xFFFFDF);
			else if (y >= diff / 2 && diff / 3 <= x && x <= 2 * diff / 3)
				mlx_pixel_put(data->mlx, data->win, x + j, y + i, 0xFFFFDF);
			else
				mlx_pixel_put(data->mlx, data->win, x + j, y+ i, 0x000000);
		}
	}
}

void	draw_down(double i, double j, double diff, t_data *data)
{
	for (int y = 2; y < diff - 2; y++)
	{
		for (int x = 2; x < diff - 2; x++)
		{
			if (y > diff / 2 && y - (diff / 2) <= x && x <= diff - (y - (diff / 2)))
				mlx_pixel_put(data->mlx, data->win, x + j, y + i, 0xFFFFDF);
			else if (y <= diff / 2 && diff / 3 <= x && x <= 2 * diff / 3)
				mlx_pixel_put(data->mlx, data->win, x + j, y + i, 0xFFFFDF);
			else
				mlx_pixel_put(data->mlx, data->win, x + j, y+ i, 0x000000);
		}
	}
}

void	draw_left(double i, double j, double diff, t_data *data)
{
	for (int y = 2; y < diff - 2; y++)
	{
		for (int x = 2; x < diff - 2; x++)
		{
			if (x <= diff / 2 && diff / 2 - x <= y && y <= diff / 2 + x)
				mlx_pixel_put(data->mlx, data->win, x + j, y + i, 0xFFFFDF);
			else if (x >= diff / 2 && diff / 3 <= y && y <= 2 * diff / 3)
				mlx_pixel_put(data->mlx, data->win, x + j, y + i, 0xFFFFDF);
			else
				mlx_pixel_put(data->mlx, data->win, x + j, y+ i, 0x000000);
		}
	}
}

void	draw_right(double i, double j, double diff, t_data *data)
{
	for (int y = 2; y < diff - 2; y++)
	{
		for (int x = 2; x < diff - 2; x++)
		{
			if (x >= diff / 2 && x - (diff / 2) <= y && y <= 3 * diff / 2 - x)
				mlx_pixel_put(data->mlx, data->win, x + j, y + i, 0xFFFFDF);
			else if (x <= diff / 2 && diff / 3 <= y && y <= 2 * diff / 3)
				mlx_pixel_put(data->mlx, data->win, x + j, y + i, 0xFFFFDF);
			else
				mlx_pixel_put(data->mlx, data->win, x + j, y+ i, 0x000000);
		}
	}
}

void	draw_skip(double i, double j, double diff, t_data *data)
{
	for (int y = 2; y < diff - 2; y++)
	{
		for (int x = 2; x < diff - 2; x++)
		{
			if (FT_SQR(diff / 3) >= FT_SQR(diff / 2 - y) + FT_SQR(diff / 2 - x))
				mlx_pixel_put(data->mlx, data->win, x + j, y + i, 0x0000FF);
			else
				mlx_pixel_put(data->mlx, data->win, x + j, y+ i, 0x000000);
		}
	}
}

void	draw_coll(double i, double j, double diff, t_data *data)
{
	for (int y = 2; y < diff - 2; y++)
	{
		for (int x = 2; x < diff - 2; x++)
		{
			if (y >= diff / 5 && y <= 4 * diff / 5 &&
				(FT_ABS(diff / 2 - x) * 1.5) <= y - diff / 4)
				mlx_pixel_put(data->mlx, data->win, x + j, y + i, 0xFF0000);
			else
				mlx_pixel_put(data->mlx, data->win, x + j, y+ i, 0x000000);
		}
	}
}

int		key_hook(int keycode)
{
	if (keycode == 53)
		exit(0);
	return (0);
}

int		main()
{
	t_data	data;
	char	*line;
	char	**split;

	bzero(&data, sizeof(t_data));

	/* SKIP LOADING STATUS */
	for (int i = 0; i < 5; i++)
	{
		get_next_line(0, &line);
		ft_strdel(&line);
	}

	/* SET GAME DATA */
	get_next_line(0, &line);
	split = ft_strsplit(line, ' ');
	data.pn = ft_atoi(split[1]);
	ft_splitdel(split);
	ft_strdel(&line);
	for (int i = 0; i < data.pn; i++)
	{
		get_next_line(0, &line);
		split = ft_strsplit(line, ' ');
		data.player[i] = ft_strdup(split[2]);
		ft_splitdel(split);
		ft_strdel(&line);
	}
	get_next_line(0, &line);
	split = ft_strsplit(line, ' ');
	data.wid = ft_atoi(split[1]);
	data.hgt = ft_atoi(split[2]);
	ft_splitdel(split);
	ft_strdel(&line);

	/* SET GRAPHICS */
	data.mlx = mlx_init();
	data.win_x = 1200;
	data.win_y = 800;
	data.win = mlx_new_window(data.mlx, data.win_x, data.win_y, "Ohlone Conqueror's War");
	data.diff_x = (data.win_y - 100) / data.wid;
	data.diff_y = (data.win_y - 100) / data.hgt;

	mlx_string_put(data.mlx, data.win, data.win_y - 30, 15, 0xFFFFDF, "Player 1:");
	mlx_string_put(data.mlx, data.win, data.win_y - 30, 35, 0xFFFFDF, "Move:");
	mlx_string_put(data.mlx, data.win, data.win_y - 30, 15 + (data.win_y / 4),
					0xFFFFDF, "PLayer 2:");
	mlx_string_put(data.mlx, data.win, data.win_y - 30, 35 + (data.win_y / 4),
					0xFFFFDF, "Move:");
	mlx_string_put(data.mlx, data.win, data.win_y - 30, 15 + 2 * (data.win_y / 4),
					0xFFFFDF, "Player 3:");
	mlx_string_put(data.mlx, data.win, data.win_y - 30, 35 + 2 * (data.win_y / 4),
					0xFFFFDF, "Move:");
	mlx_string_put(data.mlx, data.win, data.win_y - 30, 15 + 3 * (data.win_y / 4),
					0xFFFFDF, "Player 4:");
	mlx_string_put(data.mlx, data.win, data.win_y - 30, 35 + 3 * (data.win_y / 4),
					0xFFFFDF, "Move:");

	if (data.player[0])
		mlx_string_put(data.mlx, data.win, data.win_y + 70, 15, 0xFF0000, data.player[0]);
	else
		mlx_string_put(data.mlx, data.win, data.win_y + 70, 15, 0xFFFFDF, "NONE");
	if (data.player[1])
		mlx_string_put(data.mlx, data.win, data.win_y + 70, 15 + (data.win_y / 4), 0x00FF00, data.player[1]);
	else
		mlx_string_put(data.mlx, data.win, data.win_y + 70, 15 + (data.win_y / 4), 0xFFFFDF, "NONE");
	if (data.player[2])
		mlx_string_put(data.mlx, data.win, data.win_y + 70, 15 + 2 * (data.win_y / 4), 0x0000FF, data.player[2]);
	else
		mlx_string_put(data.mlx, data.win, data.win_y + 70, 15 + 2 * (data.win_y / 4), 0xFFFFDF, "NONE");
	if (data.player[3])
		mlx_string_put(data.mlx, data.win, data.win_y + 70, 15 + 3 * (data.win_y / 4), 0xFFF000, data.player[3]);
	else
		mlx_string_put(data.mlx, data.win, data.win_y + 70, 15 + 3 * (data.win_y / 4), 0xFFFFDF, "NONE");

	for (int i = 50; i <= (50 + data.diff_y * data.hgt); i += data.diff_y)
		for (int j = 50; j <= (50 + data.diff_y * data.wid); j++)
			mlx_pixel_put(data.mlx, data.win, j, i, 0xFFFFFF);
	for (int i = 50; i <= (50 + data.diff_y * data.hgt); i++)
		for (int j = 50; j <= (50 + data.diff_y * data.wid); j += data.diff_x)
			mlx_pixel_put(data.mlx, data.win, j, i, 0xFFFFFF);

	mlx_do_sync(data.mlx);
	sleep(2);

	/* READ TURN */
	char	map[data.hgt + 1][data.wid + 1];
	int		seg = 0;

	while (get_next_line(0, &line))
	{
		char	*turn;

		ft_strdel(&line);
		seg = 0;
		get_next_line(0, &turn);
		for (int i = 0; i < data.pn; i++)
		{
			if (!get_next_line(0, &line))
			{
				seg = i;
				break ;
			}
			if (!ft_strncmp(turn, "Final", 5))
			{
				seg = -1;
				break ;
			}
			ft_strdel(&line);
		}
		if (seg < 0)
		{
			int	score[4];

			bzero(&score, sizeof(int) * 4);
			for (int i = 0; i < data.hgt; i++)
				for (int j = 0; j < data.wid; j++)
				{
					if (map[i][j] == 'a' || map[i][j] == 'A')
						score[0]++;
					else if (map[i][j] == 'b' || map[i][j] == 'B')
						score[1]++;
					else if (map[i][j] == 'c' || map[i][j] == 'C')
						score[2]++;
					else if (map[i][j] == 'd' || map[i][j] == 'D')
						score[3]++;
				}
			mlx_string_put(data.mlx, data.win, data.win_y + 150, 35, 0xFFFFDF, "Score:");
			mlx_string_put(data.mlx, data.win, data.win_y + 250, 35, 0xFF0000, ft_itoa(score[0]));
			mlx_string_put(data.mlx, data.win, data.win_y + 150, 35 + (data.win_y / 4),
					0xFFFFDF, "Score: ");
			mlx_string_put(data.mlx, data.win, data.win_y + 250, 35 + (data.win_y / 4),
					0x00FF00, ft_itoa(score[1]));
			if (data.pn >= 3)
			{
				mlx_string_put(data.mlx, data.win, data.win_y + 150, 35 + 2 * (data.win_y / 4),
						0xFFFFDF, "Score: ");
				mlx_string_put(data.mlx, data.win, data.win_y + 250, 35 + 2 * (data.win_y / 4),
						0x0000FF, ft_itoa(score[2]));
			}
			if (data.pn >= 4)
			{
			mlx_string_put(data.mlx, data.win, data.win_y + 150, 35 + 3 * (data.win_y / 4),
					0xFFFFDF, "Score:");
			mlx_string_put(data.mlx, data.win, data.win_y + 250, 35 + 3 * (data.win_y / 4),
					0xFFF000, ft_itoa(score[3]));
					}
			break ;
		}
		else if (seg != 0)
		{
			if (seg == 1)
				mlx_string_put(data.mlx, data.win, data.win_y + 250, 35, 0xFF0000, "ERROR!");
			if (seg == 2)
				mlx_string_put(data.mlx, data.win, data.win_y + 250, 35 + (data.win_y / 4),
						0x00FF00, "ERROR!");
			if (seg == 3)
				mlx_string_put(data.mlx, data.win, data.win_y + 250, 35 + 2 * (data.win_y / 4),
						0x0000FF, "ERROR!");
			if (seg == 4)
				mlx_string_put(data.mlx, data.win, data.win_y + 250, 35 + 3 * (data.win_y / 4),
						0xFFF000, "ERROR!");
			break ;
		}
		else
		{
			for (int i = 0; i < data.hgt; i++)
			{
				get_next_line(0, &line);
				strcpy(map[i], line);
				ft_strdel(&line);
			}
			for (int i = 0; i < data.pn; i++)
			{
				if (data.hist[i][3])
					ft_strdel(&data.hist[i][3]);
				data.hist[i][3] = data.hist[i][2];
				data.hist[i][2] = data.hist[i][1];
				data.hist[i][1] = data.hist[i][0];
			}
			for (int i = 0; i < data.pn; i++)
			{
				get_next_line(0, &line);
				split = ft_strsplit(line, ' ');
				data.hist[i][0] = ft_strdup(split[2]);
				ft_splitdel(split);
				ft_strdel(&line);
			}
		}
		if (data.wall == 0)
		{
			for (int i = 0; i < data.hgt; i++)
			{
				for (int j = 0; j < data.wid; j++)
				{
					if (map[i][j] == '*')
					{
						for (double y = 52 + data.diff_y * i; y < 49 + data.diff_y * (i + 1); y++)
							for (double x = 52 + data.diff_x * j; x < 49 + data.diff_y * (j + 1); x++)
									mlx_pixel_put(data.mlx, data.win, x, y, 0xFFFFAF);
					}
				}
			}
			data.wall = 1;
		}
		for (int i = 0; i < data.hgt; i++)
		{
			for (int j = 0; j < data.wid; j++)
			{
				if (map[i][j] == 'A')
				{
					for (double y = 52 + data.diff_y * i; y < 49 + data.diff_y * (i + 1); y++)
						for (double x = 52 + data.diff_x * j; x < 49 + data.diff_y * (j + 1); x++)
								mlx_pixel_put(data.mlx, data.win, x, y, 0xFF0000);
				}
				if (map[i][j] == 'B')
				{
					for (double y = 52 + data.diff_y * i; y < 49 + data.diff_y * (i + 1); y++)
						for (double x = 52 + data.diff_x * j; x < 49 + data.diff_y * (j + 1); x++)
								mlx_pixel_put(data.mlx, data.win, x, y, 0x00FF00);
				}
				if (map[i][j] == 'C')
				{
					for (double y = 52 + data.diff_y * i; y < 49 + data.diff_y * (i + 1); y++)
						for (double x = 52 + data.diff_x * j; x < 49 + data.diff_y * (j + 1); x++)
								mlx_pixel_put(data.mlx, data.win, x, y, 0x0000FF);
				}
				if (map[i][j] == 'D')
				{
					for (double y = 52 + data.diff_y * i; y < 49 + data.diff_y * (i + 1); y++)
						for (double x = 52 + data.diff_x * j; x < 49 + data.diff_y * (j + 1); x++)
								mlx_pixel_put(data.mlx, data.win, x, y, 0xFFFF00);
				}
			}
		}
		for (int i = 0; i < data.pn; i++)
		{
				if (!data.hist[i][0])
					continue ;
				if (!strcmp(data.hist[i][0], "UP"))
					draw_up(50 + (i * data.win_y / 4), 25 + data.win_y, data.win_y / 12, &data);
				if (!strcmp(data.hist[i][0], "DOWN"))
					draw_down(50 + (i * data.win_y / 4), 25 + data.win_y, data.win_y / 12, &data);
				if (!strcmp(data.hist[i][0], "LEFT"))
					draw_left(50 + (i * data.win_y / 4), 25 + data.win_y, data.win_y / 12, &data);
				if (!strcmp(data.hist[i][0], "RIGHT"))
					draw_right(50 + (i * data.win_y / 4), 25 + data.win_y, data.win_y / 12, &data);
				if (!strcmp(data.hist[i][0], "COLLISION"))
					draw_coll(50 + (i * data.win_y / 4), 25 + data.win_y, data.win_y / 12, &data);
				if (!strcmp(data.hist[i][0], "TIME_OUT"))
					draw_skip(50 + (i * data.win_y / 4), 25 + data.win_y, data.win_y / 12, &data);
		}
		for (int i = 0; i < data.pn; i++)
		{
			for (int j = 1; j < 4; j++)
			{
				if (!data.hist[i][j])
					continue ;
				if (!strcmp(data.hist[i][j], "UP"))
					draw_up(70 + (i * 2.0 * data.win_y / 8), (60 + 15 * (j - 1))
							+ (9 + (0.5 * (j - 1))) * data.win_y / 8, data.win_y / 16, &data);
				if (!strcmp(data.hist[i][j], "DOWN"))
					draw_down(70 + (i * 2.0 * data.win_y / 8), (60 + 15 * (j - 1))
							+ (9 + (0.5 * (j - 1))) * data.win_y / 8, data.win_y / 16, &data);
				if (!strcmp(data.hist[i][j], "LEFT"))
					draw_left(70 + (i * 2.0 * data.win_y / 8), (60 + 15 * (j - 1))
							+ (9 + (0.5 * (j - 1))) * data.win_y / 8, data.win_y / 16, &data);
				if (!strcmp(data.hist[i][j], "RIGHT"))
					draw_right(70 + (i * 2.0 * data.win_y / 8), (60 + 15 * (j - 1))
							+ (9 + (0.5 * (j - 1))) * data.win_y / 8, data.win_y / 16, &data);
				if (!strcmp(data.hist[i][j], "COLLISION"))
					draw_coll(70 + (i * 2.0 * data.win_y / 8), (60 + 15 * (j - 1))
							+ (9 + (0.5 * (j - 1))) * data.win_y / 8, data.win_y / 16, &data);
				if (!strcmp(data.hist[i][j], "TIME_OUT"))
					draw_skip(70 + (i * 2.0 * data.win_y / 8), (60 + 15 * (j - 1))
							+ (9 + (0.5 * (j - 1))) * data.win_y / 8, data.win_y / 16, &data);
			}
		}
		for (int i = 0; i <= 30; i++)
			for (int j = 10; j <= 100; j++)
				mlx_pixel_put(data.mlx, data.win, j, i, 0x000000);
		mlx_string_put(data.mlx, data.win, 10, 10, 0xFFFFDF, turn);
		ft_strdel(&turn);
		mlx_do_sync(data.mlx);
	}
	mlx_hook(data.win, 2, 2, key_hook, NULL);
	mlx_loop(data.mlx);
	return (0);
}
