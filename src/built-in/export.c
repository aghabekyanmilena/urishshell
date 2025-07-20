/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 15:34:35 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/20 14:37:46 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

void	no_arg_case(char **args, t_data *data)
{
	char	**env_copy;
	int		i;
	int		j;

	if (args[1])
		return ;
	i = 0;
	while (data->env && data->env[i])
		i++;
	env_copy = malloc(sizeof(char *) * (i + 1));
	if (!env_copy)
		return ;
	j = 0;
	while (j < i)
	{
		env_copy[j] = ft_strdup(data->env[j]);
		j++;
	}
	env_copy[i] = NULL;
	sort_env(env_copy);
	print_exported_env(env_copy, 0);
}

char	*handle_var_name(char *arg, int *name_len)
{
	char	*equal_sign;
	char	*var_name;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (ft_strdup(arg));
	if (*(equal_sign - 1) == '+')
		*name_len = equal_sign - arg - 1;
	else
		*name_len = equal_sign - arg;
	var_name = malloc(*name_len + 1);
	if (!var_name)
		return (NULL);
	ft_strncpy(var_name, arg, *name_len);
	var_name[*name_len] = '\0';
	return (var_name);
}

int	handle_existing_var(char *arg, char *var_name, int name_len, t_data *data)
{
	char	*tmp;
	char	*tmp2;
	int		index;

	index = find_env_var_index(data->env, var_name);
	if (index < 0)
		return (0);
	if (ft_strchr(arg, '=') && *(ft_strchr(arg, '=') - 1) == '+')
	{
		tmp = ft_substr(data->env[index], name_len + 1,
				ft_strlen(data->env[index]) - name_len - 1);
		free(data->env[index]);
		tmp2 = ft_strsjoin(var_name, tmp, '=');
		free(tmp);
		tmp = ft_substr(arg, name_len + 2, ft_strlen(arg) - name_len - 2);
		data->env[index] = ft_strjoin(tmp2, tmp);
		free(tmp);
		free(tmp2);
	}
	else
	{
		free(data->env[index]);
		data->env[index] = ft_strdup(arg);
	}
	return (1);
}

void	append_new_var(t_data *data, char *arg, char *var_name, int name_len)
{
	char	**new_env;
	int		len;
	int		j;
	char	*tmp;

	len = 0;
	while (data->env && data->env[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	j = -1;
	while (++j < len)
		new_env[j] = data->env[j];
	if (ft_strchr(arg, '=') && *(ft_strchr(arg, '=') - 1) == '+')
	{
		tmp = ft_substr(arg, name_len + 1, ft_strlen(arg) - name_len - 1);
		new_env[len] = ft_strjoin(var_name, tmp);
		free(tmp);
	}
	else
		new_env[len] = ft_strdup(arg);
	new_env[len + 1] = NULL;
	free(data->env);
	data->env = new_env;
}

int	builtin_export(char **args, t_data *data)
{
	int		i;
	int		name_len;
	char	*var_name;

	i = 1;
	no_arg_case(args, data);
	while (args[i])
	{
		if (!is_valid_var_name(args[i]))
			return (print_export_error(args[i]), 1);
		var_name = handle_var_name(args[i], &name_len);
		if (!var_name)
			return (1);
		if (ft_strcmp(var_name, "_") == 0)
		{
			free(var_name);
			i++;
			continue ;
		}
		if (!handle_existing_var(args[i], var_name, name_len, data))
			append_new_var(data, args[i], var_name, name_len);
		free(var_name);
		i++;
	}
	return (g_err_no = 0, 0);
}
