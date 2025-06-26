/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:04:27 by miaghabe          #+#    #+#             */
/*   Updated: 2024/11/18 16:45:09 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*mem;
	size_t			i;

	if ((size != 0 && count > 65536) || (size > 65536 && count != 0))
		return (NULL);
	mem = (unsigned char *)malloc(count * size);
	if (!mem)
		return (NULL);
	i = 0;
	while (i < count * size)
	{
		mem[i] = 0;
		i++;
	}
	return (mem);
}
