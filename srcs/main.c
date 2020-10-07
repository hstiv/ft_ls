#include "ft_ls.h"

static void 		output(int argc, char **argv, t_data *data)
{
	int i;

	i = 0;
	while (++i < argc)
		set_filename(argv[i], data);
}

int					main(int argc, char **argv)
{
	t_data			ls;

	if (argc > 1 && argv[1] != NULL && argv[1][0] == '-')
		option_reader(argc, argv, &ls);
	else if (argc > 1)
		output(argc, argv, &ls);
	else

	return (0);
}