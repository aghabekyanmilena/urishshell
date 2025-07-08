/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:23:09 by miaghabe          #+#    #+#             */
/*   Updated: 2025/07/08 20:56:35 by miaghabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/built_in.h"

static int	is_digital(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

// bool	ft_atolli(char *arg)
// {
// 	long long int	res;
// 	int				sign = 1;

// 	res = 0;
// 	while (*arg && (*arg == 32 || (*arg >= 9 && *arg <= 13)))
// 		arg++;
// 	if (*arg == '-')
// 	{
// 		sign *= -1;
// 		arg++;
// 	}
// 	else if (*arg == '+')
// 		arg++;
// 	while (*arg && *arg == '0')
// 		arg++;
// 	if (ft_strlen(arg) > 11)
// 		return (false);
// 	while (*arg && (*arg >= '0' && *arg <= '9'))
// 	{
// 		res = res * 10 + (*arg - '0');
// 		arg++;
// 	}
// 	if ((res * sign) > INT_MAX || (res * sign) < INT_MIN)
// 		return (false);
// 	return (true);
// }

int	builtin_exit(char **args)
{
	int	exit_code;
	int	i;
	
	exit_code = 0;
	printf("exit\n");
	i = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("exit: too many arguments", 2);
		ERR_NO = 1;
		return (1);
	}
	if (args[1])
	{
		if (!is_digital(args[1]))
			printf("minishell: exit: %s: numeric argument required\n", args[1]);
		if ((long long)exit_code >= 9223372036854775807)
		{
			ERR_NO = 2;
			write(2, "exit: ", 6);
			write(2, ft_itoa(exit_code), ft_strlen(ft_itoa(exit_code)));
			write(2, ": numeric argument required\n", 29);
		}
		exit_code = ft_atoi(args[1]);
	}
	ERR_NO = exit_code;
	exit(exit_code);
}

/*exit_code-y sarqum em long long isk ete exitis argumenty valid a
 aysinqn long longic poqr a uremn ERR_NO = exit_code % 255
ete invalid a uremn ERR_NO = 2 stex anum em strlen u hamematum
heto nayel PWD-i depqy u cd
*/