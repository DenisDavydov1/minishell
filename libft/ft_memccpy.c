/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <danx@mail.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 20:21:36 by abarbie           #+#    #+#             */
/*   Updated: 2020/05/02 20:21:36 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char *s;

	if (dest == NULL && src == NULL)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (*s != (unsigned char)c && n--)
		*d++ = *s++;
	if (*s == (unsigned char)c && n > 0)
	{
		*d = *s;
		return (void *)(d + 1);
	}
	else
		return (NULL);
}
