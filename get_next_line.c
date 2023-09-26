/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.45urduli>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 00:20:59 by ivromero          #+#    #+#             */
/*   Updated: 2023/06/21 22:32:56 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//static int	fill_buffer(int fd, char *buffer){}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*buffer;
	char		*aux;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);

	if (read(fd, buffer, BUFFER_SIZE) < 1)
		return (free(buffer), NULL);
	while (buffer[i] != '\n' && i < BUFFER_SIZE)
		i++;
	str = ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (free(buffer), NULL);
	while (j < i)
	{
		str[j] = buffer[j];
		j++;
	}


	aux = ft_calloc(BUFFER_SIZE - i + 1, sizeof(char));
	if (!aux)
		return (free(buffer), NULL);
	j = 0;
	while (buffer[i] != '\0')
		aux[j++] = buffer[i++];

	free(buffer);
	buffer = aux;
	return (str);
}
