/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:05:02 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/03 17:29:41 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	read_here_doc(t_pipex *heredoc, char *limiter)
{
	char	*str;

	heredoc->infile = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	// if (heredoc->infile < 0)
	// error handle
	while (1)
	{
		str = readline("> ");
		if (!str || ft_strcmp(limiter, str) == 0)
		{
			free(str);
			break;
		}
		write(heredoc->infile, str, ft_strlen(str));
		write(heredoc->infile, "\n", 1);
		free(str);
	}
	close(heredoc->infile);
	heredoc->infile = open(TMP_FILE, O_RDONLY);
	// if (heredoc->infile < 0)
	// error handle
}
