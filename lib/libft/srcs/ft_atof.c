/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mikim <mikim@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 15:37:05 by mikim             #+#    #+#             */
/*   Updated: 2018/01/07 12:42:18 by mikim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static double	ft_atof_prec(const char *s)
{
	double	n;
	double	prec;

	n = 0;
	prec = 0.1;
	while (*s >= '0' && *s <= '9')
	{
		n += prec * (*s - 48);
		prec /= 10;
	}
	return (n);
}

double			ft_atof(const char *s)
{
	double	n;
	int		np;

	np = 1;
	n = 0;
	while (*s == '\t' || *s == ' ' || *s == '\n' ||
			*s == '\r' || *s == '\v' || *s == '\f')
		++s;
	*s == '-' ? np = -1 : 0;
	*s == '-' || *s == '+' ? ++s : 0;
	while (*s >= '0' && *s <= '9')
	{
		n *= 10;
		n += *s - 48;
		++s;
	}
	if (*s == '.')
		n += ft_atof_prec(s + 1);
	return (n * np);
}
