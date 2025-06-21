/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:12:32 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/21 18:49:58 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/tokenization.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

void	init_tokens(char *line, t_data *data_base)
{
	int	i;

	i = 0;
	while (ft_isspace(*line) == 1)
		line++;
	while (line[i])
	{ 
		check_quotes(); // stuguma "" ev '' ka te che
		open_dolar(); // $
		i++;
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	*data_base;

	while (1)
	{
		line = readline("entter command: ");
		if (line && *line != '\0')
		{
			init_tokens(line, data_base); // init anox funkcia
		}
		else
			free(line);
	}
}
