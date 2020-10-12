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

typedef	struct		s_stack
{
	t_file			*file;
	struct s_stack	*next;
}					t_stack;


t_data				data;
t_stack				*stack;

void				set_data(void);
void				arg_reader(int argc, char **argv);
int 				throw(char *s);
t_file				*new_file(char *s);
t_stat				*new_tstat(struct stat file_stat);
t_file				*read_dir(char *path);
void 				sort(t_file *files, int sort_by);
void				add_stack(t_file *file);
void				print(t_file *start, char print_one);
void 				print_l(t_file *file);
t_file				*only_dirs(t_file *head);
void				del_file(t_file *node);
void				swap_files(t_file *p1, t_file *p2);
size_t 				num_len(int n);
void 				print_n_times(char c, int n);
void 				arg_handler(void);

#endif
