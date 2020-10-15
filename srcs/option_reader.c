/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_reader.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <satmak335@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 19:18:17 by hstiv             #+#    #+#             */
/*   Updated: 2020/10/15 19:18:19 by hstiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static	void	option_parsing(char *s)
{
	while (*s)
	{
		(*s == 'l') ? g_data.option[0] = 1 : 0;
		(*s == 'R') ? g_data.option[1] = 1 : 0;
		(*s == 'a') ? g_data.option[2] = 1 : 0;
		(*s == 'r') ? g_data.option[3] = 1 : 0;
		(*s == 't') ? g_data.option[4] = 1 : 0;
		if (ft_strchr(OPT, (int)*s) == NULL)
		{
			write(1, IL_OPT, ft_strlen(IL_OPT));
			write(1, &(*s), 1);
			throw(USAGE);
		}
		s++;
	}
}

static void		file_reader(char *s)
{
	if (g_data.arg_file == NULL)
	{
		g_data.arg_file = new_file(s);
		g_data.arg_files_count++;
	}
	else
	{
		g_data.arg_file->next = new_file(s);
		g_data.arg_file->next->prev = g_data.arg_file;
		g_data.arg_file = g_data.arg_file->next;
		g_data.arg_files_count++;
	}
}

void			arg_reader(int argc, char **argv)
{
	int			i;

	i = 0;
	while (++i < argc && argv[i][0] == '-')
		option_parsing(argv[i] + 1);
	while (i < argc)
		file_reader(argv[i++]);
	while (g_data.arg_files_count > 0 && g_data.arg_file->prev != NULL)
		g_data.arg_file = g_data.arg_file->prev;
}
