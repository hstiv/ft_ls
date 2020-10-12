#include "ft_ls.h"

void 				ft_ls(t_file *ptr)
{
	t_file			*files;

	files = ptr;
	sort(files, (data.option[4]) ? MTIME : ASCII);
	print(files);
	if (data.option[1] == 1)
	{
		ptr = only_dirs(files);
		files = ptr;
		while (files)
		{
			ft_ls(read_dir(files->filename));
			files = files->next;
		}
	}
}

void 				arg_handler(void)
{

}

int					main(int argc, char **argv)
{
	t_file			*files;

	set_data();
	(argc > 1 && argv[1] != NULL) ? arg_reader(argc, argv) : 0;
	if (data.arg_files_count == 0)
		ft_ls(read_dir("."));
	else
		arg_handler();
//	sort(files, ASC, ASCII);
//	files = reverse_list(files);
//	while (files)
//	{
//		write(1, files->filename, ft_strlen(files->filename));
//		write(1, "\t", 1);
//		files = files->next;
//	}
//	write(1, "\n", 1);
	return (0);
}
