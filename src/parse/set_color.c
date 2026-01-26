/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:04:36 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/19 16:05:06 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	skip_space(const char *s, int *i)
{
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
}

static int	parse_int_0_255(const char *s, int *i)
{
	long	v;
	int		digits;

	v = 0;
	digits = 0;
	skip_space(s, i);
	while (ft_isdigit(s[*i]))
	{
		v = v * 10 + (s[*i] - '0');
		(*i)++;
		digits++;
		if (v > 255)
			return (-1);
	}
	if (digits == 0)
		return (-1);
	skip_space(s, i);
	return ((int)v);
}

static void	check_color_trailing(t_parse_data *pd, const char *raw, int i)
{
	while (raw[i] == ' ' || raw[i] == '\t')
		i++;
	if (raw[i] != '\n' && raw[i] != '\0')
		exit_parse(pd, "Error\nTrailing junk in color\n");
}

static void	parse_rgb(t_parse_data *pd, const char *raw, int rgb[3])
{
	int	i;

	i = 0;
	rgb[0] = parse_int_0_255(raw, &i);
	if (rgb[0] < 0 || raw[i++] != ',')
		exit_parse(pd, "Error\nInvalid color (R)\n");
	rgb[1] = parse_int_0_255(raw, &i);
	if (rgb[1] < 0 || raw[i++] != ',')
		exit_parse(pd, "Error\nInvalid color (G)\n");
	rgb[2] = parse_int_0_255(raw, &i);
	if (rgb[2] < 0)
		exit_parse(pd, "Error\nInvalid color (B)\n");
	check_color_trailing(pd, raw, i);
}

void	set_color(t_parse_data *pd, int *has_flag, int rgb[3], char *raw)
{
	if (!has_flag || !rgb)
		exit_parse(pd, "Error\nInvalid color target\n");
	if (*has_flag)
		exit_parse(pd, "Error\nDuplicate color\n");
	parse_rgb(pd, raw, rgb);
	*has_flag = 1;
}
