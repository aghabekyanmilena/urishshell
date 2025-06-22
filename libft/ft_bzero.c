/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 16:30:37 by miaghabe          #+#    #+#             */
/*   Updated: 2025/01/18 23:25:12 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *ptr, size_t n)
{
	ft_memset (ptr, '\0', n);
}

/*#include <stdio.h>
int main()
{

	char buffer[6] = "Hello";
	printf("Before %s\n", buffer);
	ft_bzero(buffer, 6);
	printf("After %s\n", buffer);
	return 0;
}*/