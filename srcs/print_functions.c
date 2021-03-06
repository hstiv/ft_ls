/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <satmak335@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 19:18:23 by hstiv             #+#    #+#             */
/*   Updated: 2020/10/15 19:18:25 by hstiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				print_n_times(char c, int n)
{
	int				i;

	i = 0;
	while (i < n)
	{
		write(1, &c, 1);
		i++;
	}
}

int					print_dir_name(t_file *file)
{
	char			*s;
	int 			size;

	s = (g_curr_dir != NULL) ?
	path_with_f_name(file->filename, g_curr_dir) : ft_strdup(file->filename);
	if (g_data.arg_dir_count > 1)
	{
		write(1, s, ft_strlen(s));
		write(1, ":\n", 2);
	}
	if (g_data.option[0] && (size = get_block_size(s)) != -1)
	{
		write(1, "total ", 6);
		ft_putnbr(size);
		write(1, "\n", 1);
	}
	free(s);
	return (size);
}

void				print_l(t_file *file)
{
	write(1, file->f_stat->permission, ft_strlen(file->f_stat->permission));
	print_n_times(' ', g_data.alley_mlen[0] - file->f_stat->len[0]);
	ft_putnbr(file->f_stat->nlink);
	print_n_times(' ', g_data.alley_mlen[1] - file->f_stat->len[1]);
	write(1, file->f_stat->pw_name, ft_strlen(file->f_stat->pw_name));
	print_n_times(' ', g_data.alley_mlen[2] - file->f_stat->len[2]);
	write(1, file->f_stat->gr_name, ft_strlen(file->f_stat->gr_name));
	print_n_times(' ', g_data.alley_mlen[3] - file->f_stat->len[3]);
	ft_putnbr(file->f_stat->size);
	write(1, " ", 1);
	write(1, file->f_stat->month, ft_strlen(file->f_stat->month));
	print_n_times(' ', g_data.alley_mlen[4] - file->f_stat->len[4]);
	write(1, file->f_stat->day, ft_strlen(file->f_stat->day));
	write(1, " ", 1);
	write(1, file->f_stat->hour, 2);
	write(1, ":", 1);
	write(1, file->f_stat->min, 2);
	write(1, " ", 1);
	write(1, file->filename, ft_strlen(file->filename));
	if (file->f_stat->permission[0] == 'l')
	{
		write(1, " -> ", 4);
		ft_putstr(file->f_stat->linked_path);
	}
}

static void			print_reversed(t_file *start, char print_one)
{
	t_file			*file;

	file = start;
	while (file)
	{
		(g_data.option[0] == 1) ? print_l(file) :
		write(1, file->filename, ft_strlen(file->filename));
		write(1, "\n", 1);
		file = (print_one) ? NULL : file->next;
	}
}

void				print(t_file *start, char print_one)
{
	t_file			*file;

	file = start;
	if (g_data.option[3])
	{
		while (file->next)
			file = file->next;
		while (file)
		{
			(g_data.option[0] == 1) ? print_l(file) :
			write(1, file->filename, ft_strlen(file->filename));
			write(1, "\n", 1);
			file = (print_one) ? NULL : file->prev;
		}
	}
	else
		print_reversed(start, print_one);
}
