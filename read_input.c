/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jthompki <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/12 14:23:47 by jthompki          #+#    #+#             */
/*   Updated: 2017/12/21 13:24:29 by msharpe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"

/*
**  Ft_validate_file determines whether the file is valid by checking whether
**  each tetrimino is composed of four rows of five characters, these five
**  characters being either four #'s or .'s followed by a newline '\n'.
**
**  Furthermore, each tetrimino must be separated by one and only one newline
**  character \n. If the file is either empty or exceeds 26 tetriminos, it is
**  invalid.
*/

static int		ft_validate_file(char buff[], int shift)
{
	int		i;

	i = 0;
	while (i < 20)
	{
		if ((i % 5) < 4)
			if ((buff[shift + i] != '.' && buff[shift + i] != '#'))
				return (0);
		if ((i % 5) == 4 && buff[shift + i] != '\n')
			return (0);
		i++;
	}
	if (buff[shift + i] && buff[shift + i] != '\n')
		return (0);
	return (1);
}

/*
**  Ft_validate_tetrimino determines whether the tetriminos in the file are
**  valid by counting the total number of neighbors and the total number of
**  sharps ('#').
**
**  Neighbors are defined as the contiguous sharps ('#') next to a
**  given sharp. If the number of neighors is 6 or 8, the tetrimino
**  is valid.
**
**  If less than four sharps are found per 20 bytes read, the tetrimino is
**  invalid.
*/

static int		ft_validate_tetrimino(char buff[], int shift, int sharp)
{
	int		i;
	int		neighbor;

	i = 0;
	sharp = 0;
	neighbor = 0;
	while (i < 19)
	{
		if (buff[shift + i] == '#')
		{
			if (i + 1 < 19 && (i + 1) % 5 != 4 && buff[shift + i + 1] == '#')
				neighbor++;
			if (i - 1 >= 0 && (i - 1) % 5 != 4 && buff[shift + i - 1] == '#')
				neighbor++;
			if (i + 5 < 19 && buff[shift + i + 5] == '#')
				neighbor++;
			if (i - 5 >= 0 && buff[shift + i - 5] == '#')
				neighbor++;
			sharp++;
		}
		i++;
	}
	if (sharp != 4 || (neighbor != 6 && neighbor != 8))
		return (0);
	return (1);
}

/*
**  Ft_read scans the entire document and determines if both the file and
**  the tetriminos are valid.
*/

int				ft_read(int fd, char buff[])
{
	int		ret;
	int		shift;

	shift = 0;
	ft_strclr(buff);
	ret = read(fd, buff, BUFF_SIZE);
	if (ret <= 0 || read(fd, buff, BUFF_SIZE) != 0)
		return (ft_error(0));
	while (shift < ret)
	{
		if (!ft_validate_file(buff, shift))
			return (ft_error(0));
		if (!ft_validate_tetrimino(buff, shift, 0))
			return (ft_error(0));
		shift += 21;
	}
	if (shift == ret)
		return (ft_error(0));
	return (ret);
}
