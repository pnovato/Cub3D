#include "../../includes/cub3d.h"

/* ** Esta função é um rascunho do parser. 
** Ela lê o arquivo e pula as configurações iniciais para pegar o mapa.
** Para um projeto final, você precisará validar NO, SO, WE, EA, F, C.
*/
int	parse_map(char *file, t_data *data)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (printf("Error\nNão foi possível abrir o mapa.\n"), 1);

	data->map.map = malloc(sizeof(char *) * 100);
	i = 0;
	while ((line = get_next_line(fd)))
	{
		if (line[0] == '1' || line[0] == ' ')
		{
			data->map.map[i] = ft_strdup(line);
			i++;
		}
		free(line);
	}
	data->map.map[i] = NULL;
	close(fd);
	return (0);
}