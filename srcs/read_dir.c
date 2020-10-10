#include "ft_ls.h"

static void 		set_permission(mode_t st_mode, t_stat *f_st)
{
	f_st->permission[0] = (S_ISDIR(st_mode)) ? 'd' : '-';
	f_st->permission[1] = (st_mode & S_IRUSR) ? 'r' : '-';
	f_st->permission[2] = (st_mode & S_IWUSR) ? 'w' : '-';
	f_st->permission[3] = (st_mode & S_IXUSR) ? 'x' : '-';
	f_st->permission[4] = (st_mode & S_IRGRP) ? 'r' : '-';
	f_st->permission[5] = (st_mode & S_IWGRP) ? 'w' : '-';
	f_st->permission[6] = (st_mode & S_IXGRP) ? 'x' : '-';
	f_st->permission[7] = (st_mode & S_IROTH) ? 'r' : '-';
	f_st->permission[8] = (st_mode & S_IWOTH) ? 'w' : '-';
	f_st->permission[9] = (st_mode & S_IXOTH) ? 'x' : '-';
}

static void 		set_mtime(time_t *mtime, t_stat *f_st)
{
	char			**s;
	char 			**time_str;

	s = ft_strsplit(ctime(mtime), ' ');
	time_str = ft_strsplit(s[3], ':');
	f_st->month = ft_strdup(s[1]);
	f_st->day = ft_strdup(s[2]);
	f_st->hour = ft_strdup(time_str[0]);
	f_st->min = ft_strdup(time_str[1]);
	ft_arraydel((void **)s);
	ft_arraydel((void **)time_str);
}

static t_stat		*def_st(t_stat *f_st)
{
	if (data.f_stat == NULL)
	{
		data.f_stat = new_tstat();
		return (data.f_stat);
	}
	f_st->next = new_tstat();
	f_st->next->prev = f_st;
	return (f_st->next);
}

void 				put_stats(t_stat *f_st, struct stat file_stat)
{
	set_permission(file_stat.st_mode, f_st);
	f_st->nlink = file_stat.st_nlink;
	f_st->pw_name = getpwuid(file_stat.st_uid)->pw_name;
	f_st->gr_name = getgrgid(file_stat.st_gid)->gr_name;
	f_st->size = file_stat.st_size;
	set_mtime(&file_stat.st_mtime, f_st);
}

void 				read_dir(DIR *dirp)
{
	t_stat			*f_st;
	struct	stat 	file_stat;
	struct	dirent	*el;

	f_st = NULL;
	while ((el = readdir(dirp)) != NULL)
	{
		if (!data.option[2] && el->d_name[0] == '.')
			continue ;
		f_st = def_st(f_st);
		stat(el->d_name, &file_stat);
		put_stats(f_st, file_stat);
		f_st->name = el->d_name;
	}
}
