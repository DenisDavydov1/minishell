/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandarin <danx@mail.ru>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 19:17:34 by mandarin          #+#    #+#             */
/*   Updated: 2020/05/03 19:17:34 by mandarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*out;

	if (!s)
		return (NULL);
	if (!f)
		return (ft_strdup(s));
	out = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!out)
		return (NULL);
	i = 0;
	while (s[i])
	{
		out[i] = f(i, (char)s[i]);
		i++;
	}
	return (out);
}
