/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stats.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstiv <satmak335@gmail.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 19:19:10 by hstiv             #+#    #+#             */
/*   Updated: 2020/10/15 19:19:11 by hstiv            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

size_t				num_len(int n)
{
	size_t			l;

	l = (n < 0) ? 1 : 0;
	while (n)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

static void			set_permission(mode_t st_mode, t_stat *f_st)
{
	if ((st_mode & S_IFMT) == S_IFBLK)
		f_st->permission[0] = 'b';
	else if ((st_mode & S_IFMT) == S_IFCHR)
		f_st->permission[0] = 'c';
	else if ((st_mode & S_IFMT) == S_IFLNK)
		f_st->permission[0] = 'l';
	else if ((st_mode & S_IFMT) == S_IFDIR)
		f_st->permission[0] = 'd';
	else if ((st_mode & S_IFMT) == S_IFSOCK)
		f_st->permission[0] = 's';
	else if ((st_mode & S_IFMT) == S_IFIFO)
		f_st->permission[0] = 'p';
	else
		f_st->permission[0] = '-';
	f_st->permission[1] = (st_mode & S_IRUSR) ? 'r' : '-';
	f_st->permission[2] = (st_mode & S_IWUSR) ? 'w' : '-';
	f_st->permission[3] = (st_mode & S_IXUSR) ? 'x' : '-';
	f_st->permission[4] = (st_mode & S_IRGRP) ? 'r' : '-';
	f_st->permission[5] = (st_mode & S_IWGRP) ? 'w' : '-';
	f_st->permission[6] = (st_mode & S_IXGRP) ? 'x' : '-';
	f_st->permission[7] = (st_mode & S_IROTH) ? 'r' : '-';
	f_st->permission[8] = (st_mode & S_IWOTH) ? 'w' : '-';
	f_st->permission[9] = (st_mode & S_IXOTH) ? 'x' : '-';
	f_st->permission[10] = ' ';
	f_st->permission[11] = '\0';
}

static void			set_mtime(time_t *mtime, t_stat *f_st)
{
	char			**s;
	char			**time_str;

	f_st->mtime = *mtime;
	s = ft_strsplit(ctime(mtime), ' ');
	time_str = ft_strsplit(s[3], ':');
	f_st->month = ft_strdup(s[1]);
	f_st->day = ft_strdup(s[2]);
	f_st->hour = ft_strdup(time_str[0]);
	f_st->min = ft_strdup(time_str[1]);
	ft_arraydel((void **)s);
	ft_arraydel((void **)time_str);
	free(s);
	free(time_str);
}

static void			ally_setter(t_stat *new)
{
	new->len[0] = num_len(new->nlink);
	new->len[1] = ft_strlen(new->pw_name);
	new->len[2] = ft_strlen(new->gr_name);
	new->len[3] = num_len(new->size);
	new->len[4] = ft_strlen(new->day);
	if (g_data.alley_mlen[0] < new->len[0] + 1)
		g_data.alley_mlen[0] = new->len[0] + 1;
	if (g_data.alley_mlen[1] < new->len[1] + 1)
		g_data.alley_mlen[1] = new->len[1] + 1;
	if (g_data.alley_mlen[2] < new->len[2] + 2)
		g_data.alley_mlen[2] = new->len[2] + 2;
	if (g_data.alley_mlen[3] < new->len[3] + 2)
		g_data.alley_mlen[3] = new->len[3] + 2;
	if (g_data.alley_mlen[4] < new->len[4] + 1)
		g_data.alley_mlen[4] = new->len[4] + 1;
}

t_stat				*new_tstat(struct stat file_stat)
{
	t_stat			*new;

	if (!(new = (t_stat *)malloc(sizeof(t_stat))))
		throw("malloc");
	set_permission(file_stat.st_mode, new);
	new->nlink = file_stat.st_nlink;
	new->pw_name = ft_strdup(getpwuid(file_stat.st_uid)->pw_name);
	new->gr_name = ft_strdup(getgrgid(file_stat.st_gid)->gr_name);
	new->size = file_stat.st_size;
	set_mtime(&file_stat.st_mtime, new);
	ally_setter(new);
	return (new);
}
