/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 16:12:32 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/22 18:53:35 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/tokenization.h"

void	print_tokens(t_token *tok)
{
	while (tok)
	{
		printf("Type: %d, Value: %s\n", tok->type, tok->value);
		tok = tok->next;
	}
}

void	init_tokens(char *line, t_data *data_base, char **env)
{
	int		i;
	t_token	*head = NULL;
	t_token_type	type;

	i = 0;
	while (line[i])
	{
		while (ft_isspace(line[i]))
			i++;
		if (!line[i])
			break;
		if (line[i] == '\'' || line[i] == '"')
		{
			if (line[i] == '"')
				type = D_QUOTE;
			else
				type = S_QUOTE;
			add_token(&head, read_quoted_string(line, &i, env), type);
		}
		else if (line[i] == '|')
		{
			if (line[i + 1] == '|')
			{
				type = D_PIPE;
				i++;
			}
			else
				type = S_PIPE;
			add_token(&head, strdup("|"), type);
			i++;
		}
		else if (line[i] == '&')
		{
			if (line[i + 1] == '&')
			{
				type = D_AND;
				i++;
			}
			else
				type = S_AND;
			add_token(&head, strdup("&"), type);
			i++;
		}
		else if (line[i] == '>' && line[i + 1] == '>')
		{
			add_token(&head, ft_strdup(">>"), APPEND);
			i += 2;
		}
		else if (line[i] == '<' && line[i + 1] == '<')
		{
			add_token(&head, ft_strdup("<<"), HEREDOC);
			i += 2;
		}
		else if (line[i] == '>')
		{
			add_token(&head, ft_strdup(">"), REDIR_OUT);
			i++;
		}
		else if (line[i] == '<')
		{
			add_token(&head, ft_strdup("<"), REDIR_IN);
			i++;
		}
		else
			add_token(&head, read_word(line, &i), WORD);
	}
	data_base->token = head;
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	t_data	data_base;
	(void)argv;
	(void)argc;

	while (1)
	{
		line = readline("enter command: ");
		if (line && *line != '\0')
		{
			init_tokens(line, &data_base, env); // note the &
			print_tokens(data_base.token);
		}
		free(line);
	}
}
