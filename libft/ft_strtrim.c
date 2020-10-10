/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandarin <danx@mail.ru>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 16:54:16 by mandarin          #+#    #+#             */
/*   Updated: 2020/05/03 16:54:16 by mandarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		in_set(char c, char const *set)
{
	int set_size;

	set_size = ft_strlen(set);
	while (set_size--)
	{
		if (c == set[set_size])
			return (1);
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*out;
	int		b;
	int		e;

	if (!s1)
		return (NULL);
	b = 0;
	e = ft_strlen((const char *)s1) - 1;
	while (b < e && in_set(s1[b], set))
		b++;
	while (e > b - 1 && in_set(s1[e], set))
		e--;
	if (b > e)
		return (ft_strdup(""));
	out = (char *)ft_calloc(e - b + 2, sizeof(char));
	if (!out)
		return (NULL);
	ft_strlcpy(out, (const char*)&s1[b], e - b + 2);
	return (out);
}
