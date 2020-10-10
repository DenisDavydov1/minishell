/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mandarin <danx@mail.ru>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/03 19:29:17 by mandarin          #+#    #+#             */
/*   Updated: 2020/05/03 19:29:17 by mandarin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;
	int				decade;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num = (unsigned int)(n * (-1));
	}
	else
		num = (unsigned int)n;
	decade = 1;
	while (num / decade >= 10)
		decade *= 10;
	while (decade > 0)
	{
		ft_putchar_fd((char)(num / decade + '0'), fd);
		num %= decade;
		decade /= 10;
	}
}
