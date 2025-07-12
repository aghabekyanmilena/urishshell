/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:13:17 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/12 16:13:44 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

static int	ft_atolli_safe(const char *str, long long *out)
{
	int				sign = 1;
	unsigned long	result = 0;
	int				i = 0;

	*out = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		result = result * 10 + (str[i] - '0');
		if (result > 9223372036854775807ULL && !(sign == -1 && result == 9223372036854775808ULL))
			return (0);
		i++;
	}
	if (sign == -1 && result == 9223372036854775808ULL)
		*out = -9223372036854775807LL - 1;
	else
		*out = result * sign;
	return (1);
}

int	builtin_exit(char **args)
{
	long long	exit_code;
	int			count;

	printf("exit\n");
	count = 0;
	while (args[count])
		count++;
	if (count > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		ERR_NO = 1;
		return (1);
	}
	if (args[1])
	{
		if (!ft_atolli_safe(args[1], &exit_code))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(args[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			exit(2);
		}
		exit((unsigned char)exit_code);
	}
	exit(0);
}
