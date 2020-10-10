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
# include <sys/errno.h>
#include <grp.h>
# include "libft.h"

# define OPT	"lRart"
# define USAGE	"\nusage: ft_ls [-lRart] [file ...]\n"
# define IL_OPT	"ft_ls: illegal option -- "
# define NOFILE "No such file or directory\n"

/*
**_____________________Structure____________________*
**		1 - is present, in case 0 - flag is absent	*
**			option[0]:[-l];	option[1]:[-R];			*
**			option[2]:[-a];	option[3]:[-r];			*
**					option[4]:[-t].					*
**__________________________________________________*
*/

extern int errno;

typedef struct 		s_stat
{
	char 			permission[10];
	int				nlink;
	char 			*pw_name;
	char 			*gr_name;
	int 			size;
	char 			*month;
	char 			*day;
	char 			*hour;
	char 			*min;
	char 			*name;
	struct	s_stat	*next;
	struct	s_stat	*prev;
}					t_stat;

typedef	struct		s_file
{
	char 			*filename;
	t_stat			*f_stat;
	struct	s_file	*prev;
	struct	s_file	*next;

}					t_file;

typedef struct 		s_data
{
	char			option[5];
	int 			alley_mlen[3];
	t_file 			*files;
	t_file			*dirs;
	int 			file_count;
	int				dir_count;
	t_stat			*f_stat;
}					t_data;

t_data				data;

void				set_data(void);
void				arg_reader(int argc, char **argv);
int 				throw(char *s);
t_file				*new_file(char *s);
t_stat				*new_tstat(void);
void 				read_dir(DIR *dirp);
void 				sort_files(void);
void 				put_stats(t_stat *f_st, struct stat file_stat);


#endif
