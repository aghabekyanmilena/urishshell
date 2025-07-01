/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 14:48:43 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/29 14:52:50 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

int	builtin_cd(char **args, t_data *data)
{
	char	*dir;

	(void)data;
	dir = args[1];
	if (!dir)
		dir = getenv("HOME");
	if (!dir || chdir(dir) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}
