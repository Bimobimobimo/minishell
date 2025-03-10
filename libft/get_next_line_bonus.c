/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:03:07 by amonfret          #+#    #+#             */
/*   Updated: 2025/01/02 09:49:17 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

static int	find_newline(char *remainder)
{
	int	i;

	i = 0;
	if (remainder)
	{
		while (remainder[i])
		{
			if (remainder[i] == '\n')
				return (i);
			i++;
		}
	}
	return (-1);
}

static char	*extract_line(char *remainder)
{
	char	*line;
	int		newline_index;

	newline_index = find_newline(remainder);
	if (newline_index >= 0)
	{
		line = malloc(newline_index + 2);
		if (!line)
			return (NULL);
		ft_strlcpy2(line, remainder, newline_index + 2);
	}
	else
	{
		line = malloc(ft_strlen2(remainder) + 1);
		if (!line)
			return (NULL);
		ft_strlcpy2(line, remainder, ft_strlen2(remainder) + 1);
	}
	return (line);
}

static char	*update_remainder(char **remainder)
{
	char	*new_remainder;
	int		newline_index;
	size_t	len_nl;

	if (!remainder || !*remainder)
		return (NULL);
	newline_index = find_newline(*remainder);
	len_nl = ft_strlen2(*remainder) - newline_index;
	if (newline_index >= 0)
	{
		if ((*remainder)[newline_index + 1] != '\0')
		{
			new_remainder = malloc(len_nl);
			if (!new_remainder)
				return (NULL);
			ft_strlcpy2(new_remainder, *remainder + newline_index + 1, len_nl);
		}
		else
			new_remainder = NULL;
	}
	else
		new_remainder = NULL;
	free(*remainder);
	*remainder = new_remainder;
	return (*remainder);
}

// static char	*update_remainder(char **remainder)
// {
// 	char	*new_remainder;
// 	int		newline_index;
// 	size_t	len_nl;

// 	newline_index = find_newline(*remainder);
// 	len_nl = ft_strlen2(*remainder) - newline_index;
// 	if (newline_index >= 0)
// 	{
// 		new_remainder = malloc(ft_strlen2(*remainder) - newline_index);
// 		if (!new_remainder)
// 			return (NULL);
// 		ft_strlcpy2(new_remainder, *remainder + newline_index + 1, len_nl);
// 		free(*remainder);
// 		*remainder = new_remainder;
// 	}
// 	else
// 	{
// 		free(*remainder);
// 		*remainder = NULL;
// 	}
// 	return (*remainder);
// }

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;

	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		*s1 = '\0';
	}
	str = malloc((ft_strlen2(s1) + ft_strlen2(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy2(str, s1, ft_strlen2(s1) + 1);
	ft_strlcpy2(str + ft_strlen2(s1), s2, ft_strlen2(s2) + 1);
	free(s1);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*remainders[1024];
	ssize_t		b;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	b = read(fd, buffer, BUFFER_SIZE);
	while (b > 0)
	{
		buffer[b] = '\0';
		remainders[fd] = ft_strjoin(remainders[fd], buffer);
		if (find_newline(remainders[fd]) >= 0)
			break ;
		b = read(fd, buffer, BUFFER_SIZE);
	}
	if (b < 0 || (b == 0 && (!remainders[fd] || !*remainders[fd])))
		return (free_mem(&remainders[fd], &buffer));
	line = extract_line(remainders[fd]);
	update_remainder(&remainders[fd]);
	return (free(buffer), line);
}

// int main(void)
// {
// 	char *line;

// 	int i = 0;
// 	while (i < 3)
// 	{
// 		line = get_next_line(0);
// 		printf("%s\n", line);
// 		free(line);
// 		i++;
// 	}
// 	return (0);
// }

// int main(void)
// {
// 	int fd;
// 	int fd1 = open("test1.txt", O_RDONLY);
// 	int fd2 = open("test2.txt", O_RDONLY);
// 	if(fd1 == -1 || fd2 == -1)
// 	{
// 		if (fd1 == -1) close(fd1);
// 		if (fd2 == -1) close(fd2);
// 		return (1);
// 	}
// 	int i = 0;
// 	char *line;
// 	while ((line = get_next_line(fd = i % 2 == 0 ? fd1 : fd2)) != NULL)
// 	{
// 		printf("Calling get_next_line on fd %d\n", fd);
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}

// 	close(fd);
// 	return (0);
// }

/*Lorem ipsum dolor sit amet,
consectetur adipiscing elit,
sed do eiusmod tempor,
incididunt ut labore et dolore magna aliqua.
Ut enim ad minim veniam,
quis nostrud exercitation ullamco laboris nisi ut,
aliquip ex ea commodo consequat. Duis aute irure dolor in,
reprehenderit in voluptate velit esse cillum dolore eu,
fugiat nulla pariatur. Excepteur sint occaecat cupidatat,
non proident, sunt in culpa qui officia deserunt,
mollit anim id est laborum.*/

/*Pour vous faire mieux connaître d’où vient,
l’erreur de ceux qui blâment la volupté,
et qui louent en quelque sorte la douleur,
je vais entrer dans une explication plus étendue,
et vous faire voir tout ce qui a été dit là-dessus par l’inventeur de la vérité,
et, pour ainsi dire, par l’architecte de la vie heureuse.
Personne ne craint ni ne fuit la volupté en tant que volupté,
mais en tant qu’elle attire de grandes douleurs à ceux qui ne savent pas,
en faire un usage modéré et raisonnable ;
et personne n’aime ni ne recherche la douleur comme douleur,
mais parce qu’il arrive quelquefois que, par le travail et par la peine,
on parvienne à jouir d’une grande volupté. En effet,
pour descendre jusqu’aux petites choses,
qui de vous ne fait point quelque exercice pénible,
pour en retirer quelque sorte d’utilité ?*/
