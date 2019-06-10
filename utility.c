/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 22:51:03 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/08 23:05:16 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int					ft_2d_int_array_min(int **arr, int h, int i)
{
	int				a;
	int				b;
	int				crnt;

	a = -1;
	crnt = 0;
	while (++a < h)
	{
		b = -1;
		while (++b < i)
		{
			if (arr[a][b] < crnt)
				crnt = arr[a][b];
		}
	}
	return (crnt);
}

int					ft_2d_int_array_max(int **arr, int h, int i)
{
	int				a;
	int				b;
	int				crnt;

	a = -1;
	crnt = 0;
	while (++a < h)
	{
		b = -1;
		while (++b < i)
		{
			if (arr[a][b] > crnt)
				crnt = arr[a][b];
		}
	}
	return (crnt);
}

double				ft_2d_double_array_max(double **arr, int h, int i)
{
	int				a;
	int				b;
	double			crnt;

	a = -1;
	crnt = 0;
	while (++a < h)
	{
		b = -1;
		while (++b < i)
		{
			if (arr[a][b] > crnt)
				crnt = arr[a][b];
		}
	}
	return (crnt);
}

double				ft_2d_double_array_min(double **arr, int h, int i)
{
	int				a;
	int				b;
	double			crnt;

	a = -1;
	crnt = 0;
	while (++a < h)
	{
		b = -1;
		while (++b < i)
		{
			if (arr[a][b] < crnt)
				crnt = arr[a][b];
		}
	}
	return (crnt);
}
