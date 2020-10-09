#include "ft_ls.h"

int					main(int argc, char **argv)
{

	set_data();
	if (argc > 1 && argv[1] != NULL)
		arg_reader(argc, argv);
	return (0);
}