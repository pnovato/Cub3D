/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:40:11 by kali              #+#    #+#             */
/*   Updated: 2026/05/04 07:07:39 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	parse_texture(char **dest, char *line)
{
	char	*trimmed;

	if (*dest != NULL)
		return (printf("Error\nDuplicated texture.\n"), 1);
	trimmed = ft_strtrim(line, " \t\n\r");
	if (!trimmed || trimmed[0] == '\0')
		return (free(trimmed), printf("Error\nInvalid path\n"), 1);
	if (has_spaces(trimmed))
		return (free(trimmed), printf("Error\nToo many args in tex\n"), 1);
	if (!is_xpm_extension(trimmed))
		return (free(trimmed), printf("Error\nInvalid extension\n"), 1);
	*dest = trimmed;
	return (0);
}

int	parse_element(char *line, t_data *data)
{
	char	*trim;
	char	type;

	trim = ft_strtrim(line, " \t\n\r");
	if (!trim || trim[0] == '\0')
		return (free(trim), 0);
	if (!ft_strncmp(trim, "NO ", 3))
		return (free(trim), parse_texture(&data->map.path_no, line + 3));
	if (!ft_strncmp(trim, "SO ", 3))
		return (free(trim), parse_texture(&data->map.path_so, line + 3));
	if (!ft_strncmp(trim, "WE ", 3))
		return (free(trim), parse_texture(&data->map.path_we, line + 3));
	if (!ft_strncmp(trim, "EA ", 3))
		return (free(trim), parse_texture(&data->map.path_ea, line + 3));
	if (!ft_strncmp(trim, "F ", 2) || !ft_strncmp(trim, "C ", 2))
	{
		type = trim[0];
		free(trim);
		return (parse_color(line, data, type));
	}
	free(trim);
	return (2);
}
