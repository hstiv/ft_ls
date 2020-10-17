/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <satmak335@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 19:18:03 by hstiv             #+#    #+#             */
/*   Updated: 2020/10/15 20:13:28 by hstiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void			recursive(t_file *ptr)
{
	t_file			*files;
	char			*s;

	ptr = only_dirs(ptr);
	if (g_data.option[3])
		while (ptr && ptr->next)
			ptr = ptr->next;
	while (ptr)
	{
		files = ptr;
		if (ft_strcmp(files->filename, ".") && ft_strcmp(files->filename, ".."))
		{
			(g_curr_dir == NULL) ? g_curr_dir = ft_strdup(".") : 0;
			(g_data.print_enter == 1) ? write(1, "\n", 1) : 0;
			print_dir_name(ptr);
			s = path_with_f_name(ptr->filename, g_curr_dir);
			free(g_curr_dir);
			g_curr_dir = s;
			ft_ls(read_dir(g_curr_dir));
			g_curr_dir = rmallocladir(g_curr_dir);
		}
		ptr = (g_data.option[3]) ? ptr->prev : ptr->next;
		del_file(files);
	}
}

void				ft_ls(t_file *ptr)
{
	t_file			*files;

	if (ptr == NULL)
		return ;
	files = ptr;
	sort(files, (g_data.option[4]) ? MTIME : ASCII);
	print(files, 0);
	g_data.print_enter = 1;
	g_data.alley_mlen[0] = 0;
	g_data.alley_mlen[1] = 0;
	g_data.alley_mlen[2] = 0;
	g_data.alley_mlen[3] = 0;
	g_data.alley_mlen[4] = 0;
	if (g_data.option[1] == 1)
		recursive(files);
	else
		while (files)
		{
			ptr = files;
			files = files->next;
			del_file(ptr);
		}
}

static void			arg_handler(void)
{
	t_file			*file;
	int				print_enter;

	file = g_data.arg_file;
	print_enter = 0;
	sort(file, (g_data.option[4]) ? MTIME : ASCII);
	while (file)
	{
		(file->f_stat->permission[0] != 'd') ? print(file, 1) : 0;
		file = file->next;
	}
	g_data.arg_file = only_dirs(g_data.arg_file);
	while (g_data.arg_file)
	{
		file = g_data.arg_file;
		(print_enter == 1) ? write(1, "\n", 1) : 0;
		g_curr_dir = ft_strdup(g_data.arg_file->filename);
		print_dir_name(g_data.arg_file);
		ft_ls(read_dir(g_data.arg_file->filename));
		free(g_curr_dir);
		g_curr_dir = NULL;
		g_data.arg_file = g_data.arg_file->next;
		print_enter = 1;
		del_file(file);
	}
}

static void			current_dir(void)
{
	t_file			*file;

	file = new_file(".");
	if (g_data.option[0])
	{
		write(1, "total ", 6);
		ft_putnbr(get_block_size("."));
		write(1, "\n", 1);
	}
	ft_ls(read_dir("."));
	del_file(file);
}

int					main(int argc, char **argv)
{
	set_data();
	(argc > 1 && argv[1] != NULL) ? arg_reader(argc, argv) : 0;
	if (g_data.arg_files_count == 0 || g_data.arg_file == NULL)
		current_dir();
	else
		arg_handler();
	if (g_curr_dir != NULL)
		free(g_curr_dir);
	return (0);
}
