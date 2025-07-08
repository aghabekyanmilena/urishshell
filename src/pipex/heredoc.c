/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:05:02 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/08 20:35:34 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	read_here_doc(t_pipex *heredoc, char *limiter, t_data *db)
{
	char	*str;
	char	*lim;
	char	*line;
	t_token	token;
	int		i;

	lim = ft_strjoin(limiter, "\n");
	heredoc->infile = open(TMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	while (1)
	{
		write(1, "> ", 2);
		str = get_next_line(0);
		if (ft_strcmp(str, "\0") == 0 || ft_strcmp(lim, str) == 0)
		{
			if (ft_strcmp(str, "\0") == 0)
			{
				line = "\nwarning: here-document at line ";
				write(1, line, ft_strlen(line));
				line = ft_itoa(db->command_count);
				write(1, line, ft_strlen(line));
				free(line);
				line = " delimited by end-of-file (wanted `";
				write(1, line, ft_strlen(line));
				write(1, limiter, ft_strlen(limiter));
				write(1, "')\n", 3);
			}
			free(str);
			break ;
		}
		token.value = ft_strdup(str);
		i = 0;
		while (token.value[i])
			check_dollar_existance(&token, db, &i);
		write(heredoc->infile, token.value, ft_strlen(token.value));
		free(token.value);
		free(str);
	}
	close(heredoc->infile);
	heredoc->infile = open(TMP_FILE, O_RDONLY);
}
