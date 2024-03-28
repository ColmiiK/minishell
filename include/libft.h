/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvega-g <alvega-g@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 11:56:19 by alvega-g          #+#    #+#             */
/*   Updated: 2024/03/28 11:30:13 by alvega-g         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdbool.h>
# include <limits.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/**
 * @brief	Checks if passed variable is an alphabetic character,
 * 			returning 1 if it is and 0 if it isn't
 *
 * @param c Character to check
 * @return int
 */
int					ft_isalpha(int c);

/**
 * @brief	Checks if passed variable is a digit,
 * 			returning 1 if it is and 0 if it isn't
 *
 * @param c Character to check
 * @return int
 */
int					ft_isdigit(int c);

/**
 * @brief 	Checks if passed variable is an alphanumeric character,
 * 			returning 1 if it is and 0 if it isn't
 *
 * @param c Character to check
 * @return int
 */
int					ft_isalnum(int c);

/**
 * @brief 	Checks if passed variable is an ASCII character (0-255),
 * 			returning 1 if it is and 0 if it isn't
 *
 * @param c Character to check
 * @return int
 */
int					ft_isascii(int c);

/**
 * @brief 	Checks if passed character is a printable ASCII character,
 * 			returning 1 if it is and 0 if it isn't
 *
 * @param c Character to check
 * @return int
 */
int					ft_isprint(int c);

/**
 * @brief 	Returns the total size of the string passed,
		defined as the number of
 * 			characters before a null terminator
 *
 * @param str String to check
 * @return size_t
 */
size_t				ft_strlen(const char *str);

/**
 * @brief 	Sets the memory occupied by a string to the value of an integer
 * 			for as many characters as indicated, returning the modified string
 *
 * @param str String in memory to be modified
 * @param c Character to replace said string
 * @param len How many characters to replace
 * @return void*
 */
void				*ft_memset(void *str, int c, size_t len);

/**
 * @brief 	Modifies a string in memory by replacing a set amount of
 * characters with null, returning said modified string
 *
 * @param str String to be modified
 * @param n Amount of characters to modify
 * @return void*
 */
void				*ft_bzero(void *str, size_t n);

/**
 * @brief Copies a given amount of characters from one string in
 * memory to another, returning the modified string
 *
 * @param dst String to copy to
 * @param src String to copy from
 * @param n Number of characters to copy
 * @return void*
 */
void				*ft_memcpy(void *dst, const void *src, size_t n);

/**
 * @brief Non-destructively copies a given amount of characters from one
 * string in memory to another, returning said modified string
 *
 * @param dst String to copy to
 * @param src String to copy from
 * @param len Amount of characters to copy
 * @return void*
 */
void				*ft_memmove(void *dst, const void *src, size_t len);

/**
 * @brief Copies a given amount of characters from one string to another,
 * returning the size of the original string to copy from
 *
 * @param dest String to copy to
 * @param src String to copy from
 * @param size Amount of characters to copy
 * @return size_t
 */
size_t				ft_strlcpy(char *dest, const char *src, size_t size);

/**
 * @brief Concatenates a given amount of characters from one string to another,
 * returning the size of the original string to concatenate from
 *
 * @param dest String to be concatenated to
 * @param src String to concatenate from
 * @param size Amount of characters to concatenate
 * @return size_t
 */
size_t				ft_strlcat(char *dest, const char *src, size_t size);

/**
 * @brief Transforms a letter to uppercase if possible, returning said letter
 *
 * @param c Character to transform
 * @return int
 */
int					ft_toupper(int c);

/**
 * @brief Transforms a letter to lowercase if possible, returning said letter
 *
 * @param c Character to transform
 * @return int
 */
int					ft_tolower(int c);

/**
 * @brief Checks for a given character in a string, returning a
 * pointer to the first occurrence of the character
 * if it's found or null if it isn't
 *
 * @param s String to check
 * @param c Character to find
 * @return char*
 */
char				*ft_strchr(const char *s, int c);

/**
 * @brief Checks for a given character in a string, returning a
 * pointer to the last occurrence of the character
 * if it's found or null if it isn't
 *
 * @param s String to check
 * @param c Character to find
 * @return char*
 */
char				*ft_strrchr(const char *s, int c);

/**
 * @brief Compares two strings for a given amount of characters, returning the
 * difference of the values of the first characters that are different, or
 * null if there isn't any difference
 *
 * @param s1 First string to compare
 * @param s2 Second string to compare
 * @param n Amount of characters to compare
 * @return int
 */
