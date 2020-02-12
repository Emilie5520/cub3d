#include "../includes/cub3d.h"

char	*ft_recup_root(char *line)
{
	int	i;
	char	**tab;
	char	*line2;

	i = 0;

	line2 = ft_strdup("");	
	tab = ft_split(line, ' ');
	if (line2)
		line2 = ft_strdup(tab[1]);
	while (tab[i])
		free(tab[i++]);
	free(tab[i]);
	free(tab);
	return (line2);
}
