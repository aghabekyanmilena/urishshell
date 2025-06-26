/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 00:39:10 by miaghabe          #+#    #+#             */
/*   Updated: 2024/11/16 20:58:00 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsize)
{
	size_t	i;
	size_t	dest_size;
	size_t	src_size;

	i = 0;
	src_size = ft_strlen(src);
	if (dsize == 0)
		return (src_size);
	dest_size = ft_strlen(dst);
	if (dest_size >= dsize)
		return (dsize + src_size);
	while (src[i] && (dest_size + i) < dsize - 1)
	{
		dst[dest_size + i] = src[i];
		i++;
	}
	dst[dest_size + i] = '\0';
	if (dest_size + i < dsize)
		return (dest_size + src_size);
	return (dsize + src_size);
}
