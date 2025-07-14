/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:52:22 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/14 15:27:15 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

char *get_env(char **env, const char *key);

int	builtin_pwd(t_data *data)
{
	char	*cwd;
	char	*pwd;

	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		printf("%s\n", cwd);
		free(cwd);
	}
	else
	{
		pwd = get_env(data->env, "PWD");
		if (pwd)
			printf("%s\n", pwd);
		else
			printf("pwd: error retrieving current directory\n");
	}
	return (0);
}
