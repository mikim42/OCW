/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mingyun Kim <mikim@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 13:54:43 by Mingyun K         #+#    #+#             */
/*   Updated: 2018/02/20 08:58:52 by Mingyun K        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

bool	ft_vec_del(t_vec *vec, size_t index)
{
	bool	res;

	res = false;
	if (vec && vec->content && index >= vec->size)
		res = true;
	if (res)
	{
		ft_bzero(&vec->content[vec->content_size * index], vec->content_size);
		vec->content = realloc(vec->content, vec->content_size * (vec->size));
		ft_bzero(&vec->content[vec->content_size * (vec->size - 1)],
					vec->content_size);
		vec->size--;
	}
	return (res);
}

void	ft_vec_destroy(t_vec **vec)
{
	free((*vec)->content);
	free(*vec);
	*vec = NULL;
}

t_vec	*ft_vec_create(size_t content_size)
{
	t_vec	*vec;

	if (!content_size || !(vec = ft_memalloc(sizeof(t_vec))))
		return (NULL);
	vec->content_size = content_size;
	return (vec);
}

