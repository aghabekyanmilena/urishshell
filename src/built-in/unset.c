/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 15:05:04 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/08 20:21:48 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

static void	print_unset_error(char *arg)
{
	ERR_NO = 1;
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

int	builtin_unset(char **args, t_data *data)
{
	char	**new_env;
	int		i;
	int		idx;
	int		len;
	int		k;
	int		j;

	i = 1;
	while (args[i])
	{
		if (!valid_identifier(args[i]))
			return (print_unset_error(args[i]), 1);
		idx = find_env_var_index(data->env, args[i]);
		if (idx >= 0)
		{
			len = 0;
			while (data->env[len])
				len++;
			new_env = malloc(sizeof(char *) * len);
			if (!new_env)
				return (1);
			if (args[i][0] == '_')
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
		}
		i++;
	}
	ERR_NO = 0;
	return (0);
}
