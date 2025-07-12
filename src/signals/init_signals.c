/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 16:01:23 by miaghabe          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/08 19:37:14 by miaghabe         ###   ########.fr       */
=======
/*   Updated: 2025/07/12 16:01:48 by miaghabe         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */


#include "../includes/signals.h"

static void	handling_signal(int signal)
{
	if (signal == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		if (ERR_NO)
			 rl_redisplay();
	}
}

void	init_signal(void)
{
	signal(SIGINT, &handling_signal);
	signal(SIGQUIT, SIG_IGN);
}
