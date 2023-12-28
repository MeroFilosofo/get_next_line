/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ivromero <ivromero@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 00:20:50 by ivromero          #+#    #+#             */
/*   Updated: 2023/12/28 19:39:11 by ivromero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memset(void *b, int c, size_t len)
{
	while (len--)
		((char *)b)[len] = (unsigned char)c;
	return (b);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*pntrs;

	pntrs = malloc(size * count);
	if (pntrs)
		ft_memset(pntrs, 0, size * count);
	return (pntrs);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' || (c % 256) == '\0')
		if (*s++ == (c % 256))
			return ((char *)--s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*pstr;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!str)
		return (NULL);
	pstr = str;
	while (*s1)
		*(str++) = *(s1++);
	while (*s2)
		*(str++) = *(s2++);
	*str = '\0';
	return (pstr);
}

/*
char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*dest;

	dest = 0;
	i = -1;
	len = ft_strlen(s);
	dest = (char *)ft_calloc(len + 1, sizeof(*dest));
	if (dest)
		while (++i < len)
			dest[i] = s[i];
	return (dest);
}
*/
