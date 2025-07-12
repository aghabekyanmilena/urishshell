/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:26:50 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/08 19:14:03 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"

char	*ft_free_null(char *s)
{
	free(s);
	return (NULL);
}

int	ft_newline_instr(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin_free(char *s1, char *s2, size_t l1, size_t l2)
{
	char	*s;
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (ft_free_null(s1));
	s = (char *)malloc((l1 + l2 + 1) * sizeof(char));
	if (!s)
		return (ft_free_null(s1));
	while (i < l1)
	{
		s[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < l2)
	{
		s[l1 + i] = s2[i];
		i++;
	}
	s[l1 + l2] = '\0';
	s1 = ft_free_null(s1);
	return (s);
}
