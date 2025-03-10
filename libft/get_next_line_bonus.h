/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:02:26 by amonfret          #+#    #+#             */
/*   Updated: 2025/01/02 09:43:13 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
size_t	ft_strlen2(const char *s);
size_t	ft_strlcpy2(char *dst, const char *src, size_t size);
void	*free_mem(char **remainder, char **buffer);
// int		find_newline(char *str);
// char	*extract_line(char	*remainder);

#endif
