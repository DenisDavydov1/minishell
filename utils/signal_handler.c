/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 22:51:58 by odhazzar          #+#    #+#             */
/*   Updated: 2020/10/21 23:51:40 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int sn)
{
	if (write(1, "\b\b  \n", 5) < 0)
		return ;
	write(1, "minishell-1.0$ ", 15);
	signal(SIGINT, sigint_handler);
}

void	sigquit_handler(int sn)
{
	if (write(1, "\b\b  \b\b", 6) < 0)
		return ;
	return ;
}
