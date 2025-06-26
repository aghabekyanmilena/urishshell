/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:39:39 by miaghabe          #+#    #+#             */
/*   Updated: 2024/11/23 17:06:52 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	unsigned int	i;

	i = ft_strlen(str);
	while (i > 0 && str[i] != (char)c)
		i--;
	if (str[i] == (char)c)
		return ((char *)&str[i]);
	else
		return (NULL);
}
