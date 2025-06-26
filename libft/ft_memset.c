/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:28:07 by miaghabe          #+#    #+#             */
/*   Updated: 2024/11/16 20:47:39 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int c, size_t n)
{
	unsigned char	*ptr_byte;
	unsigned char	c_byte;
	size_t			i;

	ptr_byte = (unsigned char *)ptr;
	c_byte = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		ptr_byte[i] = c_byte;
		i++;
	}
	return (ptr);
}
