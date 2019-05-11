/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_push.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mingyun Kim <mikim@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 20:54:14 by Mingyun K         #+#    #+#             */
/*   Updated: 2018/02/03 15:15:14 by Mingyun K        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

bool	ft_vec_push_index(t_vec *vec, void *elem, size_t index)
{
	bool	res;

	res = false;
	if (vec && elem && vec->content && index < vec->size)
		res = realloc(vec->content, vec->content_size * (vec->size + 2));
	if (res)
	{
		ft_bzero(&vec->content[vec->content_size * (vec->size + 1)],
					vec->content_size);
		ft_memmove(&vec->content[vec->content_size * (index + 1)],
					&vec->content[vec->content_size * index],
					vec->content_size * (vec->size - index));
		ft_memcpy(&vec->content[vec->content_size * index], elem,
					vec->content_size);
		vec->size++;
	}
	return (res);
}

bool	ft_vec_push_front(t_vec *vec, void *elem)
{
	bool	res;

	res = false;
	if (vec && vec->content)
		res = realloc(vec->content, vec->content_size * (vec->size + 2));
	else if (vec)
	{
		vec->content = ft_memalloc(vec->content_size * 2);
		res = true;
	}
	if (res)
	{
		ft_bzero(&vec->content[vec->content_size * vec->size],
					vec->content_size);
		ft_memmove(&vec->content[vec->content_size * 1], &vec->content[0],
					vec->content_size * vec->size);
		ft_memcpy(&vec->content[0], elem, vec->content_size);
		vec->size++;
	}
	return (res);
}

bool	ft_vec_push_back(t_vec *vec, void *elem)
{
	bool	res;

	res = false;
	if (vec && vec->content)
		res = realloc(vec->content, vec->content_size * (vec->size + 2));
	else if (vec)
	{
		vec->content = ft_memalloc(vec->content_size * 2);
		res = true;
	}
	if (res)
	{
		ft_bzero(&vec->content[vec->content_size * vec->size],
					vec->content_size);
		ft_memcpy(&vec->content[vec->content_size * vec->size],
					elem, vec->content_size);
		vec->size++;
	}
	return (res);
}
