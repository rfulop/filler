/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 04:27:45 by rfulop            #+#    #+#             */
/*   Updated: 2017/05/23 04:07:19 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../include/filler.h"

void	freemem(t_map *map, t_piece *piece)
{
	int a;

	a = 0;
	while (a != piece->y)
	{
		free(piece->form[a]);
		a++;
	}
	a = 0;
	while (a != map->y)
	{
		free(map->board[a]);
		a++;
	}
}

int		main(void)
{
	char			*line;
	static t_core	core;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (ft_findstr(line, "$$$"))
			init_player(&core, line);
		if ((ft_findstr(line, "Plateau")))
		{
			init_coord(&core.map, line, ft_strnew(3), ft_strnew(3));
			init_core(&core, line, 0);
		}
		if (ft_isdigit(*line) && line[3] == ' ')
			init_core(&core, line, 1);
		if (line[1] == 'i' || line[0] == '.' || line[0] == '*')
			init_piece(&core, &core.piece, line);
		free(line);
	}
	freemem(&core.map, &core.piece);
	free(core.map.board);
	free(core.piece.form);
	return (0);
}
