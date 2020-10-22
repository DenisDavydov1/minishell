/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   e_functions_a.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:35:22 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 09:24:00 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*e_malloc(size_t size)
{
	void *out;

	if (!(out = malloc(size)))
		throw_error(MEMALLOC, NULL);
	return (out);
}

void	*e_calloc(size_t nmemb, size_t size)
{
	void *out;

	if (!(out = ft_calloc(nmemb, size)))
		throw_error(MEMALLOC, NULL);
	return (out);
}

char	*e_strdup(char *s)
{
	char *out;

	if (!(out = ft_strdup(s)))
		throw_error(MEMALLOC, NULL);
	return (out);
}

char	**e_split(char *s, char c)
{
	char **out;

	if (!(out = ft_split(s, c)))
		throw_error(MEMALLOC, NULL);
	return (out);
}

char	*e_substr(char *s, int start, int len)
{
	char *out;

	if (!(out = ft_substr((char const *)s, (unsigned int)start, (size_t)len)))
		throw_error(MEMALLOC, NULL);
	return (out);
}
