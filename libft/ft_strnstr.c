/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <danx@mail.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 22:35:44 by abarbie           #+#    #+#             */
/*   Updated: 2020/05/02 22:35:44 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t i;
	size_t little_len;
	size_t big_len;

	i = 0;
	little_len = ft_strlen(little);
	big_len = ft_strlen(big);
	while (i < big_len + 1 && i + little_len <= len)
	{
		if (!(ft_memcmp(&big[i], little, little_len)))
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