int					ft_strncmp(const char *s1, const char *s2, size_t n);

/**
 * @brief For an amount of given characters, checks for a given character
 * in an array of memory, returning a pointer to the first occurrence of
 * the character if it's found or null if it isn't
 *
 * @param s String to check
 * @param c Character to find
 * @param n Amount of characters to check
 * @return void*
 */
void				*ft_memchr(const void *s, int c, size_t n);

/**
 * @brief Compares two arrays in memory for a given amount of characters,
 * returning the difference of the values of the first characters that are
 * different, or null if there isn't any difference
 *
 * @param s1 First string to compare
 * @param s2 Second string to compare
 * @param n Amount of characters to compare
 * @return int
 */
int					ft_memcmp(const void *s1, const void *s2, size_t n);

/**
 * @brief Finds a given string in another string for a set amount of
 * characters, returning a pointer to the start of the found string
 * if it appears or null if it doesn't. If the string to find is
 * empty, it returns the first string
 *
 * @param haystack String to search in
 * @param needle String to find
 * @param len Amount of characters to search
 * @return char*
 */
char				*ft_strnstr(const char *haystack, const char *needle,
						size_t len);

/**
 * @brief Transforms a string of numbers into an integer, returning
 * said integer. It skips control characters and spaces until it
 * finds a digit, stopping if it finds anything else other than a digit.
 *
 * @param str String to transform
 * @return int
 */
int					ft_atoi(const char *str);

/**
 * @brief Allocates a set amount of memory of a specific size,
 * initializing it with null terminators and returning a pointer
 * to the start of said memory
 *
 * @param n Amount of spaces in memory
 * @param size Size of those spaces
 * @return void*
 */
void				*ft_calloc(size_t n, size_t size);

/**
 * @brief Duplicates a string from stack memory to heap memory,
 * allocating as needed and returning a pointer to said heap memory
 *
 * @param s String to duplicate
 * @return char*
 */
char				*ft_strdup(const char *s);

/**
 * @brief Copies a set amount of characters from a string given
 * a starting position, duplicating and allocating it, returning
 * said subsection
 *
 * @param s String to copy from
 * @param start Index to start copying from
 * @param len Amount of characters to copy
 * @return char*
 */
char				*ft_substr(char const *s, unsigned int start, size_t len);

/**
 * @brief Concatenates two strings into a third, new dynamically allocated one,
 * returning said string
 *
 * @param s1 First string to concatenate
 * @param s2 Second string to concatenate
 * @return char*
 */
char				*ft_strjoin(char const *s1, char const *s2);

/**
 * @brief Concatenates two strings into a third, new dynamically allocated one,
 * returning said string and possibly freeing the passed strings
 *
 * @param s1 First string to concatenate
 * @param s2 Second string to concatenate
 * @param del Which string to free, 0 being none, 1 being the first, 2 being
 * the second one and 3 being both
 * @return char*
 */
char				*ft_strjoin_ex(char *s1, char *s2, int del);

/**
 * @brief Removes selected characters from the beginning and end of a string,
 * returning the new dynamically allocated trimmed string
 *
 * @param s1 String to trim
 * @param set Characters to remove
 * @return char*
 */
char				*ft_strtrim(char const *s1, char const *set);

/**

 * @brief Separates a string into substrings when encountering a 
 * given character, returning a 2D array of said substrings
 *
 * @param s String to separate
 * @param c Character that delimitates the strings
 * @return char**
 */
char				**ft_split(char const *s, char c);

/**
 * @brief Transforms an integer into a string, allocating and
 * returning said string
 *
 * @param n Integer to transform
 * @return char*
 */
char				*ft_itoa(int n);

/**
 * @brief Applies a given function to all characters of a string,
 * returning the new allocated transformed string
 *
 * @param s String to transform
 * @param f Function to apply
 * @return char*
 */
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

/**
 * @brief Applies a given function to all characters of a string,
 * returning the new transformed string
 *
 * @param s String to transform
 * @param f Function to apply
 */
void				ft_striteri(char *s, void (*f)(unsigned int, char *));

/**
 * @brief Writes a character into a given file descriptor
 *
 * @param c Character to write
 * @param fd File descriptor to write to
 */
void				ft_putchar_fd(char c, int fd);

/**
 * @brief Writes a string into a given file descriptor
 *
 * @param s String to write
 * @param fd File descriptor to write to
 */
void				ft_putstr_fd(char *s, int fd);

/**
 * @brief Writes a string into a given file descriptor,
 * adding a newline at the end
 *
 * @param s String to write
 * @param fd File descriptor to write to
 */
