/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:05:02 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/09 19:54:34 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	read_here_doc(t_pipex *heredoc, char *limiter, t_data *db)
{
	char	*str;
	char	*lim;
	char	*line;
	char	*new;

	lim = ft_strjoin(limiter, "\n");
	heredoc->infile = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	new = NULL;
	while (1)
	{
		write(1, "> ", 2);
		str = get_next_line(0);
		if (!str || ft_strcmp(lim, str) == 0)
		{
			if (ft_strcmp(str, "\0") == 0)
			{
				write(1, "\nwarning: here-document at line ", 33);
				line = ft_itoa(db->command_count);
				write(1, line, ft_strlen(line));
				free(line);
				write(1, " delimited by end-of-file (wanted `", 36);
				write(1, limiter, ft_strlen(limiter));
				write(1, "')\n", 3);
			}
			free(str);
			break ;
		}
		new = dollar_in_line(str, db);
		write(heredoc->infile, new, ft_strlen(new));
		free(new);
		free(str);
	}
	free(lim);
	close(heredoc->infile);
	heredoc->infile = open(TMP_FILE, O_RDONLY);
	unlink(TMP_FILE);
}
