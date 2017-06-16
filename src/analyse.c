/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 02:13:07 by rfulop            #+#    #+#             */
/*   Updated: 2017/05/23 04:06:29 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../include/filler.h"

int		chase(t_map *map, int x, int y)
{
	int	a;
	int	b;

	a = (x - map->i);
	if (a < 0)
		a = a * -1;
	b = (y - map->j);
	if (b < 0)
		b = b * -1;
	return (a + b);
}

void	checkminmax(t_map *map, t_player *player, t_enemy *enemy)
{
	int	a;

	a = 0;
	while (a != map->y)
	{
		if (ft_strchr(map->board[a], enemy->color))
		{
			if (enemy->min == -1)
				enemy->min = a;
			else
				enemy->max = a;
		}
		if (ft_strchr(map->board[a], player->color))
		{
			if (player->min == -1)
				player->min = a;
			else
				player->max = a;
		}
		++a;
	}
	if (!enemy->max)
		enemy->max = enemy->min;
	if (!player->max)
		player->max = player->min;
}

void	analysesides(t_map *map, t_player *player, t_enemy *enemy)
{
	int x;
	int y;
	int i;

	x = 0;
	i = 0;
	if (player->gobot)
		y = map->y - 1;
	else
		y = 0;
	while (x != map->x)
	{
		if (map->board[y][x] == enemy->color)
			++i;
		++x;
	}
	if (i >= (map->x / 2))
	{
		player->gobot = 0;
		player->gotop = 0;
	}
}

int		isvalidplace(t_core *core, t_map *map, t_piece *piece)
{
	int	x;
	int	y;
	int	check;

	y = 0;
	check = 0;
	while (y < piece->y)
	{
		x = 0;
		while (x < piece->x)
		{
			if (piece->form[y][x] == '*')
			{
				if (map->board[map->j + y][map->i + x] == core->enemy.color)
					return (0);
				if (map->board[map->j + y][map->i + x] == core->player.color)
					++check;
			}
			x++;
		}
		y++;
	}
	return (check == 1 ? 1 : 0);
}