void				ft_putendl_fd(char *s, int fd);

/**
 * @brief Writes an integer into a given file descriptor
 *
 * @param n Integer to write
 * @param fd File descriptor to write to
 */
void				ft_putnbr_fd(int n, int fd);

/**
 * @brief Creates a node with a given content, making it point
 * to null
 *
 * @param content Content to add to the node
 * @return t_list*
 */
t_list				*ft_lstnew(void *content);

/**
 * @brief Adds a given node to the head of the given list
 *
 * @param lst List to put the node on top
 * @param new Node to place
 */
void				ft_lstadd_front(t_list **lst, t_list *new);

/**
 * @brief Returns the current amount of nodes in a list
 *
 * @param lst List to search
 * @return int
 */
int					ft_lstsize(t_list *lst);

/**
 * @brief Returns the current last node in a list
 *
 * @param lst List to find the last node of
 * @return t_list*
 */
t_list				*ft_lstlast(t_list *lst);

/**
 * @brief Adds a node to the end of a given list
 *
 * @param lst List to place the node on
 * @param new Node to place at the end
 */
void				ft_lstadd_back(t_list **lst, t_list *new);

/**
 * @brief Deletes a given node of a list
 *
 * @param lst Node to delete
 * @param del Function to delete and free the node
 */
void				ft_lstdelone(t_list *lst, void (*del)(void *));

/**
 * @brief Deletes and clears a given list
 *
 * @param lst List to delete and clear
 * @param del Function to delete and free the list with
 */
void				ft_lstclear(t_list **lst, void (*del)(void *));

/**
 * @brief Applies a given function to the nodes of a list
 *
 * @param lst Node to start the application from
 * @param f Function to apply
 */
void				ft_lstiter(t_list *lst, void (*f)(void *));

/**
 * @brief Applies a given function to a list, deleting and clearing the
 * list in case of failure
 *
 * @param lst List to transform
 * @param f Function to apply
 * @param del Function to delete and clear
 * @return t_list*
 */
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));

/**
 * @brief Writes a number in a given base
 *
 * @param nbr Int to write
 * @param base Base to write in
 */
void				ft_putnbr_base(int nbr, char *base);

/**
 * @brief Prints any number of arguments to the standard output. Supports 
 conversions like %s, %c, %i, %u, %x, %X, %p and %%. Doesn't support
 modifying flags nor returns -1 on error.
 * 
 * @param input Sring to print
 * @param ... Any number of arguments to print
 * @return int Number of characters printed
 */
int					ft_printf(char const *input, ...);
int					print_char(char c);
int					print_integer(int nb);
int					print_string(char *str);
int					print_unsigned(unsigned int nb);
int					print_hex_lower(unsigned int n);
int					print_hex_upper(unsigned int n);
int					print_pointer(void *ptr);

/**
 * @brief Reads a line from a file descriptor and
 * 		returns it as a string.
 *
 * @param fd The file descriptor to read from.
 * @return char* A pointer to the string containing the line read
 * 		from the file descriptor.
 */
char				*get_next_line(int fd);

/**
 * @brief Reallocates a block of memory.
 *
 * The ft_realloc function reallocates a block of memory that was previously
 * allocated with malloc or calloc. The size of the memory block is changed to
 * the size specified by the new_size parameter. The contents of the memory
 * block are preserved up to the lesser of the new and old sizes. If the new
 * size is larger, the additional memory is uninitialized.
 *
 * @param ptr A pointer to the previously allocated memory block.
 * @param new_size The new size of the memory block, in bytes.
 * @return A pointer to the reallocated memory block, or NULL if the operation
 * failed.
 */
void				*ft_realloc(void *ptr, size_t new_size);

/**
 * @brief Splits a string into tokens based on a delimiter.
 *
 * This function takes a string and a delimiter as input and splits 
 * the string into tokens.
 * It returns a pointer to the first token found in the string, 
 * or NULL if no token is found.
 *
 * @param str The string to be tokenized.
 * @param del The delimiter used to split the string.
 * @return A pointer to the first token found in the string, 
 * or NULL if no token is found.
 */
char				*ft_strtok(char *str, char *del);

/**
 * @brief Returns the number of elements in a 2D array.
 * 
 * This function takes a 2D array as input and returns the number of
 * elements in the array.
 * 
 * @param ptr The 2D array to be counted.
 * @return The number of elements in the array.
 */
int					ft_double_ptr_amount(char **ptr);

#endif