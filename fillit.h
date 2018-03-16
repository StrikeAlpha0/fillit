/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthompki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 14:43:02 by jthompki          #+#    #+#             */
/*   Updated: 2017/12/21 13:21:11 by msharpe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <fcntl.h>
# include "libft/libft.h"
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

/*
**  Definitions
*/

# define BUFF_SIZE 524

/*
**  Structures
*/

typedef struct	s_tetris
{
	char				name;
	char				shape[5][5];
	int					min_row;
	int					min_col;
	struct s_tetris		*next;
}				t_tetris;

typedef struct	s_board
{
	char			map[104][104];
	int				size;
}				t_board;

/*
**  Client: Main.c
*/

int				ft_error(int e);

/*
** Module 1: Read_input.c
*/

int				ft_read(int fd, char buff[]);

/*
**  Module 2: List.c
*/

t_tetris		*ft_parse_tetriminos(char buff[], int shift, int ret);

/*
**  Module 3: Solve.c
*/

int				ft_solve(t_tetris **alst, t_board *b);

#endif
