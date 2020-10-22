/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_validity_a.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 23:39:33 by abarbie           #+#    #+#             */
/*   Updated: 2020/10/22 09:40:46 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	split_validity_less(char **s)
{
	if (!*s)
		return (0);
	if (**s == '<' || **s == ';')
		return (0);
	if (**s == '>')
	{
		if (split_validity_skip(s + 1))
			return (2);
		else
			return (0);
	}
	else if (**s == ' ')
		return (split_validity_skip(s));
	return (1);
}

static int	split_validity_greater(char **s)
{
	if (!*s)
		return (0);
	if (**s == '<' || **s == ';')
		return (0);
	else if (**(s) == '>' && **(s + 1) == '>')
		return (0);
	else if (**s == ' ')
		return (split_validity_skip(s));
	return (1);
}

static int	split_validity_semicolon(char **s)
{
	if (!*s)
		return (1);
	while (*s && **s == ' ')
		s++;
	if (*s && **s == ';')
		return (0);
	return (1);
}

static int	split_validity_pipe(char **s)
{
	if (!*s)
		return (0);
	while (*s && **s == ' ')
		s++;
	if (*s && (**s == '|' || **s == ';'))
		return (0);
	return (1);
}

int			split_validity(char **s)
{
	while (*s)
	{
		if (**s == '<' && split_validity_less(s + 1) == 2)
			s++;
		else if (**s == '<' && !split_validity_less(s + 1))
			return (0);
		else if (**s == '>' && !split_validity_greater(s + 1))
			return (0);
		else if (**s == ';' && !split_validity_semicolon(s + 1))
			return (0);
		else if (**s == '|' && !split_validity_pipe(s + 1))
			return (0);
		s++;
	}
	return (1);
}
