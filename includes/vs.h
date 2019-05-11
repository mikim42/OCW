/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vs.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 20:49:48 by mikim             #+#    #+#             */
/*   Updated: 2019/05/10 14:51:55 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                              Mingyun Kim   */
/*                                           https://www.github.com/mikim42   */
/* ************************************************************************** */

#ifndef _VS_H_
# define _VS_H_

# include <libft.h>
# include <mlx.h>

typedef	struct	s_data
{
	char		*player[4];
	char		*hist[4][4];
	int			pn;
	int			wid;
	int			hgt;
	int			win_x;
	int			win_y;
	double		diff_x;
	double		diff_y;
	void		*mlx;
	void		*win;
	int			wall;
}				t_data;

typedef	struct	s_mlx
{
}				t_mlx;

#endif
