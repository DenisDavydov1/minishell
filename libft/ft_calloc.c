/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <danx@mail.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 23:01:35 by abarbie           #+#    #+#             */
/*   Updated: 2020/05/02 23:01:35 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char			*mem;
	unsigned int	i;

	if ((nmemb && SIZE_MAX / nmemb < size) || \
		(size && SIZE_MAX / size < nmemb))
		return (NULL);
	if (!(mem = (char *)malloc(nmemb * size)))
		return (NULL);
	i = 0;
	while (i < (nmemb * size))
	{
		mem[i] = '\0';
		i++;
	}
	return (mem);
}
