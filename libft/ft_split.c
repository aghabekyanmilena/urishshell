/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 16:51:48 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/19 20:00:09 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	count_words(char *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			cnt++;
			while (s[i] != '\0' && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (cnt);
}

void	ft_free(char **s, int j)
{
	int	i;

	i = 0;
	while (i <= j)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

static int	len_malloc(char *s, char **str, char c, int i)
{
	int	cnt;
	int	j;

	j = 0;
	while (s[i] != '\0')
	{
		cnt = 0;
		if (s[i] != c)
			while (s[i] != '\0' && s[i++] != c)
				cnt++;
		else
			i++;
		if (cnt != 0)
		{
			str[j] = (char *)malloc((cnt + 1) * sizeof(char));
			if (!str[j])
			{
				ft_free(str, j);
				return (0);
			}
			j++;
		}
	}
	return (1);
}

static void	ktr(char *s, char **str, char c, int i)
{
	int	j;
	int	cnt;

	j = 0;
	while (s[i] != '\0')
	{
		cnt = 0;
		if (s[i] != c)
		{
			while (s[i] != '\0' && s[i] != c)
			{
				str[j][cnt] = s[i++];
				cnt++;
			}
		}
		else
			i++;
		if (cnt != 0)
			str[j++][cnt] = '\0';
	}
	str[j] = NULL;
}

char	**ft_split(char *s, char c)
{
	int		j;
	int		k;
	char	**str;

	if (ft_strlen(s) == 0)
		return (NULL);
	j = count_words((char *)s, c);
	str = (char **)malloc((j + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	k = len_malloc((char *)s, str, c, 0);
	if (k == 0)
		return (NULL);
	ktr((char *)s, str, c, 0);
	return (str);
}
// int main()
// {
//     char *s="aa ";
//     char **s1=ft_split(s,' ');
//     int i=0;
//     while (i<2)
//     {
//         printf("%s\n", s1[i]);
//         i++;
//     }
// }
