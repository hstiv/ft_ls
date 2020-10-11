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

t_stat			*new_tstat(struct stat file_stat)
{
	t_stat		*new;

	if (!(new = (t_stat *)malloc(sizeof(t_stat))))
		throw("memory ERROR\n");
	set_permission(file_stat.st_mode, new);
	new->nlink = file_stat.st_nlink;
	new->pw_name = getpwuid(file_stat.st_uid)->pw_name;
	new->gr_name = getgrgid(file_stat.st_gid)->gr_name;
	new->size = file_stat.st_size;
	set_mtime(&file_stat.st_mtime, new);
	return (new);
}
