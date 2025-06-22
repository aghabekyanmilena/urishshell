/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 22:47:22 by miaghabe          #+#    #+#             */
/*   Updated: 2025/01/18 23:58:42 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

/*#include <stdio.h>
int	main(void)
{
	t_list *head = ft_lstnew("erku");
	ft_lstadd_front(&head, ft_lstnew("mek"));
	printf("%s %s\n", (char *)head->content, (char *)head->next->content);
	return (0);
}*/