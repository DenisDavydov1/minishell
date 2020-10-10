/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <danx@mail.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 20:33:02 by abarbie           #+#    #+#             */
/*   Updated: 2020/05/02 20:33:02 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char *ptr_s;

	ptr_s = (unsigned char *)s;
	while (n--)
		if (*(ptr_s++) == (unsigned char)c)
			return ((void *)(--ptr_s));
	return (NULL);
}
