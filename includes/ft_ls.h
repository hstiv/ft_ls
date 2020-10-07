//
// Created by Hallie Stiv on 10/7/20.
//

#ifndef FT_LS_H
# define FT_LS_H

# include <stdint.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <sys/xattr.h>
# include <time.h>
# include "libft.h"

# define OPT	"lRart"
# define USAGE	"\nusage: ft_ls [-lRart] [file ...]\n"
# define IL_OPT	"ft_ls: illegal option -- "

/*
**_____________________Structure____________________*
**		1 - is present, in case 0 - flag is absent	*
**			option[0]:[-l];	option[1]:[-R];			*
**			option[2]:[-a];	option[3]:[-r];			*
**					option[4]:[-t].					*
**__________________________________________________*
*/

typedef struct 		s_data
{
	char			option[5];
	char 			**filenames;
	int 			file_count;

}					t_data;

void				set_data(t_data *data);
void				option_reader(int argc, char **argv, t_data *data);
void 				set_filename(char *s, t_data *data);

#endif
