/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:04:36 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/19 16:05:06 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

static int is_digit(char c)
{
    return (c >= '0' && c <= '9');
}

static void skip_ws(const char *s, int *i)
{
    while (s[*i] == ' ' || s[*i] == '\t')
        (*i)++;
}

static int parse_int_0_255(const char *s, int *i)
{
    long v = 0;
    int digits = 0;

    skip_ws(s, i);
    while (is_digit(s[*i]))
    {
        v = v * 10 + (s[*i] - '0');
        (*i)++;
        digits++;
        if (v > 255)
            return -1;
    }
    if (digits == 0)
        return -1;
    skip_ws(s, i);
    return (int)v;
}

void set_color(int *has_flag, int rgb[3], char *raw)
{
    int i = 0;
    int r, g, b;

    if (!has_flag || !rgb)
        exit_text("Error\nInvalid color target\n");
    if (*has_flag)
        exit_text("Error\nDuplicate color\n");
    r = parse_int_0_255(raw, &i);
    if (r < 0 || raw[i] != ',')
        exit_text("Error\nInvalid color (R)\n");
    i++; // skip ','

    g = parse_int_0_255(raw, &i);
    if (g < 0 || raw[i] != ',')
        exit_text("Error\nInvalid color (G)\n");
    i++;

    b = parse_int_0_255(raw, &i);
    if (b < 0)
        exit_text("Error\nInvalid color (B)\n");

    // dopo B: solo whitespace o '\n' o '\0'
    while (raw[i] == ' ' || raw[i] == '\t')
        i++;
    if (raw[i] != '\n' && raw[i] != '\0')
        exit_text("Error\nTrailing junk in color\n");

    rgb[0] = r;
    rgb[1] = g;
    rgb[2] = b;
    *has_flag = 1;
}
