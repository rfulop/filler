/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 04:27:45 by rfulop            #+#    #+#             */
/*   Updated: 2017/05/03 00:42:34 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../include/filler.h"

void	init_coord(t_map *map, char *line, char *x, char *y)
{
	int a;
	int b;

	a = 8;
	b = 0;
	while (line[a] && ft_isdigit(line[a]))
	{
		y[b] = line[a];
		++a;
		++b;
	}
	a++;
	b = 0;
	while (line[a] && ft_isdigit(line[a]))
	{
		x[b] = line[a];
		++a;
		++b;
	}
	map->x = ft_atoi(x);
	map->y = ft_atoi(y);
	free(x);
	free(y);
}

void	create_values(t_core *core)
{
	core->map.init = 0;
	core->piece.i = 0;
	core->piece.init = 0;
	core->player.put_y = 0;
	core->player.put_x = 0;
	core->player.min = -1;
	core->player.max = 0;
	core->enemy.min = -1;
	core->enemy.max = 0;
	core->enemy.place = 0;
	core->player.target_y = 0;
	core->player.target_x = 0;
	core->player.gotop = 0;
	core->player.gobot = 0;
	core->piece.top = 0;
}

void	init_core(t_core *core, char *line, int initmap)
{
	if (!initmap)
	{
		if (!core->init)
		{
			core->init = 1;
			if (!(core->map.board = (char**)malloc(sizeof(char*) *
							(core->map.x + 1))))
				return ;
			core->map.board[core->map.x] = NULL;
			core->init = 1;
		}
		create_values(core);
	}
	else
	{
		core->map.board[core->map.init] = ft_strdup(line + 4);
		core->map.init++;
	}
}

void	init_player(t_core *core, char *line)
{
	if (!core->player.color)
	{
		if (ft_findstr(line, "p1"))
		{
			core->player.color = 'O';
			core->enemy.color = 'X';
		}
		else
		{
			core->player.color = 'X';
			core->enemy.color = 'O';
		}
	}
}
