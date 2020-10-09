#include "ft_ls.h"

static void 		print_permission(mode_t st_mode)
{
	write(1, (S_ISDIR(st_mode)) ? "d" : "-", 1);
	write(1, (st_mode & S_IRUSR) ? "r" : "-", 1);
	write(1, (st_mode & S_IWUSR) ? "w" : "-", 1);
	write(1, (st_mode & S_IXUSR) ? "x" : "-", 1);
	write(1, (st_mode & S_IRGRP) ? "r" : "-", 1);
	write(1, (st_mode & S_IWGRP) ? "w" : "-", 1);
	write(1, (st_mode & S_IXGRP) ? "x" : "-", 1);
	write(1, (st_mode & S_IROTH) ? "r" : "-", 1);
	write(1, (st_mode & S_IWOTH) ? "w" : "-", 1);
	write(1, (st_mode & S_IXOTH) ? "x" : "-", 1);
}

static void 		print_mtime(time_t st_mtime)
{
	//YOU STOPPED HERE
}

static void			show_curr_dir()
{
	DIR				*dirp;
	struct dirent	*el;
	struct stat 	fileStat;
	struct passwd	user;

	dirp = opendir(".");
	while ((el = readdir(dirp)) != NULL)
	{
		stat(el->d_name, &fileStat);
		print_permission(fileStat.st_mode);
		write(1, "  ", 2);
		ft_putnbr(fileStat.st_nlinks);
		write(1, " ", 1);
		ft_putstr(getpwuid(fileStat.st_uid)->pw_name);
		write(1, "  ", 2);
		ft_putstr(getgrgid(fileStat.st_uid)->gr_name);
		write(1, "  ", 2);
		ft_putnbr(fileStat.st_size);
		write(1, " ", 1);
		print_mtime(fileStat.st_mtime);
	}
	closedir(dirp);
}

int					main(int argc, char **argv)
{
	set_data();
	if (argc > 1 && argv[1] != NULL)
		arg_reader(argc, argv);
	t_file *file = data.file;
//	while (file != NULL)
//	{
//		printf("%s ", file->filename);
//		file = file->next;
//	}
	show_curr_dir();
	return (0);
}
