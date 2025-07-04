/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:05:04 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/04 23:35:33 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

static void	print_unset_error(char *arg)
{
	write(2, "unset: `", 9);
	write(2, arg, strlen(arg));
	write(2, "': not a valid identifier\n", 27);
}

static int	valid_identifier(const char *name)
{
	int i = 0;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return 0;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return 0;
		i++;
	}
	return 1;
}

int	builtin_unset(char **args, t_data *data)
{
	int	i = 1;

	while (args[i])
	{
		if (!valid_identifier(args[i]))
		{
			print_unset_error(args[i]);
			i++;
			continue;
		}
		int idx = find_env_var_index(data->env, args[i]);
		if (idx >= 0)
		{
			int len = 0;
			while (data->env[len])
				len++;
			char **new_env = malloc(sizeof(char *) * len);
			if (!new_env)
				return (1);
			int j = 0;
			int k = 0;
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
		}
		i++;
	}
	return (0);
}
