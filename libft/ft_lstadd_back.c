/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 00:11:34 by miaghabe          #+#    #+#             */
/*   Updated: 2025/01/23 22:49:56 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	node = ft_lstlast(*lst);
	node -> next = new;
}

#include <stdio.h>
int	main()
{
	t_list *head = ft_lstnew("mek");
	ft_lstadd_back(&head, ft_lstnew("erku"));
	printf("%s %s\n", (char *)head->content, (char *)head->next->content);
	return (0);
}