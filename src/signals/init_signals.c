/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:01:23 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/05 16:58:17 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/signals.h"

static void	handling_signal(int signal)
{
	if (signal == SIGQUIT)
		(void)0;
	else if (signal == SIGINT)
		printf("\nminishell: ");
}

void	heredoc_case(int signal)
{
	
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
