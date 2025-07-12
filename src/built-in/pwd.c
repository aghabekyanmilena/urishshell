/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 17:52:22 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/12 16:24:12 by miaghabe         ###   ########.fr       */
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

/* pwd-n petqa pahel structi mej, vory char *a u cuyca talis env-i pwd-n
ete chi gtnum unset aneluc heto
inqy petqa tpi et pwd-i meji exacy*/