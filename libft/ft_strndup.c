/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 14:53:45 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/26 15:01:53 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*s1_dup;

	if (n > ft_strlen(s1))
		n = ft_strlen(s1);
	i = 0;
	s1_dup = (char *)malloc(n + 1);
	if (!s1_dup)
		return (NULL);
	while (i < n)
	{
		s1_dup[i] = s1[i];
		i++;
	}
	s1_dup[i] = '\0';
	return ((char *)s1_dup);
}
