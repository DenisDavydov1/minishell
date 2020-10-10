/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <danx@mail.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 20:36:54 by abarbie           #+#    #+#             */
/*   Updated: 2020/05/02 20:36:54 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char *p1;
	const char *p2;

	if (!n)
		return (0);
	p1 = (char *)s1;
	p2 = (char *)s2;
	while (*p1 == *p2)
	{
		n--;
		p1++;
		p2++;
		if (!n)
			return (0);
	}
	return ((int)((unsigned char)*p1 - (unsigned char)*p2));
}
