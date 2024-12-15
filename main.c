/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skang <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:18:28 by skang             #+#    #+#             */
/*   Updated: 2024/12/15 21:03:02 by skang            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	main(void)
{
	int		fd;
	char	*s;

	fd = open("test.txt", O_RDONLY);
	printf("%s", get_next_line(fd));
	while (fd > 0)
	{
		s = get_next_line(fd);
		printf("%s", s);
		if (!s)
			break ;
	}
	return (0);
}
