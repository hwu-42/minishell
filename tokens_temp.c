/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrios-he <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:29:23 by mrios-he          #+#    #+#             */
/*   Updated: 2024/07/27 16:29:33 by mrios-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ARG 0
#define CMD 1
#define RED 2
#define PIP 3
#define ENV 4
#define PAR 5
#define AND 6
#define OR 7

typedef	struct t_list {
	char			*token;
	int				type;
	struct t_list	*prev;
	struct t_list	*next;
}	t_list;

typedef	struct {
	char	*input;
	t_list	**head;
	int		*j;
	int		*i;
	char	word[1024];
	char	*token;
}	DollarSignParams;

typedef struct {
	char *input;
	t_list **head;
	char token[1024];
	int j;
} QuoteParams;

typedef struct {
    char *input;
    t_list **head;
    int *i;
    int *j;
    char token[1024];
} WordParams;

int	ft_strcmp(const char *s1, const char *s2)
{
	while ((*s1 && *s2) && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

size_t ft_strlen(const char *str)
{
	int count;

	count = 0;
	while (*str != '\0')
	{
		count++;
		str++;
	}
	return count;
}

int ft_isalnum(int c)
{
	return (isalpha(c) || isdigit(c));
}

void *ft_memcpy(void *dst, const void *src, size_t n)
{
	char *temp_dst = (char *)dst;
	const char *temp_src = (const char *)src;

	if ((dst == src) || n == 0)
		return dst;
	if (!dst && !src)
		return 0;
	while (n--)
		temp_dst[n] = temp_src[n];
	return dst;
}

char *ft_strdup(const char *s1)
{
	size_t	len;
	char	*rtn;

	len = ft_strlen(s1) + 1;
	rtn = malloc(sizeof(char) * len);
	if (rtn == NULL)
		return NULL;
	rtn = ft_memcpy(rtn, s1, len);
	return rtn;
}

t_list *create_node(const char *token, int type)
{
	t_list	*new_node;

	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
	{
		printf("Memory allocation error\n");
		exit(1);
	}
	new_node->token = ft_strdup(token);
	new_node->type = type;
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	concatenate_tokens(char **dest, const char *src1, const char *src2)
{
	size_t	new_len;
	char	*new_token;
	char	*p;

	new_len = ft_strlen(src1) + ft_strlen(src2) + 2;
	new_token = (char *)malloc(new_len);
	if (new_token == NULL)
	{
		printf("Memory allocation error\n");
		exit(1);
	}
	p = new_token;
	while (*src1 != '\0')
		*p++ = *src1++;
	*p++ = ' ';
	while (*src2 != '\0')
		*p++ = *src2++;
	*p = '\0';
	free(*dest);
	*dest = new_token;
}

t_list *find_last_node(t_list *head)
{
	while (head->next != NULL)
		head = head->next;
	return (head);
}

void append_node(t_list **head, const char *token, int type)
{
	t_list	*current;
	t_list	*new_node;
	
	if (*head == NULL)
		*head = create_node(token, type);
	else
	{
		current = find_last_node(*head);
		if (current->type == type)
			concatenate_tokens(&current->token, current->token, token);
		else
		{
			new_node = create_node(token, type);
			current->next = new_node;
			new_node->prev = current;
		}
	}
}

int ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\f' || c == '\v');
}

int	is_command(const char *token)
{
	char	*cmd[10];
	int		i;

	cmd[0] = "echo";
	cmd[1] = "cd";
	cmd[2] = "pwd";
	cmd[3] = "export";
	cmd[4] = "unset";
	cmd[5] = "env";
	cmd[6] = "exit";
	cmd[7] = "ls";
	cmd[8] = "grep";
	cmd[9] = "cat";
	i = 0;
	while (i < 10)
	{
		if (ft_strcmp(cmd[i], token) == 0)
			return (1);
		i++;
	}
	return (0);
}

void set_type(t_list **head, const char *token, int is_first)
{
	if (is_first)
		append_node(head, token, CMD);
	else if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0
		|| ft_strcmp(token, ">>") == 0 || ft_strcmp(token, "<<") == 0)
		append_node(head, token, RED);
	else if (ft_strcmp(token, "|") == 0)
		append_node(head, token, PIP);
	else if (ft_strcmp(token, "&&") == 0)
		append_node(head, token, AND);
	else if (ft_strcmp(token, "||") == 0)
		append_node(head, token, OR);
	else if (ft_strcmp(token, "(") == 0 || ft_strcmp(token, ")") == 0)
		append_node(head, token, PAR);
	else if (token[0] == '$')
		append_node(head, token, ENV);
	else if (is_command(token))
		append_node(head, token, CMD);
	else
		append_node(head, token, ARG);
}

void add_token(t_list **head, char *token, int *j, int is_first, int combine)
{
	t_list	*last_node;
	size_t	old_length;

	token[*j] = '\0';
	if (combine)
	{
		last_node = *head;
		while (last_node && last_node->next)
			last_node = last_node->next;
		if (last_node && last_node->type == ARG)
		{
			old_length = ft_strlen(last_node->token);
			last_node->token = (char *)realloc(last_node->token, old_length + *j + 1);
			if (last_node->token == NULL)
			{
				printf("Memory allocation error\n");
				exit(1);
			}
			ft_memcpy(last_node->token + old_length, token, *j + 1);
		} else
			set_type(head, token, is_first);
	} else
		set_type(head, token, is_first);
	*j = 0;
}

int is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void handle_dollar_sign_in_word(WordParams *params, int is_first)
{
    if (*(params->j) > 0)
        add_token(params->head, params->token, params->j, is_first, 0);
    params->token[(*(params->j))++] = params->input[(*(params->i))++];
    while (ft_isalnum(params->input[*(params->i)]) || params->input[*(params->i)] == '{')
        params->token[(*(params->j))++] = params->input[(*(params->i))++];
    params->token[*(params->j)] = '\0';
    append_node(params->head, params->token, ENV);
    *(params->j) = 0;
}


int process_word_loop(WordParams *params, int is_first, int *is_env_var)
{
    while (params->input[*(params->i)] != '\0' && !ft_is_space(params->input[*(params->i)])
		&& params->input[*(params->i)] != '\'' && params->input[*(params->i)] != '"'
		&& !is_operator(params->input[*(params->i)]))
	{
        if (params->input[*(params->i)] == '$')
		{
            *is_env_var = 1;
            handle_dollar_sign_in_word(params, is_first);
        }
		else
            params->token[(*(params->j))++] = params->input[(*(params->i))++];
    }
    return *(params->i);
}


int process_word(char *input, t_list **head, int start, int is_first)
{
    WordParams params;
    int i;
    int j;
    int is_env_var;

    i = start;
    j = 0;
    is_env_var = 0;
    params.input = input;
    params.head = head;
    params.i = &i;
    params.j = &j;
    process_word_loop(&params, is_first, &is_env_var);
    if (j > 0)
        add_token(head, params.token, &j, is_first, is_env_var);
    return (i - start);
}

int	process_operator(char *input, t_list **head, int start)
{
	char	token[3];
	int		i;
	int		j;

	i = start;
	j = 0;
	token[j++] = input[i++];
	if ((token[0] == '>' || token[0] == '<') && input[i] == token[0])
		token[j++] = input[i++];
	else if ((token[0] == '&' && input[i] == '&')
		|| (token[0] == '|' && input[i] == '|'))
		token[j++] = input[i++];
	token[j] = '\0';
	append_node(head, token, (ft_strcmp(token, "&&") == 0) ? AND : (ft_strcmp(token, "||") == 0) ? OR : PIP);
	return (i - start);
}

int	handle_dollar_sign(DollarSignParams params, int i, char quote_char)
{
	int start;
	int j;

	start = 1;
	j = 0;
	params.token[j++] = params.input[i++];
	while (params.input[i] != '\0' && (ft_isalnum(params.input[i])
		|| params.input[i] == '_'))
	{
		if (j < 1023)
			params.token[j++] = params.input[i++];
		else
			break ;
	}
	params.token[j] = '\0';
	add_token(params.head, params.token, &j, 0, 0);
	return (i);
}

void process_quote_body(QuoteParams *params, char quote_char, int *i, int is_first)
{
	while (params->input[*i] != quote_char && params->input[*i] != '\0')
	{
		if (quote_char == '\'')
			params->token[params->j++] = params->input[(*i)++];
		else if (quote_char == '"')
		{
			if (params->input[*i] == '$')
			{
				if (params->j > 0)
					add_token(params->head, params->token, &params->j, is_first, 0);
				params->token[params->j++] = params->input[(*i)++];
				while (isalnum(params->input[*i]) || params->input[*i] == '_')
					params->token[params->j++] = params->input[(*i)++];
				params->token[params->j] = '\0';
				append_node(params->head, params->token, ENV);
				params->j = 0;
			}
			else
				params->token[params->j++] = params->input[(*i)++];
		}
	}
}

int	process_quotes(char *input, t_list **head, int start, int is_first)
{
	QuoteParams params;
	int		i;
	char quote_char;

	params.input = input;
	params.head = head;
	params.j = 0;
	i = start;
	quote_char = input[i++];
	process_quote_body(&params, quote_char, &i, is_first);
	if (input[i] == quote_char)
		i++;
	if (params.j > 0)
	{
		params.token[params.j] = '\0';
		if (quote_char == '\'')
			append_node(params.head, params.token, ARG);
		else
			add_token(params.head, params.token, &params.j, is_first, 0);
	}
	return (i - start);
}

void	process_token(char *input, t_list **head, int *i, int *is_first)
{
	DollarSignParams params;

	if (input[*i] == '\'' || input[*i] == '"')
		*i += process_quotes(input, head, *i, *is_first);
	else if (is_operator(input[*i]))
		*i += process_operator(input, head, *i);
	else
	{
		if (input[*i] == '$')
		{
			params.input = input;
			params.head = head;
			params.i = i;
			params.token = malloc(1024);
			*i = handle_dollar_sign(params, *i, 0);
			free(params.token);
		}
		else
			*i += process_word(input, head, *i, *is_first);
		if (*is_first)
			*is_first = 0;
	}
}

void	tokenize_and_classify(char *input, t_list **head)
{
	int is_first;
	int i;

	is_first = 1;
	i = 0;
	while (input[i] != '\0')
	{
		while (ft_is_space(input[i]))
			i++;
		if (input[i] != '\0')
			process_token(input, head, &i, &is_first);
	}
}


void	print_list(t_list *head)
{
	t_list	*current;

	current = head;
	while (current != NULL) {
		printf("Token: %s, Type: %d\n", current->token, current->type);
		current = current->next;
	}
}

void	free_list(t_list *head)
{
	t_list	*tmp;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->token);
		free(tmp);
	}
}

int main(void)
{
	t_list *head = NULL;
	char *input = " Hi (\"Hello, $USER!\" >  output.txt ) && cat \" ( output.txt ) \" >> log.txt || echo This is a test | grep test | export VAR=123 | ' echo $VAR ' <<EOF\nLine1\nLine2\nEOF";
	tokenize_and_classify(input, &head);
	print_list(head);
	free_list(head);
	return 0;
}
