/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:34:35 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/01 17:40:30 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

static void	print_export_error(char *arg)
{
	write(2, "export: `", 9);
	write(2, arg, strlen(arg));
	write(2, "`: not a valid identifier\n", 27);
}

int	find_env_var_index(char **env, const char *name)
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

static void	no_arg_case(char **args, t_data *data)
{
	if (!args[1])
	{
		int i = 0;
		while (data->env && data->env[i])
		{
			char *equal = ft_strchr(data->env[i], '=');
			if (equal)
			{
				int key_len = equal - data->env[i];
				write(1, "declare -x ", 11);
				write(1, data->env[i], key_len);
				write(1, "=\"", 2);
				write(1, equal + 1, ft_strlen(equal + 1));
				write(1, "\"\n", 2);
			}
			else
			{
				write(1, "declare -x ", 11);
				write(1, data->env[i], ft_strlen(data->env[i]));
				write(1, "\n", 1);
			}
			i++;
		}
	}
}

int builtin_export(char **args, t_data *data)
{
	int i = 1;

	no_arg_case(args, data);
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
			data->env[idx] = ft_strdup(args[i]);
		else
		{
			int len = 0;
			while (data->env && data->env[len])
				len++;
			char **new_env = malloc(sizeof(char *) * (len + 2));
			int j = 0;
			while (j < len)
			{
				new_env[j] = data->env[j];
				j++;	
			}
			new_env[len] = ft_strdup(args[i]);
			new_env[len + 1] = NULL;
			data->env = new_env;
		}
		i++;
		free(var_name);
	}
	return 0;
}
