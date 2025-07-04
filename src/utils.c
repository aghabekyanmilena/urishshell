typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

struct s_data
{
	t_token	*token;
	t_env	*env;  // linked list env
	int		pipes_count;
};

#include "../includes/tokenization.h"

// es funkcian envn char **-ic sarquma list
t_env	*env_list_from_envp(char **envp)
{
	t_env	*head = NULL;
	t_env	*tail = NULL;
	int		i = 0;

	while (envp[i])
	{
		char	*equal_sign = strchr(envp[i], '=');
		if (!equal_sign)
		{
			i++;
			continue;
		}
		t_env *new = malloc(sizeof(t_env));
		if (!new)
			return NULL;
		new->key = strndup(envp[i], equal_sign - envp[i]);
		new->value = strdup(equal_sign + 1);
		new->next = NULL;
		if (!head)
			head = new;
		else
			tail->next = new;
		tail = new;
		i++;
	}
	return head;
}

// jnjuma hamapatasxan nody
void	remove_env_node(t_env **env, const char *key)
{
	t_env *curr = *env;
	t_env *prev = NULL;

	while (curr)
	{
		if (strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return;
		}
		prev = curr;
		curr = curr->next;
	}
}

// esi el sarquma unsety listerov
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
		remove_env_node(&data->env, args[i]);
		i++;
	}
	return (0);
}


// HIMA EXPORTI HAMAR

// gtnuma env listi mej key-i valuen
t_env	*get_env_node(t_env *env, const char *name)
{
	while (env)
	{
		if (ft_strcmp(env->key, name) == 0)
			return env;
		env = env->next;
	}
	return NULL;
}

// stuguma valida te che
static int	is_valid_var_name(const char *name)
{
	int i = 0;

	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return 0;
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return 0;
		i++;
	}
	return 1;
}

// no argumnet casey
static void	no_arg_case(char **args, t_data *data)
{
	if (!args[1])
	{
		int len = 0;
		t_env *tmp = data->env;
		while (tmp)
		{
			len++;
			tmp = tmp->next;
		}
		char **env_copy = malloc(sizeof(char *) * (len + 1));
		if (!env_copy)
			return;
		tmp = data->env;
		int i = 0;
		while (tmp)
		{
			if (tmp->value)   // esi petqa lini strsjoin
				env_copy[i] = ft_strsjoin(tmp->key, "=", tmp->value);
			else
				env_copy[i] = ft_strdup(tmp->key);
			tmp = tmp->next;
			i++;
		}
		env_copy[i] = NULL;
		sort_env(env_copy);
		i = 0;
		while (env_copy[i])
		{
			char *equal = ft_strchr(env_copy[i], '=');
			if (equal)
			{
				int key_len = equal - env_copy[i];
				write(1, "declare -x ", 11);
				write(1, env_copy[i], key_len);
				write(1, "=\"", 2);
				write(1, equal + 1, ft_strlen(equal + 1));
				write(1, "\"\n", 2);
			}
			else
			{
				write(1, "declare -x ", 11);
				write(1, env_copy[i], ft_strlen(env_copy[i]));
				write(1, "\n", 1);
			}
			free(env_copy[i]);
			i++;
		}
		free(env_copy);
	}
}

// ev exporty listov

int	builtin_export(char **args, t_data *data)
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
		char *key = malloc(name_len + 1);
		if (!key)
			return 1;
		ft_strncpy(key, args[i], name_len);
		key[name_len] = '\0';

		char *value = ft_strdup(equal_sign + 1);

		t_env *node = get_env_node(data->env, key);
		if (node)
		{
			free(node->value);
			node->value = value;
		}
		else
		{
			t_env *new = malloc(sizeof(t_env));
			if (!new)
			{
				free(key);
				free(value);
				return 1;
			}
			new->key = key;
			new->value = value;
			new->next = data->env;
			data->env = new;
		}
		i++;
	}
	return 0;
}

// esi el echon
int	builtin_echo_list(t_cmd *cmd)
{
	int			n_flag = 0;
	t_cmd	*curr = cmd->next;

	while (curr && curr->value && curr->value[0] == '-' && curr->value[1] == 'n')
	{
		int j = 2;
		while (curr->value[j] == 'n')
			j++;
		if (curr->value[j] != '\0')
			break;
		n_flag = 1;
		curr = curr->next;
	}
	while (curr)
	{
		printf("%s", curr->value);
		if (curr->next)
			printf(" ");
		curr = curr->next;
	}
	if (!n_flag)
		printf("\n");
	return 0;
}
