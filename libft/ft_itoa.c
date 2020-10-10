/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandarin <danx@mail.ru>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 19:11:01 by mandarin          #+#    #+#             */
/*   Updated: 2020/05/03 19:11:01 by mandarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	num_len(int n, unsigned int *num, int *decade)
{
	int digits;
	int sign;

	*decade = 1;
	digits = 1;
	sign = 0;
	if (n < 0 && ++sign)
		*num = (unsigned int)n * (-1);
	else
		*num = (unsigned int)n;
	while (*num / *decade >= 10 && ++digits)
		*decade *= 10;
	return ((size_t)(sign + digits));
}

char			*ft_itoa(int n)
{
	char			*out;
	char			*ptr;
	unsigned int	num;
	int				decade;

	out = (char *)ft_calloc(num_len(n, &num, &decade) + 1, sizeof(char));
	if (!out)
		return (NULL);
	ptr = out;
	if (n < 0)
		*ptr++ = '-';
	while (decade > 0)
	{
		*ptr++ = num / decade + '0';
		num %= decade;
		decade /= 10;
	}
	return (out);
}
