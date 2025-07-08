/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:01:23 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/08 16:39:07 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signals.h"

static void	handling_signal(int signal)
{
	// if (signal == SIGQUIT)
	(void)signal;
	// else if (signal == SIGINT)
	printf("\nurishshell: ");
}

void	heredoc_case(int signal)
{
	(void)signal;
	ERR_NO = 130;
	exit(ERR_NO);
}

void	handle_exec(int signal)
{
	if (signal == SIGQUIT)
		printf("Quit (core dumped)\n");
	else
		printf("\n");
}

void	init_signal(void)
{
	signal(SIGINT, &handling_signal);
	signal(SIGQUIT, SIG_IGN);
}
