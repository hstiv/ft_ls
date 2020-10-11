#include "ft_ls.h"

//void 				ft_ls(t_file *files)
//{
//
//}

int					main(int argc, char **argv)
{
	t_file			*files;

	set_data();
	(argc > 1 && argv[1] != NULL) ? arg_reader(argc, argv) : 0;
	if (data.arg_files_count == 0)
		files = read_dir(".");
	sort_files(files);
	while (files)
	{
		write(1, files->filename, ft_strlen(files->filename));
		write(1, "\t", 1);
		files = files->next;
	}
	write(1, "\n", 1);
	return (0);
}
