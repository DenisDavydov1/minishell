/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <danx@mail.ru>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 22:56:36 by abarbie           #+#    #+#             */
/*   Updated: 2020/05/02 22:56:36 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*out;

	out = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!out)
		return (NULL);
	i = 0;
	while (s[i])
	{
		out[i] = s[i];
		i++;
	}
	out[i] = '\0';
	return (out);
}
