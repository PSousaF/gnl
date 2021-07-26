#include "get_next_line.h"

static void	ft_strfree(char **str)
{
	if (*str && str)
	{
		free(*str);
		*str = NULL;
	}
}	

static char	*ft_split_line(int ret, char **save)
{
	char		*tmp;
	char		*line;
	int			i;

	i = 0;
	if (ret < 0 || BUFFER_SIZE < 1 || !*save || *save[i] == '\0')
	{
		ft_strfree(save);
		return (NULL);
	}
	while ((*save)[i] != '\n' && (*save)[i])
		i++;
	if (ft_strchr (*save, '\n'))
	{
		line = ft_substr(*save, 0, i + 1);
		tmp = ft_strdup(*save + i + 1);
		ft_strfree(save);
		*save = tmp;
		return (line);
	}
	line = ft_substr(*save, 0, i);
	ft_strfree(save);
	return (line);
}

char	*get_next_line(int fd)
{
	static char		*save;
	char			*buffer;
	char			*tmp;
	int				ret;

	buffer = (char *)malloc(BUFFER_SIZE + 1);
	ret = read(fd, buffer, BUFFER_SIZE);
	while (ret > 0)
	{
		buffer[ret] = '\0';
		if (!save)
			save = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(save, buffer);
			free(save);
			save = tmp;
		}
		if (ft_strchr(save, '\n'))
			break ;
		ret = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (ft_split_line(ret, &save));
}
