/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:12:04 by ffreze            #+#    #+#             */
/*   Updated: 2023/11/15 17:42:22 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_data				t_data;
typedef struct s_parsing_commands	t_parsing_cmd;
typedef struct s_parsing_file		t_parsing_file;

typedef enum e_parsing_token
{
	PIPE,
	R_IN,
	R_OUT,
	C_IN,
	C_OUT,
}			t_parsing_token;

struct s_parsing_file
{
	char			*file_name;
	char			*here_doc_end;
	int				fd;
	t_parsing_token	type;
	t_parsing_file	*next;
};

struct s_parsing_commands
{
	t_parsing_cmd	*next;
	t_parsing_cmd	*prev;
	pid_t			pid;
	char			**cmd;
	int				(*builtin)(t_data *, t_parsing_cmd *);
	char			*here_doc_fname;
	int				fin;
	int				fout;
	t_parsing_file	*files;
};

typedef struct s_expands_parsing
{
	int		i;
	int		quoted;
	int		read_env;
	char	*token;
	char	*res;
}				t_expands_p;

/**/

int		ft_push_new_file(t_parsing_cmd *cmd, char *file_name,
			t_parsing_token type, char *here_doc_end);

/**/

int		ft_push_new_command(t_data *minishell, char *line);

/* expands */

char	**ft_pipe_split(char *arg, int *c);
int		check_quotes(char *string);
char	**ft_split_cmd(char *arg);
char	*ft_parse_expands(t_data *minishell, char *arg, int t);

/* free parsing linked list */

void	ft_destroy_parsing_files(t_parsing_cmd	*cmd);
void	ft_destroy_parsing_cmd(t_data *minishell);

/* utils */

int		get_env_var_token(t_data *ms, char *line,
			t_expands_p *p, int q);
char	**ft_joinf_tab(char **tab, char *str);
int		is_redir_token(char *cmd);

#endif /* PARSING_H */	