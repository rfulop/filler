/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piece.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/16 04:27:45 by rfulop            #+#    #+#             */
/*   Updated: 2017/05/03 00:42:10 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../include/filler.h"

void	check_piece(t_piece *piece)
{
	int a;
	int b;
	int flag;

	a = piece->x - 1;
	flag = 0;
	while (a >= 0 && (flag != -1))
	{
		b = 0;
		flag = 0;
		while (b <= (piece->y - 1))
		{
			if (piece->form[b][a] == '*')
				flag++;
			++b;
		}
		if (!flag)
			--piece->x;
		else
			flag = -1;
		--a;
	}
}

void	create_piece(t_piece *piece, char *line)
{
	piece->x = ft_atoi(&line[8]);
	piece->y = ft_atoi(&line[6]);
	if (!(piece->form = (char**)malloc(sizeof(char*) * (piece->y + 1))))
		return ;
	piece->form[piece->y] = NULL;
	piece->init++;
}

void	init_piece(t_core *core, t_piece *piece, char *line)
{
	if (!piece->init)
		create_piece(piece, line);
	else
	{
		if (ft_findstr(line, "*") || (piece->i))
		{
			piece->form[piece->i] = ft_strdup(line);
			piece->i++;
		}
		else
			piece->top++;
	}
	if (piece->i + piece->top == piece->y)
	{
		if (piece->top)
		{
			piece->form[piece->y - piece->top] = NULL;
			piece->y = piece->y - piece->top;
		}
		check_piece(piece);
		solve(core, &core->map, &core->player, piece);
	}
}
