#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* to  read/or write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 when using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: which is the number field
 * @str: is a string
 * @next: which it points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - just contains pseudo-arguements to pass into function,
 * allowing uniforming the  prototype for function pointer struct
 * @arg: which is a string generated from getline containing arguements
 * @argv:an array of strings generated from arg
 * @path: is a string which path for the current command
 * @argc: being the argument count
 * @line_count: produces an error count
 * @err_num: an error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: which is the program filename
 * @env: a linked list local copy of environ
 * @environ: as a custom modified copy of environ from LL env
 * @history: which is the history node
 * @alias: is the alias node
 * @env_changed: on if environ was changed
 * @status: it gives the return status of the last exec'd command
 * @cmd_buf: being the address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: to read the fd from which to read line input
 * @histcount: being the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - which it contains a builtin string and related function
 * @type: act as the builtin command flag
 * @func: which is the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;


int interact(info_t *);
int to_delimate(char, char *);
int _alphacar(int);
int _convst(char *);

int _exsh(info_t *);
int _changdir(info_t *);
int _chpro(info_t *);

int _strlengh(char *);
int _strcompare(char *, char *);
char *starts_by(const char *, const char *);
char *_strconcat(char *, char *);

char *_strcopy(char *, char *);
char *_strduppl(const char *);
void _pri(char *);
int _writechar(char);

int rep_str(char **, char *);
int rep_vars(info_t *);
int rep_alias(info_t *);
void ch_chain(info_t *, char *, size_t *, size_t, size_t);
int jk_chain(info_t *, char *, size_t *);

char **splitstr(char *, char *);
char **splitstr2(char *, char);

int msh(info_t *, char **);
int find_builtincm(info_t *);
void find_cmdp(info_t *);
void fork_cmdx(info_t *);

char *_memcon(char *, char, unsigned int);
void freest(char **);
void *_reallocate(void *, unsigned int, unsigned int);

int det_cmd(info_t *, char *);
char *duppl_chars(char *, int, int);
char *find_apath(info_t *, char *, char *);

int pofree(void **);

size_t link_len(const list_t *);
char **list_of_strings(list_t *);
size_t print_elem(const list_t *);
list_t *node_starts_pref(list_t *, char *, char);
ssize_t get_n_index(list_t *, list_t *);

list_t *add_a_node(list_t **, const char *, int);
list_t *add_node_to_end(list_t **, const char *, int);
size_t print_alist_str(const list_t *);
int delete_node_in_index(list_t **, unsigned int);
void free_nodlist(list_t **);


char *get_history_file(info_t *inf);
int create_history(info_t *inf);
int renum_history(info_t *inf);
int build_hist_list(info_t *inf, char *buff, int linecount);
int read_hist(info_t *inf);

void clear_inform(info_t *);
void set_inform(info_t *, char **);
void free_inform(info_t *, int);


char **get_envir(info_t *);
int _unsetenv(info_t *, char *);
int _setenvar(info_t *, char *, char *);

ssize_t get_lininput(info_t *);
int _getnxline(info_t *, char **, size_t *);
void sigintHandler(int);


char *strn_cpy(char *, char *, int);
char *str_cat(char *, char *, int);
char *loc_str(char *, char);
int conv_st(char *);
void print_err(info_t *, char *);
int print_dec(int, int);
char *conv_num(long int, int, int);
void rep_fir(char *);

void prin_instr(char *);
int writ_chr(char);
int chr_wr(char, int);
int inp_str(char *, int);

int cur_env(info_t *);
char *get_env(info_t *, const char *);
int inith_env(info_t *);
int rem_env(info_t *);
int pop_env_lis(info_t *);

int alias_set(info_t *, char *);
int dis_hist(info_t *);
int ali_man(info_t *);
int print_alstr(list_t *);
int set_ali(info_t *, char *);

int exi_shel(info_t *);
int ch_crdir(info_t *);
int pro_ch_dir(info_t *);



#endif
