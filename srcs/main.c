#include "ft_ls.h"

static void			ls(char *path)
{
	DIR				*dirp;

	dirp = opendir(path);
	read_dir(dirp);
	closedir(dirp);
}

int					main(int argc, char **argv)
{
	t_file			files;
	set_data();
	if (argc > 1 && argv[1] != NULL)
		arg_reader(argc, argv);
//	if (data.file_count > 0)
//	{
//		sort_files();
//		files = data.files;
//		while (files)
//		{
//
//		}
//	}
//	t_file *file = data.file;
//	while (file != NULL)
//	{
//		printf("%s ", file->filename);
//		file = file->next;
//	}
	ls(".");
	return (0);
}
