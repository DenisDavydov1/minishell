/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <abarbie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 22:44:39 by abarbie           #+#    #+#             */
/*   Updated: 2020/09/28 16:19:48 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *nptr)
{
	long long int	num;
	int				sign;

	num = 0;
	sign = 1;
	while ((9 <= *nptr && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		if (*nptr++ == '-')
			sign = -1;
	while (ft_isdigit(*nptr))
	{
		if (num * 10 + *nptr - '0' < num)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		else
			num = num * 10 + *nptr++ - '0';
	}
	return ((int)(num * sign));
}
