/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_temp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwu <hwu@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 16:29:23 by mrios-he          #+#    #+#             */
/*   Updated: 2024/08/03 12:49:05 by hwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define CMD  0
#define ARG  1
#define IFIL 2
#define HDOC 3
#define OUT1 4
#define OUT2 5
#define PIP  6
#define OR   7
#define AND  8
#define PAR1 9
#define PAR2 10

typedef	struct t_list
{
	char			*token;
	int				type;
	struct t_list	*prev;
	struct t_list	*next;
}	t_list;
typedef struct s_parser
{
    char	*input;
    t_list	**head;
    int		i;
    int		is_first;
    char	token[1024];
    int		j;
}	t_parser;

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
	return (rtn);
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
/*
 * The concatenate_tokens function takes three arguments: a pointer to a destination string, 
 * and two source strings. It concatenates the two source strings with a space in between, 
 * and stores the result in the destination string. If the destination string was previously 
 * allocated, it is freed and a new block of memory is allocated for the new string.
 * 
 * The function first calculates the length of the new string, which is the sum of the lengths 
 * of the two source strings plus 2 (one for the space and one for the null terminator). 
 * It then allocates a block of memory of this size.
 * 
 * The function then copies the characters from the first source string to the new string, 
 * followed by a space, and then the characters from the second source string. 
 * It adds a null terminator at the end.
 */
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
	else if (ft_strcmp(token, "<") == 0)
		append_node(head, token, IFIL);
	else if (ft_strcmp(token, "<<") == 0)
		append_node(head, token, HDOC);
	else if (ft_strcmp(token, ">") == 0)
		append_node(head, token, OUT1);
	else if (ft_strcmp(token, ">>") == 0)
		append_node(head, token, OUT2);
	else if (ft_strcmp(token, "|") == 0)
		append_node(head, token, PIP);
	else if (ft_strcmp(token, "&&") == 0)
		append_node(head, token, AND);
	else if (ft_strcmp(token, "||") == 0)
		append_node(head, token, OR);
	else if (ft_strcmp(token, "(") == 0)
		append_node(head, token, PAR1);
	else if (ft_strcmp(token, ")") == 0)
		append_node(head, token, PAR2);
	else if (is_command(token))
		append_node(head, token, CMD);
	else
		append_node(head, token, ARG);
}
/*
 * The add_token function is responsible for adding a token to the linked list of tokens.
 * It takes two arguments: a pointer to a t_parser struct and a flag indicating whether 
 * the current token should be combined with the previous one.
 *
 * The function first null-terminates the current token. If the combine flag is set, 
 * it finds the last node in the list and checks if its type is ARG. If it is, 
 * it reallocates memory for the token in the last node to accommodate the current token, 
 * and then appends the current token to it.
 *
 * If the combine flag is not set, or if the last node's type is not ARG, 
 * it calls the set_type function to add the current token as a new node in the list.
 *
 * Finally, it resets the index of the current token to 0, ready for the next token.
 */
void add_token(t_parser *parser, int combine)
{
    t_list	*last_node;
    size_t	old_length;

    parser->token[parser->j] = '\0';
    if (combine)
    {
        last_node = *parser->head;
        while (last_node && last_node->next)
            last_node = last_node->next;
        if (last_node && last_node->type == ARG)
        {
            old_length = ft_strlen(last_node->token);
            last_node->token = (char *)realloc(last_node->token, old_length + parser->j + 1);
            if (last_node->token == NULL)
            {
                printf("Memory allocation error\n");
                exit(1);
            }
            ft_memcpy(last_node->token + old_length, parser->token, parser->j + 1);
        } else
            set_type(parser->head, parser->token, parser->is_first);
    } else
        set_type(parser->head, parser->token, parser->is_first);
    parser->j = 0;
}

int is_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/*
 * The process_word_loop function is a helper function for process_word. 
 * It takes a pointer to a t_parser struct as its argument.
 *
 * The function iterates over the characters in the input string until it encounters a null 
 * character, a space, a quote, or an operator. For each character, it adds the character 
 * to the current token and increments the indices of the current character and the current token.
 *
 * The function returns the index of the current character in the input string after the loop ends.
 */
int process_word_loop(t_parser *parser)
{
    while (parser->input[parser->i] != '\0' && !ft_is_space(parser->input[parser->i])
        && parser->input[parser->i] != '\'' && parser->input[parser->i] != '"'
        && !is_operator(parser->input[parser->i]))
	{
        parser->token[parser->j++] = parser->input[parser->i++];
    }
    return (parser->i);
}

/*
 * The process_word function is responsible for processing a word in the input string.
 *
 * The function calls process_word_loop to add the characters of the word to the current token. 
 * It then calls add_token to add the token to the list, with the combine flag set to 0, 
 * indicating that the token should not be combined with the previous one.
 *
 * Finally, it resets the index of the current token to 0, ready for the next token.
 */
void process_word(t_parser *parser) {
    parser->i = process_word_loop(parser);
    add_token(parser, 0);
}

/*
 * The get_operator_token function is responsible for processing an operator in the input string. 
 * It takes three arguments: a pointer to the input string, a pointer to the current token, 
 * and a pointer to the index of the current character in the input string.
 *
 * The function first adds the current character to the token. If the current character is 
 * a '>' or '<', and the next character is the same, it adds the next character to the token as well.
 * If the current character is '&' or '|', and the next character is the same, it also adds 
 * the next character to the token.
 *
 * Finally, it null-terminates the token.
 */
