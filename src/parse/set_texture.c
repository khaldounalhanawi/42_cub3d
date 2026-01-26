/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:04:36 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/19 16:05:06 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <fcntl.h>
#include <unistd.h>

static char	*trim_space_ends(char *s)
{
	int	start;
	int	end;

	start = 0;
	if (!s)
		return (NULL);
	while (s[start] && (s[start] == ' ' || s[start] == '\t'))
		start++;
	end = start;
	while (s[end] && s[end] != '\n')
		end++;
	while (end > start && (s[end - 1] == ' ' || s[end - 1] == '\t'))
		end--;
	return (ft_substr(s, (unsigned)start, (size_t)(end - start)));
}

static int	ends_with(const char *s, const char *suffix)
{
	size_t	ls;
	size_t	lf;

	ls = ft_strlen(s);
	lf = ft_strlen(suffix);
	if (ls < lf)
		return (0);
	return (ft_strncmp(s + (ls - lf), suffix, lf) == 0);
}

void	set_texture(t_parse_data *pd, char **dst, char *raw)
{
	char	*path;
	int		fd;

	if (!dst)
		exit_parse(pd, "Error\nInvalid texture target\n");
	if (*dst)
		exit_parse(pd, "Error\nDuplicate texture\n");
	path = trim_space_ends(raw);
	if (!path || path[0] == '\0')
	{
		free(path);
		exit_parse(pd, "Error\nEmpty texture path\n");
	}
	if (!ends_with(path, ".xpm"))
	{
		free(path);
		exit_parse(pd, "Error\nTexture must be .xpm\n");
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		free(path);
		exit_parse(pd, "Error\nTexture file not readable\n");
	}
	close(fd);
	*dst = path;
}
