/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 23:52:17 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/15 15:35:41 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/tokenization.h"

static int	is_numeric(const char *str)
{
	if (!str || !*str)
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

// esi env-i mej gtnuma key@ u =ic heto dra hamapatasxan valuen return anum
char	*get_env(char **env, const char *key)
{
	size_t	len;
	int		i;

	len = ft_strlen(key);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

// update a anum env-n ete vary ka replace a anum ete chka avelacnuma
void	update_env(t_data *data, const char *key, const char *value)
{
	int		idx;
	char	*new_entry;
	int		len;
	char	**new_env;
	int		i;

	new_entry = malloc(ft_strlen(key) + ft_strlen(value) + 2);
	idx = find_env_var_index(data->env, key);
	if (!new_entry)
		return ;
	ft_strcpy(new_entry, key);
	ft_strcat(new_entry, "=");
	ft_strcat(new_entry, value);
	if (idx >= 0)
	{
		free(data->env[idx]);
		data->env[idx] = new_entry;
	}
	else
	{
		len = 0;
		while (data->env && data->env[len])
			len++;
		new_env = malloc(sizeof(char *) * (len + 2));
		if (!new_env)
			return ;
		i = -1;
		while (++i < len)
			new_env[i] = data->env[i];
		new_env[len] = new_entry;
		new_env[len + 1] = NULL;
		data->env = new_env;
	}
}

// esi el arden shlvl-n avelacnoxna
// et taky 1000+ casy comment em arel vorovhetev vrodi bashum ela okay 
//ete 1000 u avela
void	handle_shlvl(t_data *data)
{
	char	*shlvl_str;
	int		shlvl;
	char	*shlvl_val;

	shlvl_str = get_env(data->env, "SHLVL");
	shlvl = 0;
	if (!shlvl_str)
		shlvl = 1;
	else if (is_numeric(shlvl_str))
		shlvl = ft_atoi(shlvl_str) + 1;
	else
		shlvl = 1;
	if (shlvl < 0)
		shlvl = 0;
	shlvl_val = ft_itoa(shlvl);
	update_env(data, "SHLVL", shlvl_val);
	free(shlvl_val);
}

// if (shlvl >= 1000)
// {
// 	printf("minishell: warning\n");
// 	shlvl = 1;
// }
// mek el libft-i mej avelacrel em strcpy ev strcat