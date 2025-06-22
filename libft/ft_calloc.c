/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 22:04:27 by miaghabe          #+#    #+#             */
/*   Updated: 2025/01/18 23:29:50 by miaghabe         ###   ########.fr       */
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

/*#include <stdio.h>
int	main(void)
{
	int *arr = (int *)ft_calloc(5, sizeof(int));
	if (!arr)
		return (1);
	printf("%d %d %d\n", arr[0], arr[1], arr[2]);
	free(arr);
	return (0);
}*/