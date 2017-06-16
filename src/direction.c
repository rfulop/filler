/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 02:13:07 by rfulop            #+#    #+#             */
/*   Updated: 2017/05/03 02:47:20 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../include/filler.h"

void	putresult(t_map *map, t_player *player, t_enemy *enemy, int place)
{
	enemy->place = place;
	player->put_x = map->i;
	player->put_y = map->j;
}

void	gotop(t_map *map, t_player *player, t_enemy *enemy, t_piece *piece)
{
	int	b;

	if (player->min != 0)
	{
		b = 0;
		player->gotop = 1;
		while (b != map->x)
		{
			if (map->board[enemy->min][b] == enemy->color)
				player->target_x = b + piece->x;
			++b;
		}
		if (player->target_x > map->x - 1)
			player->target_x = map->x - 1;
		player->target_y = 0;
	}
}

void	gobot(t_map *map, t_player *player, t_enemy *enemy)
{
	int	b;

	if (player->max != map->y - 1)
	{
		b = 0;
		player->gobot = 1;
		while (b != map->x)
		{
			if (map->board[enemy->max][b] == enemy->color)
				player->target_x = b;
			++b;
		}
		player->target_y = map->y - 1;
	}
}

void	choosedir(t_map *map, t_player *player, t_enemy *enemy, t_piece *piece)
{
	if ((player->min >= enemy->min) || (player->max <= enemy->max))
	{
		if ((player->min >= enemy->min) && (player->max <= enemy->max))
		{
			if (enemy->max - player->max > player->min - enemy->min)
				gobot(map, player, enemy);
			else
				gotop(map, player, enemy, piece);
		}
		else if (player->min >= enemy->min)
			gotop(map, player, enemy, piece);
		else
			gobot(map, player, enemy);
	}
	analysesides(map, player, enemy);
}
