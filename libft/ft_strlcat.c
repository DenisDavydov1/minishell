/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <danx@mail.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 22:19:32 by abarbie           #+#    #+#             */
/*   Updated: 2020/05/02 22:19:32 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t dst_len;

	i = 0;
	dst_len = 0;
	while (dst[dst_len] && size > 0)
	{
		dst_len++;
		size--;
	}
	while (src[i] && size > 1)
	{
		dst[dst_len + i] = src[i];
		i++;
		size--;
	}
	if (size == 1 || src[i] == '\0')
	{
		dst[dst_len + i] = '\0';
	}
	return (dst_len + ft_strlen(src));
}
