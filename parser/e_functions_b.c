/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_functions_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarbie <abarbie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:35:24 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 01:43:14 by abarbie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *e_strjoin(char *s1, char *s2)
{
	char *out;
	
	if (!(out = ft_strjoin((char const *)s1, (char const *)s2)))
		throw_error(MEMALLOC, NULL);
	return (out);
}

char *e_itoa(int n)
{
	char *out;
	
	if (!(out = ft_itoa(n)))
		throw_error(MEMALLOC, NULL);
	return (out);
}
