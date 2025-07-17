/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:05:04 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/17 17:31:09 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

static void	print_unset_error(char *arg)
{
	g_err_no = 1;
	write(2, "unset: `", 9);
	write(2, arg, ft_strlen(arg));
	write(2, "': not a valid identifier\n", 27);
}

static int	valid_identifier(const char *name)
{
	int	i;

	i = 0;
	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (0);
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	remove_env_var(t_data *data, int idx)
{
	char	**new_env;
	int		len;
	int		j;
	int		k;

	len = 0;
	while (data->env[len])
		len++;
	new_env = malloc(sizeof(char *) * len);
	if (!new_env)
		return (1);
	j = 0;
	k = 0;
	while (k < len)
	{
		if (k != idx)
			new_env[j++] = data->env[k];
		else
			free(data->env[k]);
		k++;
	}
	new_env[j] = NULL;
	free(data->env);
	data->env = new_env;
	return (0);
}

int	builtin_unset(char **args, t_data *data)
{
	int	i;
	int	idx;

	i = 1;
	while (args[i])
	{
		if (!valid_identifier(args[i]))
			return (print_unset_error(args[i]), g_err_no = 1, 1);
		if (args[i][0] == '_' && args[i][1] == '\0')
			return (1);
		idx = find_env_var_index(data->env, args[i]);
		if (idx >= 0)
		{
			if (remove_env_var(data, idx))
				return (1);
		}
		i++;
	}
	g_err_no = 0;
	return (0);
}
