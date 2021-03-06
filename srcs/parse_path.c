/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ademurge <ademurge@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 18:23:31 by ademurge          #+#    #+#             */
/*   Updated: 2022/06/24 15:38:41 by ademurge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char	*search_path(char *line, char *to_find)
{
	char	*str;
	int		i;

	str = ft_strstr(line, to_find);
	i = 0;
	while (str && str[i] && to_find[i])
		i++;
	if (str)
		return (&str[i]);
	return (NULL);
}

void	parse(t_arg *args)
{
	int		i;
	char	*line_path;

	i = -1;
	while (args->env[++i])
	{
		line_path = search_path(args->env[i], "PATH=");
		if (line_path)
			break ;
	}
	if (!line_path)
		ft_error("Path not found", 0, args);
	args->split_path = ft_split(line_path, ':', args);
}
