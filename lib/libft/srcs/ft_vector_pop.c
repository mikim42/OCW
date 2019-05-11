/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vector_pop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mingyun Kim <mikim@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 20:54:49 by Mingyun K         #+#    #+#             */
/*   Updated: 2018/02/02 21:29:12 by Mingyun K        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_vec_pop_index(t_vec *vec, size_t index)
{
	void	*pop;

	if (!vec || !vec->content || index >= vec->size ||
		!(pop = ft_memdup(&vec->content[vec->content_size * index],
		vec->content_size)))
		return (NULL);
	ft_memmove(&vec[vec->content_size * index],
				&vec[vec->content_size * index + 1],
				vec->content_size * (vec->size - (index + 1)));
	if (realloc(vec->content, vec->content_size * (vec->size)))
		ft_bzero(&vec->content[vec->content_size * --vec->size],
				vec->content_size);
	return (pop);
}

void	*ft_vec_pop_back(t_vec *vec)
{
	void	*pop;

	if (!vec || !vec->content || 
		!(pop = ft_memdup(&vec->content[vec->content_size * (vec->size - 1)],
		vec->content_size)))
		return (NULL);
	if (!realloc(vec->content, vec->content_size * (vec->size)))
	{
		free(pop);
		return (NULL);
	}
	ft_bzero(&vec->content[vec->content_size * --vec->size],
			vec->content_size);
	return (pop);
}

void	*ft_vec_pop_front(t_vec *vec)
{
	t_vec	*new_vec;
	void	*pop;

	if (!vec || !vec->content || 
		!(pop = ft_memdup(&vec->content[0], vec->content_size)))
		return (NULL);
	if (!(new_vec = ft_memalloc(sizeof(t_vec))))
	{
		free(pop);
		return (NULL);
	}
	if (!(new_vec->content = malloc(vec->content_size * vec->size)))
	{
		free(pop);
		free(new_vec);
		return (NULL);
	}
	ft_memcpy(new_vec->content, &vec->content[vec->content_size],
				vec->content_size * (vec->size - 1));
	new_vec->size = vec->size - 1;
	new_vec->content_size = vec->content_size;
	free(vec);
	vec = new_vec;
	return (pop);
}
