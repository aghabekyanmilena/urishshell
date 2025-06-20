/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 15:26:09 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/20 17:22:37 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenization.h"

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

static char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s1_dup;

	i = 0;
	s1_dup = (char *)malloc(ft_strlen(s1) + 1);
	if (!s1_dup)
		return (NULL);
	while (s1[i] != '\0')
	{
		s1_dup[i] = s1[i];
		i++;
	}
	s1_dup[i] = '\0';
	return ((char *)s1_dup);
}

void	tokenize(const char *line)
{
	int		i = 0;
	t_token	*tokens = NULL;

	while (line[i])
	{
		if (ft_isspace(line[i]) == 1)
			i++;
		else if (line[i] == '|' )
			add_token(&tokens, ft_strdup("|"), S_PIPE), i++;
		else if (line[i] == '|' && line[i + 1] == '|')
			add_token(&tokens, ft_strdup("|"), D_PIPE), i++;
		else if (line[i] == '>' && line[i + 1] == '>')
			add_token(&tokens, ft_strdup(">>"), APPEND), i += 2;
		else if (line[i] == '>')
			add_token(&tokens, ft_strdup(">"), REDIR_OUT), i++;
		else if (line[i] == '<' && line[i + 1] == '<')
			add_token(&tokens, ft_strdup("<<"), HEREDOC), i += 2;
		else if (line[i] == '<')
			add_token(&tokens, ft_strdup("<"), REDIR_IN), i++;
		else if (line[i] == '"')
			add_token(&tokens, read_quoted_string(line, &i, line[i]), D_QUOTE);
		else
			add_token(&tokens, read_word(line, &i), WORD);
	}
	print_tokens(tokens);
	free_tokens(tokens);
}

