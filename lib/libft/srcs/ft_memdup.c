/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mingyun Kim <mikim@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 14:53:40 by Mingyun K         #+#    #+#             */
/*   Updated: 2018/02/01 15:00:25 by Mingyun K        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memdup(const void *src, size_t size)
{
	char	*tmp;
	char	*dst;
	size_t	i;

	if (!(dst = malloc(size)))
		return (NULL);
	tmp = (char*)src;
	i = -1;
	while (++i < size)
		dst[i] = tmp[i];
	return (dst);
}
