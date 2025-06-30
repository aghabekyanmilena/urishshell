/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:34:35 by miaghabe          #+#    #+#             */
/*   Updated: 2025/06/30 16:11:43 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

static void	print_export_error(char *arg)
{
	write(2, "export: `", 9);
	write(2, arg, strlen(arg));
	write(2, "`: not a valid identifier\n", 27);
}

static int find_env_var_index(char **env, const char *name)
{
	int i = 0;
	size_t len = ft_strlen(name);

	while (env && env[i])
	{
		if (!ft_strncmp(env[i], name, len) && env[i][len] == '=')
			return i;
		i++;
	}
	return -1;
}

static int is_valid_var_name(const char *name)
{
	int	i;

	i = 0;
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		return 0;
		i++;
	}
	return (1);
}

int builtin_export(char **args, t_data *data)
{
	int i = 1;

	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
		{
			print_export_error(args[i]);
			i++;
			continue;
		}
		char *equal_sign = ft_strchr(args[i], '=');
		if (!equal_sign)
		{
			i++;
			continue;
		}
		int name_len = equal_sign - args[i];
		char *var_name = malloc(name_len + 1);
		if (!var_name)
			return (1);
		ft_strncpy(var_name, args[i], name_len);
		var_name[name_len] = '\0';
		ft_strncpy(var_name, args[i], equal_sign - args[i]);
		int idx = find_env_var_index(data->env, var_name);
		if (idx >= 0)
		{
			// free(data->env[idx]);
			data->env[idx] = ft_strdup(args[i]);
		}
		else
		{
			int len = 0;
			while (data->env && data->env[len])
				len++;
			char **new_env = malloc(sizeof(char *) * (len + 2));
			for (int j = 0; j < len; j++)
				new_env[j] = data->env[j];
			new_env[len] = ft_strdup(args[i]);
			new_env[len + 1] = NULL;
			data->env = new_env;
		}
		i++;
		free(var_name);
	}
	return 0;
}