void	get_operator_token(char *input, char *token, int *i)
{
	int	j;

	j = 0;
	token[j++] = input[(*i)++];
	if ((token[0] == '>' || token[0] == '<') && input[*i] == token[0])
		token[j++] = input[(*i)++];
	else if ((token[0] == '&' && input[*i] == '&') || (token[0] == '|'
		&& input[*i] == '|'))
		token[j++] = input[(*i)++];
	token[j] = '\0';
}

void	append_operator_token(char *token, t_list **head)
{
	if (ft_strcmp(token, "&&") == 0)
		append_node(head, token, AND);
	else if (ft_strcmp(token, "||") == 0)
		append_node(head, token, OR);
	else if (ft_strcmp(token, ">") == 0)
		append_node(head, token, OUT1);
	else if (ft_strcmp(token, ">>") == 0)
		append_node(head, token, OUT2);
	else if (ft_strcmp(token, "<") == 0)
		append_node(head, token, IFIL);
	else if (ft_strcmp(token, "<<") == 0)
		append_node(head, token, HDOC);
	else
		append_node(head, token, PIP);
}

/*
 * The process_operator function is responsible for processing an operator in the input string. 
 * It takes a pointer to a t_parser struct as its argument.
 *
 * The function first adds the current character to the token. If the current character is 
 * a '|' or '<' or '>', and the next character is the same, it adds the next character to the token as well.
 *
 * Finally, it calls add_token to add the token to the list, with the combine flag set to 0, 
 * indicating that the token should not be combined with the previous one.
 */
void process_operator(t_parser *parser)
{
    parser->token[parser->j++] = parser->input[parser->i++];
    if ((parser->token[parser->j - 1] == '|' && parser->input[parser->i] == '|') ||
        (parser->token[parser->j - 1] == '<' && parser->input[parser->i] == '<') ||
        (parser->token[parser->j - 1] == '>' && parser->input[parser->i] == '>'))
	{
        parser->token[parser->j++] = parser->input[parser->i++];
    }
    add_token(parser, 0);
}

/*
 * The process_quote_body function is a helper function for process_quotes. 
 * It takes a pointer to a t_parser struct and a character representing the quote type as its arguments.
 *
 * The function iterates over the characters in the input string until it encounters a matching quote 
 * character or a null character. For each character, it adds the character to the current token 
 * and increments the indices of the current character and the current token.
 *
 * The function returns the index of the current character in the input string after the loop ends.
 */
int process_quote_body(t_parser *parser, char quote_char)
{
    while (parser->input[parser->i] != quote_char && parser->input[parser->i] != '\0')
        parser->token[parser->j++] = parser->input[parser->i++];
    return (parser->i);
}

/*
 * The process_quotes function is responsible for processing a quoted string in the input string. 
 * It takes a pointer to a t_parser struct as its argument.
 *
 * The function first adds the opening quote to the token. It then calls process_quote_body to add 
 * the characters inside the quotes to the current token. If the current character in the input string 
 * is a matching quote, it adds the closing quote to the token.
 *
 * Finally, it calls add_token to add the token to the list, with the combine flag set to 0, 
 * indicating that the token should not be combined with the previous one.
 */
void process_quotes(t_parser *parser)
{
    char	quote_char;

	quote_char = parser->input[parser->i];
    parser->token[parser->j++] = quote_char;
    parser->i++;
    parser->i = process_quote_body(parser, quote_char);
    if (parser->input[parser->i] == quote_char)
	{
        parser->token[parser->j++] = quote_char;
        parser->i++;
    }
    if (parser->input[parser->i] == '\'' || parser->input[parser->i] == '"') {
        process_quotes(parser);
    } else {
        add_token(parser, 0);
    }
}

/*
 * The process_token function is responsible for processing a token in the input string. 
 * It takes a pointer to a t_parser struct as its argument.
 *
 * The function first checks the type of the current character in the input string. 
 * If it's a quote, it calls process_quotes to process a quoted string. 
 * If it's an operator, it calls process_operator to process an operator. 
 * Otherwise, it calls process_word to process a word.
 *
 * If the token being processed is the first one in the input string, 
 * the function sets the is_first flag to 0, indicating that the first token has been processed.
 */
void process_token(t_parser *parser)
{
    if (parser->input[parser->i] == '\'' || parser->input[parser->i] == '"')
	{
        process_quotes(parser);
    } else if (is_operator(parser->input[parser->i]))
        process_operator(parser);
    else
	{
        process_word(parser);
        if (parser->is_first)
            parser->is_first = 0;
    }
}

void tokenize_and_classify(t_list **head, char *input)
{
    t_parser parser;

    parser.input = input;
    parser.head = head;
    parser.i = 0;
    parser.is_first = 1;
    parser.j = 0;

    while (parser.input[parser.i] != '\0')
    {
        if (ft_is_space(parser.input[parser.i]))
            parser.i++;
        else
            process_token(&parser);
    }
}

/*
static void	print_list(t_list *head)
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
	char *input = " Hi (\"Hello, $USER!\" >  output.txt ) && cat \" ( output.txt ) \" >> log.txt || echo This  is a test | grep test | export VAR=123 | ' echo $VAR ' <<EOF\nLine1\nLine2\nEOF | export HELLO=123 A";
	tokenize_and_classify(&head, input);
	print_list(head);
	free_list(head);
	return 0;
}*/
