#include "../../includes/cub3d.h"

int	is_xpm_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 5)
		return (0);
	if (ft_strncmp(path + len - 4, ".xpm", 4))
		return (0);
	if (path[len - 5] == '/' || len == 4)
		return (0);
	return (1);
}

int	has_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
			return (1);
		i++;
	}
	return (0);
}
