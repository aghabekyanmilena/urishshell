/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 10:13:25 by miaghabe          #+#    #+#             */
/*   Updated: 2024/11/17 01:40:10 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	lit_size;
	size_t	big_size;

	lit_size = ft_strlen(little);
	if (lit_size == 0)
		return ((char *) big);
	if (len == 0)
		return (0);
	big_size = ft_strlen(big);
	i = 0;
	while ((i + lit_size) <= len && i < big_size)
	{
		if (ft_strncmp(big + i, little, lit_size) == 0)
			return ((char *) big + i);
		i++;
	}
	return (0);
}
