/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 00:20:59 by ivromero          #+#    #+#             */
/*   Updated: 2023/12/28 20:28:17 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_get_rest(char *buffer)
{
	char	*rest;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (buffer[0] == '\0' && ft_strlen(buffer) == 0)
		return (free(buffer), NULL);
	rest = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!rest)
		return (NULL);
	while (buffer[i] != '\0')
		rest[j++] = buffer[i++];
	free(buffer);
	return (rest);
}

static char	*ft_get_line(char *buffer)
{
	char	*line;
	size_t	i;
	size_t	j;

	if (!buffer)
		return (NULL);
	i = 0;
	j = -1;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (i == 0 && buffer[0] == '\0')
		return (ft_calloc(1, sizeof(char)));
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	while (++j < i)
		line[j] = buffer[j];
	line[j] = '\0';
	return (line);
}

static char	*ft_fill_buffer(int fd, char *rest)
{
	char	*buffer;
	char	*temp;
	int		bytes_read;

	if (!rest)
		rest = ft_calloc(1, sizeof(char));
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(rest, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes_read] = '\0';
		if (bytes_read == -1 || (bytes_read == 0 && ft_strlen(rest) == 0))
			return (free(buffer), free(rest), NULL);
		if (bytes_read == 0)
			break ;
		temp = ft_strjoin(rest, buffer);
		free(rest);
		rest = temp;
		if (!rest)
			return (free(rest), NULL);
	}
	return (free(buffer), rest);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if ((fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0) && buffer[fd])
		return (free(buffer[fd]), buffer[fd] = NULL, NULL);
	if ((fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0))
		return (NULL);
	buffer[fd] = ft_fill_buffer(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = ft_get_line(buffer[fd]);
	if (!line)
		return (free(buffer[fd]), NULL);
	buffer[fd] = ft_get_rest(buffer[fd]);
	return (line);
}

/*

 #include <fcntl.h>
int	main(void)
{
	int		fd;
	char	*line;

	fd = open("test.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
	 line = get_next_line(fd);
	printf("%s#", line); 
	close(fd);
	return (0);
} 



 #include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	printf("BUFFER_SIZE = %d\n", BUFFER_SIZE);
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	else
		fd = open("tests/giant_line_nl.txt", O_RDONLY);
	if (fd < 0)
		return (perror("Error opening file"), 1);
	line = get_next_line(fd);
	while (line)
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	if (line)
		free(line);
	close(fd);
	printf("\nPulsa enter para continuar.");
	//getchar();
	//system("leaks a.out");
	return (0);
} 
*/
