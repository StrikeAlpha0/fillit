/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthompki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:53:40 by jthompki          #+#    #+#             */
/*   Updated: 2017/12/17 17:19:11 by jthompki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"

/*
**  Ft_validate_fit determines whether the tetrimino pointed to by
**  alst can fit at the position specified by row and col.
*/

static int		ft_validate_fit(t_tetris *alst, t_board *b, int row, int col)
{
	int		i;
	int		x;
	int		y;

	i = 5 * alst->min_row + alst->min_col - 1;
	while (++i < 20)
	{
		if (alst->shape[i / 5][i % 5] == '#')
		{
			x = (i / 5) - alst->min_row;
			y = (i % 5) - alst->min_col;
			if (!(0 <= row + x && row + x < b->size))
				return (0);
			if (!(0 <= col + y && col + y < b->size))
				return (0);
			if (b->map[row + x][col + y] != '.')
				return (0);
		}
	}
	return (1);
}

/*
**  Ft_place_piece places the tetrimino pointed to by alst at the
**  position specified by row and col.
*/

static void		ft_place_piece(t_tetris *alst, t_board *b, int row, int col)
{
	int		i;
	int		x;
	int		y;

	i = 5 * alst->min_row + alst->min_col - 1;
	while (++i < 20)
		if (alst->shape[i / 5][i % 5] == '#')
		{
			x = (i / 5) - alst->min_row;
			y = (i % 5) - alst->min_col;
			b->map[row + x][col + y] = alst->name;
		}
}

/*
**  Ft_remove_piece removes the tetrimino pointed to by alst from
**  the position specified by row and col.
*/

static void		ft_remove_piece(t_tetris *alst, t_board *b, int row, int col)
{
	int		i;
	int		x;
	int		y;

	i = 5 * alst->min_row + alst->min_col - 1;
	while (++i < 20)
		if (alst->shape[i / 5][i % 5] == '#')
		{
			x = (i / 5) - alst->min_row;
			y = (i % 5) - alst->min_col;
			b->map[row + x][col + y] = '.';
		}
}

/*
**  Ft_decision determines where the tetrimino pointed to by alst
**  can be placed on the board and sets it down.
**
**  If there is no solution to the problem for a given placement,
**  the function deletes the placement and moves to the next one.
*/

static int		ft_decision(t_tetris *alst, t_board *b)
{
	int		row;
	int		col;

	if (!alst)
		return (1);
	row = 0;
	while (row < b->size)
	{
		col = 0;
		while (col < b->size)
		{
			if (ft_validate_fit(alst, b, row, col))
			{
				ft_place_piece(alst, b, row, col);
				if (ft_decision(alst->next, b))
					return (1);
				else
					ft_remove_piece(alst, b, row, col);
			}
			col++;
		}
		row++;
	}
	return (0);
}

/*
**  Ft_solve initiates the recursive backtracking algorithm.
*/

int				ft_solve(t_tetris **alst, t_board *b)
{
	while (!ft_decision(*alst, b))
		b->size++;
	return (1);
}
