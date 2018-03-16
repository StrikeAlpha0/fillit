/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthompki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 20:48:08 by jthompki          #+#    #+#             */
/*   Updated: 2017/12/21 13:23:56 by msharpe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"

/*
**  Ft_new_link allocates space for a new t_tetris list element, sets
**  the initial values, and returns a pointer that points to this
**  element.
*/

static t_tetris		*ft_new_link(void)
{
	int			i;
	int			j;
	t_tetris	*link;

	if (!(link = (t_tetris *)malloc(sizeof(t_tetris))))
		return (NULL);
	i = 0;
	link->name = '-';
	link->min_row = 4;
	link->min_col = 4;
	link->next = NULL;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
			link->shape[i][j++] = '.';
		link->shape[i][j] = '\n';
		i++;
	}
	return (link);
}

/*
**  Ft_fill_link replaces the default values of the given t_tetris
**  element with information from the buffer.
*/

static void			ft_fill_link(t_tetris **link, char buff[], int i, int shift)
{
	int			x;
	t_tetris	*current;
	char		*namelist;

	x = 0;
	namelist = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	current = *link;
	current->name = namelist[i];
	while (x < 20)
	{
		if (buff[shift + x] == '#')
		{
			if (x % 5 < current->min_col)
				current->min_col = x % 5;
			if (x / 5 < current->min_row)
				current->min_row = x / 5;
			current->shape[x / 5][x % 5] = buff[shift + x];
		}
		x++;
	}
}

/*
**  Ft_add_link places the t_tetris link passed through as an
**  argument to the end of the list alst.
*/

static void			ft_add_link(t_tetris **alst, t_tetris **link)
{
	t_tetris	*current;
	t_tetris	*previous;

	if (!(*alst))
		*alst = *link;
	else
	{
		current = *alst;
		while (current != NULL)
		{
			previous = current;
			current = current->next;
		}
		previous->next = (*link);
	}
}

/*
**  Ft_parse_tetriminos reads through the character buffer buff[]
**  and creates t_tetris links for each tetrimino contained in it.
*/

t_tetris			*ft_parse_tetriminos(char buff[], int shift, int ret)
{
	int				i;
	t_tetris		*alst;
	t_tetris		*current;

	i = -1;
	alst = NULL;
	while (shift < ret)
	{
		if (!(current = ft_new_link()))
			return (!(ft_error(0)) ? NULL : alst);
		ft_fill_link(&current, buff, ++i, shift);
		ft_add_link(&alst, &current);
		shift += 21;
	}
	return (alst);
}
