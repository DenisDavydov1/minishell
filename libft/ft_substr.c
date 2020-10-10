/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandarin <danx@mail.ru>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 16:13:26 by mandarin          #+#    #+#             */
/*   Updated: 2020/05/03 16:13:26 by mandarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*out;
	size_t	s_size;

	if (!s)
		return (NULL);
	s_size = ft_strlen(s);
	if (s_size < (size_t)start)
		return (ft_strdup(""));
	if (((size_t)start + len) > s_size + 1)
		len = s_size - (size_t)start + 1;
	out = (char *)malloc(sizeof(char) * (len + 1));
	if (!out)
		return (NULL);
	ft_strlcpy(out, &s[start], len + 1);
	return (out);
}
