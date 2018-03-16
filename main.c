/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthompki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 19:52:44 by jthompki          #+#    #+#             */
/*   Updated: 2017/12/21 13:22:10 by msharpe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"

/*
**  Ft_initialize_board creates a t_board element b that will be
**  used to place the tetriminos.
*/

static void		ft_initialize_board(t_board *b)
{
	int			i;
	int			j;

	i = -1;
	while (++i < 104)
	{
		j = 0;
		while (j < 104)
			b->map[i][j++] = '.';
	}
	b->size = 4;
}

/*
**  Ft_getsize obtains the initial minimum dimensions for the
**  board.
*/

static int		ft_getsize(t_tetris *alst, int i)
{
	int			count;
	t_tetris	*current;

	count = 0;
	current = alst;
	while (current)
	{
		current = current->next;
		count++;
	}
	while ((i * i) < 4 * count)
		i++;
	return ((count == 1) ? 4 : i);
}

/*
**  Ft_print_board prints the solution to standard output.
*/

static void		ft_print_board(t_board *b)
{
	int		i;

	i = -1;
	while (++i < (b->size + 1) * b->size)
		if (i % (b->size + 1) == b->size)
			ft_putchar('\n');
		else
			ft_putchar(b->map[i / (b->size + 1)][i % (b->size + 1)]);
}

/*
**  Ft_error writes "error\n" to standard output in the event
**  of any error.
*/

int				ft_error(int e)
{
	if (e == 1)
		ft_putendl("usage: ./fillit sourcefile");
	else
		ft_putendl("error");
	return (0);
}

int				main(int argc, char **argv)
{
	int			ret;
	char		*filename;
	char		buff[BUFF_SIZE];
	t_tetris	*alst;
	t_board		*b;

	if (argc != 2)
		return (ft_error(1));
	alst = NULL;
	if (!(b = (t_board*)malloc(sizeof(t_board))))
		return ((int)ft_error(0));
	filename = argv[1];
	ret = ft_read(open(filename, O_RDONLY), buff);
	if (ret == 0)
		return (0);
	if (!(alst = ft_parse_tetriminos(buff, 0, ret)))
		return (0);
	ft_initialize_board(b);
	b->size = ft_getsize(alst, 2);
	ft_solve(&alst, b);
	ft_print_board(b);
	return (1);
}
