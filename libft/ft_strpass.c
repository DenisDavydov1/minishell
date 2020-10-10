/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpass.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <abarbie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 22:47:12 by abarbie           #+#    #+#             */
/*   Updated: 2020/06/13 22:52:30 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strpass(const char *s, int c)
{
	int i;
	int size;

	i = 0;
	size = (int)ft_strlen(s);
	while (i < size && s[i] == (char)c)
		i++;
	return ((char *)&s[i]);
}
