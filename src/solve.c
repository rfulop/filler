/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/18 05:53:09 by rfulop            #+#    #+#             */
/*   Updated: 2017/05/23 04:06:53 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/filler.h"

int		scout(t_map *map, t_enemy *enemy)
{
	int	side;

	side = 1;
	enemy->flag = 0;
	while (!enemy->flag)
	{
		enemy->j = map->j - side;
		if (enemy->j < 0)
			enemy->j = 0;
		while ((enemy->j < map->y) && enemy->j <= map->j + side)
		{
			enemy->i = map->i - side;
			if (enemy->i < 0)
				enemy->i = 0;
			while ((enemy->i < map->x) && enemy->i <= map->i + side)
			{
				if (map->board[enemy->j][enemy->i] == enemy->color)
					++enemy->flag;
				++enemy->i;
			}
			++enemy->j;
		}
		++side;
	}
	return (side);
}

void	rush(t_core *core, t_map *map, t_piece *piece)
{
	int	dif;

	map->j = 0;
	while ((map->j + piece->y) <= map->y)
	{
		map->i = 0;
		while ((map->i + piece->x) <= map->x)
		{
			if (isvalidplace(core, map, piece))
			{
				dif = chase(map, core->player.target_x, core->player.target_y);
				if (dif < core->enemy.place || !core->enemy.place)
					putresult(map, &core->player, &core->enemy, dif);
			}
			map->i++;
		}
		map->j++;
	}
}

int		surround(t_core *core, t_map *map, t_player *player, t_enemy *enemy)
{
	int y;
	int x;

	if ((player->min == 0 && core->enemy.min != 0) ||
		(player->max == map->y - 1 && core->enemy.max != map->y - 1))
	{
		if (player->min == 0 && enemy->min != 0)
			player->target_y = enemy->min;
		else
			player->target_y = enemy->max;
		y = player->target_y;
		x = 0;
		while (x != map->x)
		{
			if (map->board[y][x] == enemy->color)
				player->target_x = x;
			++x;
		}
		return (1);
	}
	return (0);
}

void	hang_on(t_core *core, t_map *map, t_player *player, t_piece *piece)
{
	int place;

	map->j = 0;
	while ((map->j + piece->y) <= map->y)
	{
		map->i = 0;
		while ((map->i + piece->x) <= map->x)
		{
			if (isvalidplace(core, map, piece))
			{
				place = scout(map, &core->enemy);
				if ((!player->put_y || place < core->enemy.place))
					putresult(map, player, &core->enemy, place);
			}
			map->i++;
		}
		map->j++;
	}
}

void	solve(t_core *core, t_map *map, t_player *player, t_piece *piece)
{
	checkminmax(map, player, &core->enemy);
	choosedir(map, player, &core->enemy, piece);
	if (player->gotop || player->gobot)
		rush(core, map, piece);
	else if (surround(core, map, player, &core->enemy))
		rush(core, map, &core->piece);
	else
		hang_on(core, map, player, piece);
	ft_printf("%d %d\n", player->put_y - piece->top, player->put_x);
}
