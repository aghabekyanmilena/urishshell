/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miaghabe <miaghabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 18:23:09 by miaghabe          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/07/11 19:06:53 by miaghabe         ###   ########.fr       */
=======
/*   Updated: 2025/07/12 15:58:29 by miaghabe         ###   ########.fr       */
>>>>>>> main
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
<<<<<<< HEAD
}


// int	builtin_exit(char **args)
// {
// 	int	exit_code;
// 	int	i;
	
// 	exit_code = 0;
// 	printf("exit\n");
// 	i = 0;
// 	while (args[i])
// 		i++;
// 	if (i > 2)
// 	{
// 		ft_putendl_fd("exit: too many arguments", 2);
// 		ERR_NO = 1;
// 		return (1);
// 	}
// 	if (args[1])
// 	{
// 		if (!is_digital(args[1]))
// 		{
// 			printf("minishell: exit: %s: numeric argument required\n", args[1]);
// 			ERR_NO = 2;
// 		}
// 		if ((long long)exit_code >= 9223372036854775807)
// 		{
// 			ERR_NO = 2;
// 			write(2, "exit: ", 6);
// 			write(2, ft_itoa(exit_code), ft_strlen(ft_itoa(exit_code)));
// 			write(2, ": numeric argument required\n", 29);
// 		}
// 		exit_code = ft_atoi(args[1]);
// 	}
// 	ERR_NO = exit_code;
// 	exit(exit_code);
// }

/* PWD-i depqy u cd*/
=======
}
>>>>>>> main
