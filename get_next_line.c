/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:42:20 by skang             #+#    #+#             */
/*   Updated: 2024/12/14 17:35:51 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	size;

	if (!s)
		return (NULL);
	if ((unsigned int)gnl_strlen(s) <= (unsigned int)start)
		return (gnl_strdup(""));
	size = gnl_strlen(s + start);
	if (size < len)
		len = size;
	sub_s = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub_s)
		return (NULL);
	gnl_strlcpy(sub_s, s + start, len + 1);
	return (sub_s);
}

static char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*join_str;
	size_t	s1_len;
	size_t	s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = gnl_strlen((char *)s1);
	s2_len = gnl_strlen((char *)s2);
	join_str = (char *)malloc(s1_len + s2_len + 1);
	if (join_str == NULL)
		return (NULL);
	gnl_strlcpy(join_str, (char *)s1, gnl_strlen(s1) + 1);
	gnl_strcat(join_str, (char *)s2);
	return (join_str);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*result;
	char		buffer[BUFFER_SIZE + 1];
	ssize_t		buffer_read;
	char		*escape_location;
	int			escape_index;

	buffer_read = 1;
	while (!(gnl_strchr(stash, '\n')) && (buffer_read > 0))
	{
		buffer_read = read(fd, buffer, BUFFER_SIZE);
		buffer[buffer_read] = '\0';
		if (stash == NULL)
			stash = gnl_strjoin(buffer, "");
		else
			stash = gnl_strjoin(stash, buffer);
	}
	escape_location = gnl_strchr(stash, '\n');
	escape_index = (++escape_location) - stash;
	result = gnl_substr(stash, 0, escape_index);
	stash = gnl_substr(stash, escape_index, gnl_strlen(stash));
	return (result);
}
