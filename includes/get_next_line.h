/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atseruny <atseruny@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 19:27:26 by atseruny          #+#    #+#             */
/*   Updated: 2025/07/08 19:13:49 by atseruny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

char	*get_next_line(int fd);

char	*ft_strjoin_free(char *s1, char *s2, size_t l1, size_t l2);

size_t	ft_strlen(const char *str);

char	*ft_free_null(char *s);

int		ft_newline_instr(char *s);

#endif