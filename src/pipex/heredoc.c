/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:14:20 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/19 19:10:33 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	whilei_mejiny(t_limiter *cpy, t_pipex *pipex, t_data *db, char *lim)
{
	char	*str;
	char	*line;
	char	*new;

	new = NULL;
	write(1, "> ", 2);
	str = get_next_line(0);
	db->command_count++;
	if (!str || ft_strcmp(lim, str) == 0)
	{
		if (!str)
		{
			write(1, "\nwarning: here-document at line ", 33);
			line = ft_itoa(db->command_count);
			write(1, line, ft_strlen(line));
			free(line);
			write(1, " delimited by end-of-file (wanted `", 36);
			write(1, cpy->value, ft_strlen(cpy->value));
			write(1, "')\n", 3);
		}
		return (free(str), 1);
	}
	new = dollar_in_line(str, db);
	write(pipex->infile, new, ft_strlen(new));
	return (free(new), free(str), 0);
}

void	read_here_doc(t_pipex *pipex, t_limiter *cpy, t_data *db)
{
	char		*lim;

	while (cpy)
	{
		lim = ft_strjoin(cpy->value, "\n");
		pipex->infile = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0600);
		while (1)
		{
			if (whilei_mejiny(cpy, pipex, db, lim))
				break ;
		}
		free(lim);
		close(pipex->infile);
		pipex->infile = open(TMP_FILE, O_RDONLY);
		unlink(TMP_FILE);
		cpy = cpy->next;
	}
}
