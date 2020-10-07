#include "ft_ls.h"

int					main(int argc, char **argv)
{
	t_data			ls;

	if (argc > 1)
		option_reader(argc, argv, &ls);
	return (0);
}