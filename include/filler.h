/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfulop <rfulop@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/30 02:50:51 by rfulop            #+#    #+#             */
/*   Updated: 2017/05/23 05:08:16 by rfulop           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include "./../libft/includes/libft.h"
# include "./../libft/includes/ft_printf.h"

typedef struct		s_map
{
	int				x;
	int				y;
	int				i;
	int				j;
	int				init;
	char			**board;
}					t_map;

typedef struct		s_piece
{
	int				init;
	int				i;
	int				x;
	int				y;
	int				top;
	char			**form;
}					t_piece;

typedef struct		s_player
{
	char			color;
	int				put_x;
	int				put_y;
	int				min;
	int				max;
	int				gotop;
	int				gobot;
	int				target_y;
	int				target_x;
}					t_player;

typedef struct		s_enemy
{
	char			color;
	int				place;
	int				i;
	int				j;
	int				flag;
	int				min;
	int				max;
}					t_enemy;

typedef struct		s_core
{
	int				init;
	struct s_map	map;
	struct s_piece	piece;
	struct s_player	player;
	struct s_enemy	enemy;
}					t_core;

/*
** Initialization functions
*/
void				init_player(t_core *core, char *line);
void				init_coord(t_map *map, char *line, char *x, char *y);
void				init_core(t_core *core, char *line, int initmap);
void				create_values(t_core *core);

/*
** Piece functions
*/
void				init_piece(t_core *core, t_piece *piece, char *line);
void				check_piece(t_piece *piece);
void				create_piece(t_piece *piece, char *line);

/*
** Solve functions
*/
void				solve(t_core *core, t_map *map, t_player *player, t_piece
					*piece);
int					scout(t_map *map, t_enemy *enemy);
void				rush(t_core *core, t_map *map, t_piece *piece);
int					surround(t_core *core, t_map *map, t_player *player,
					t_enemy *enemy);
void				hang_on(t_core *core, t_map *map, t_player *player, t_piece
					*piece);

/*
** Analyse functions
*/
void				checkminmax(t_map *map, t_player *player, t_enemy *enemy);
void				checksides(t_map *map, t_player *player, t_enemy *enemy);
int					isvalidplace(t_core *core, t_map *map, t_piece *piece);
void				analysesides(t_map *map, t_player *player, t_enemy *enemy);

/*
** Direction functions
*/
void				putresult(t_map *map, t_player *player, t_enemy *enemy, int
					place);
void				gobot(t_map *map, t_player *player, t_enemy *enemy);
void				gotop(t_map *map, t_player *player, t_enemy *enemy, t_piece
					*piece);
void				choosedir(t_map *map, t_player *player, t_enemy *enemy,
					t_piece *piece);
int					chase(t_map *map, int x, int y);

#endif
