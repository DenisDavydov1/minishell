/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandarin <danx@mail.ru>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 16:13:57 by mandarin          #+#    #+#             */
/*   Updated: 2020/05/03 16:13:57 by mandarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*out;
	size_t	s1_s;
	size_t	s2_s;

	if (!s1 || !s2)
		return (NULL);
	s1_s = ft_strlen(s1);
	s2_s = ft_strlen(s2);
	out = (char *)ft_calloc(s1_s + s2_s + 1, sizeof(char));
	if (!out)
		return (NULL);
	ft_strlcat(out, s1, s1_s + 1);
	ft_strlcat(out, s2, s1_s + s2_s + 1);
	return (out);
}
