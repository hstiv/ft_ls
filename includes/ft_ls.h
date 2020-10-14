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
# define ASC	1
# define DESC	-1
# define ASCII	1
# define MTIME	2
# define SIZE	3
# define NOFILE "No such file or directory\n"
# define NOPEN	"Can not open directory"

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
	char 			permission[11];
	int				nlink;
	char 			*pw_name;
	char 			*gr_name;
	int 			size;
	int 			mtime;
	char 			*month;
	char 			*day;
	char 			*hour;
	char 			*min;
	int 			blocks;
	int 			len[5];
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
	int 			alley_mlen[5];
	t_file 			*arg_file;
	int				arg_files_count;
	int 			arg_dir_count;
}					t_data;

t_data				data;
char 				*curr_dir;

/*
**			srcs/option_reader.c			**
*/
void				arg_reader(int argc, char **argv);
/*
**			srcs/print_functions.c			**
*/
void				print(t_file *start, char print_one);
void 				print_l(t_file *file);
void 				print_dir_name(t_file *file);
void 				print_n_times(char c, int n);
/*
**				srcs/read_dir.c				**
*/
t_file				*read_dir(char *path);
t_file				*new_file(char *s);
char 				*path_with_f_name(char *filename, char *path);
char 				*rmladir(char *s);

/*
**					srcs/sort.c				**
*/
t_file				*only_dirs(t_file *head);
void 				sort(t_file *files, int sort_by);
/*
**				srcs/stats.c				**
*/
t_stat				*new_tstat(struct stat file_stat);
size_t 				num_len(int n);
/*
**				srcs/var_setters.c			**
*/
void				set_data(void);
void				del_file(t_file *node);
int 				throw(char *s);
void				swap_files(t_file *p1, t_file *p2);
/*
**					srcs/main.c				**
*/
void 				ft_ls(t_file *ptr);

#endif
