/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 18:59:27 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/17 19:18:47 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

void	print_export_error(char *arg)
{
	g_err_no = 1;
	write(2, "export: `", 9);
	write(2, arg, ft_strlen(arg));
	write(2, "`: not a valid identifier\n", 27);
}

int	find_env_var_index(char **env, char *name)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], name, len))
			return (i);
		i++;
	}
	return (-1);
}

int	is_valid_var_name(char *name)
{
	int	i;

	i = 1;
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	while (name[i] && name[i] != '=' && name[i] != '+')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	print_exported_env(char **env_copy, int j)
{
	char	*equal;
	int		key_len;

	while (env_copy[j])
	{
		equal = ft_strchr(env_copy[j], '=');
		if (equal)
		{
			key_len = equal - env_copy[j];
			write(1, "declare -x ", 11);
			write(1, env_copy[j], key_len);
			write(1, "=\"", 2);
			write(1, equal + 1, ft_strlen(equal + 1));
			write(1, "\"\n", 2);
		}
		else
		{
			write(1, "declare -x ", 11);
			write(1, env_copy[j], ft_strlen(env_copy[j]));
			write(1, "\n", 1);
		}
		free(env_copy[j]);
		j++;
	}
	free(env_copy);
}
