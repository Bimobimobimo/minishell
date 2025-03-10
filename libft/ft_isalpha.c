/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amonfret <amonfret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 00:52:02 by amonfret          #+#    #+#             */
/*   Updated: 2024/10/23 15:35:39 by amonfret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

/* cc main.c -L. -lft -lbsd
#include <stdio.h>
#include <bsd/string.h>
#include <string.h>
#include "libft.h"

void test_char(void)
{
	char test1 = 'A';
	char test2 = '1';
	char test3 = '$';
	printf("\nTesting ft_isdigit:\n");
	printf("ft_isdigit('%c') = %d\n", test1, ft_isdigit(test1));
	printf("ft_isdigit('%c') = %d\n", test2, ft_isdigit(test2));
	printf("ft_isdigit('%c') = %d\n", test3, ft_isdigit(test3));
	printf("\nTesting ft_isalpha:\n");
	printf("ft_isalpha('%c') = %d\n", test1, ft_isalpha(test1));
	printf("ft_isalpha('%c') = %d\n", test2, ft_isalpha(test2));
	printf("ft_isalpha('%c') = %d\n", test3, ft_isalpha(test3));
	printf("\nTesting ft_isalnum:\n");
	printf("ft_isalnum('%c') = %d\n", test1, ft_isalnum(test1));
	printf("ft_isalnum('%c') = %d\n", test2, ft_isalnum(test2));
	printf("ft_isalnum('%c') = %d\n", test3, ft_isalnum(test3));
	printf("\nTesting ft_isascii:\n");
	printf("ft_isascii('%c') = %d\n", test1, ft_isascii(test1));
	printf("ft_isascii('%c') = %d\n", test2, ft_isascii(test2));
	printf("ft_isascii(128) = %d\n", ft_isascii(128));
	printf("\nTesting ft_isprint:\n");
	printf("ft_isprint('%c') = %d\n", test1, ft_isprint(test1));
	printf("ft_isprint('%c') = %d\n", test2, ft_isprint(test2));
	printf("ft_isprint('\\n') = %d\n", ft_isprint('\n'));
}

void test_ft_strlen(void)
{
	char *string1 = "Test";
	char *string2 = "";
	printf("\nTesting ft_strlen:\n");
	printf("ft_strlen('%s') = %ld\n", string1, ft_strlen(string1));
	printf("ft_strlen('%s') = %ld\n", string2, ft_strlen(string2));
}

void test_ft_memset(void)
{
	char buffer[50];
	printf("\nTesting ft_memset:\n");
	printf("ft_memset(buffer, '%c', 10) = ", 'A');
	ft_memset(buffer, 'A', 10);
	buffer[10] = '\0';
	printf("%s\n", buffer);
	printf("ft_memset(buffer, '%c', 15) = ", '1');
	ft_memset(buffer, '1', 15);
	buffer[15] = '\0';
	printf("%s\n", buffer);
}
void test_ft_bzero(void)
{
	char buffer[50];
	int i;

	ft_memset(buffer, '1', 15);
	buffer[15] = '\0';
	printf("\nTesting ft_bzero, first 10 bytes: \n");
	printf("Original buffer:\n%s\n", buffer);
	ft_bzero(buffer, 10);
	printf("After ft_bzero(buffer, 10):\n");
	i = 0;
	while (i < 15)
	{
		if (buffer[i] == '\0')
			printf("\\0");
		else
			printf("%c", buffer[i]);
		i++;
	}
	printf("\n");
}

void test_ft_memcpy(void)
{
	printf("\nTesting ft_memcpy:\n");
	char src[] = "Hello, World!";
	char dest[50]; 
	printf("src = %s\n", src);
	printf("ft_memcpy(dest, src, 13)\n");
	dest[13] = '\0';
	ft_memcpy(dest, src, 13);
	printf("dest = %s\n", dest);
}

void test_ft_tolower(void)
{
	printf("\nTesting ft_toupper\n");
	printf("%c->%c | %c->%c\n", 'a', ft_toupper('a'), 'A', ft_toupper('A'));
}

void test_ft_toupper(void)
{
	printf("\nTesting ft_tolower\n");
	printf("%c->%c | %c->%c\n", 'A', ft_tolower('A'), 'a', ft_tolower('a'));
}

void test_ft_memmove(void)
{
	printf("\nTesting ft_memmove\n");
	char str1[] = "Hello, World!";
    printf("Before memmove: %s\n", str1);
    ft_memmove(str1 + 7, str1, 5);
	printf("ft_memmove(str1 + 7, str1, 5)\n");
    printf("After memmove (no overlap): %s\n", str1);
	char str2[] = "123456";
    printf("Before memmove: %s\n", str2);
    ft_memmove(str2 + 2, str2, 4);
	printf("ft_memmove(str2 + 2, str2, 4)\n");
    printf("After memmove (Overlap src before dest): %s\n", str2);
	char str3[] = "abcdef";
    printf("Before memmove: %s\n", str3);
    ft_memmove(str3, str3 + 3, 3);
	printf("ft_memmove(str3, str3 + 3, 3)\n");
    printf("After memmove (src after dest): %s\n", str3);
}
void test_ft_strlcpy(void)
{
    char dst1[20];
    char dst2[20];
    const char *src = "Some string that is longer than 20 chars";

    size_t len1 = strlcpy(dst1, src, 0);
    size_t len2 = ft_strlcpy(dst2, src, 0);
	printf("\nTesting ft_strlcpy\n");
    printf("Test size 0:\n");
    printf("strlcpy: len=%zu\n", len1);
    printf("ft_strlcpy: len=%zu\n", len2); 

    len1 = strlcpy(dst1, src, 5);
    len2 = ft_strlcpy(dst2, src, 5);
    printf("Test size 5:\n");
    printf("strlcpy: dst='%s', len=%zu\n", dst1, len1);
    printf("ft_strlcpy: dst='%s', len=%zu\n", dst2, len2); 

    len1 = strlcpy(dst1, src, 20);
    len2 = ft_strlcpy(dst2, src, 20);
    printf("Test size 20:\n");
    printf("strlcpy: dst='%s', len=%zu\n", dst1, len1);
    printf("ft_strlcpy: dst='%s', len=%zu\n", dst2, len2); 
}

void test_ft_strlcat(void)
{
	char dest1[20] = "Hello, ";
	char dest2[20] = "Hello, ";
	const char *src = "World!";
	size_t result1 = ft_strlcat(dest1, src, sizeof(dest1));
	size_t result2 = strlcat(dest2, src, sizeof(dest2));
	printf("\nTesting ft_strlcat\n");
	printf("My ft_strlcat: dest = '%s', len = %zu\n", dest1, result1);
	printf("Original strlcat: dest = '%s', len = %zu\n", dest2, result2);
}

void test_ft_strchr(void)
{
	printf("\nTesting ft_strchr\n");
	char tofind = 'a';
	char *str = "123abac";
	printf("Finding first '%c' in '%s'\n", tofind, str);
	char *chr = ft_strchr(str, tofind);
	int i = 0;
	if(chr)
	{
		while (chr[i])
		{
			printf("%c", chr[i]);
			i++;
		}
		printf("\n");
	}
	else
		printf("NULL\n");
}

void test_ft_strrchr(void)
{
	printf("\nTesting ft_strrchr\n");
	char tofind = 'a';
	char *str = "a1bcda345a89";
	printf("Finding last '%c' in '%s'\n", tofind, str);
	char *chr = ft_strrchr(str, tofind);
	int i = 0;
	if(chr)
	{
		while (chr[i])
		{
			printf("%c", chr[i]);
			i++;
		}
		printf("\n");
	}
	else
	{
		printf("NULL\n");
	}
}

void test_ft_strncmp(void)
{
	printf("\nTesting ft_strncmp\n");
	char *str1 = "abcd";
	char *str2 = "abcD";
	printf("String 1: %s, string 2: %s\n", str1, str2);
	int res = ft_strncmp(str1, str2, 4);
	printf("%d\n", res);
}

void  test_ft_memchr(void)
{
	char buffer[50];
	unsigned char *ptr;
	ft_memset(buffer, 'a', 15);
	ft_memset(buffer + 7, 'b', 1);
	buffer[15] = '\0';
	printf("\nTesting ft_memchr\n");
	printf("Before ft_memchr\n");
	int i = 0;
	while(buffer[i])
	{
		printf("%c", buffer[i]);
		i++;
	}
	ptr = ft_memchr(buffer, 'b', 15);
	printf("\nAfter ft_memchr(buffer, 'b', 15)\n");
	i = 0;
	while(ptr[i])
	{
		printf("%c", ptr[i]);
		i++;
	}
	printf("\n");
}

void	test_ft_memcmp(void)
{
	printf("\nTesting ft_memcmp\n");
	char buffer1[50];
	char buffer2[50];
	ft_memset(buffer1, 'A', 15);
	buffer1[15] = '\0';
	ft_memset(buffer2, 'A', 15);
	buffer2[15] = '\0';
	buffer2[12] = 'a';
	printf("%s\n", buffer1);
	printf("%s\n", buffer2);
	int res = ft_memcmp(buffer1, buffer2, 15);
	printf("%d\n", res);
}

void test_ft_strnstr(void)
{
	printf("\nTesting ft_strnstr\n");
	const char	*largestring = "Foo Bar Baz";
	const char	*smallstring = "Bar";
	char		*ptr;

	printf("Large: '%s', small: '%s', len: 4\n", largestring, smallstring);
	ptr = ft_strnstr(largestring, smallstring, 4);
	if (!ptr)
		printf("NULL\n");
	else
		printf("%s\n", ptr);
	printf("Large: '%s' small: '%s', len: 9\n", largestring, smallstring);
	ptr = ft_strnstr(largestring, smallstring, 9);
	if (!ptr)
		printf("NULL\n");
	else
		printf("%s\n", ptr);
}

void test_ft_atoi(void)
{
	printf("\nTesting ft_atoi\n");
	char *test = "   \n\t-1234abc";
	printf("%d\n", atoi(test));
	printf("%d\n", ft_atoi(test));
}
static void ft_calloc_callback(size_t nmemb, size_t size)
{
	void *ptr;
	printf("\nTesting ft_calloc with nmemb = %zu, size = %zu\n", nmemb, size);
	ptr = ft_calloc(nmemb, size);
	if (nmemb == 0 || size == 0)
	{
		if (ptr == NULL)
		{
			printf("ft_calloc returned NULL as expected for zero allocation\n");
		}
		else
		{
			printf("ft_calloc returned non-NULL pointer for zero alloc\n");
		}
		free(ptr);
		return;
	}
	if (!ptr)
	{
		printf("ft_calloc returned NULL\n");
		return;
	}
	size_t i = 0;
	int is_zero_flag = 1;
	while(i < nmemb * size)
	{
		if(((unsigned char *)ptr)[i] != 0)
		{
			is_zero_flag = 0;
			break;
		}
		i++;
	}
	if(is_zero_flag)
		printf("Memory allocated and initialized to zero\n");
	else
		printf("Error: memory not initialized to zero\n");
	free(ptr);
}
void test_ft_calloc(void)
{
	ft_calloc_callback(5, sizeof(int));
	ft_calloc_callback(0, sizeof(int));
	ft_calloc_callback(5, 0);
	ft_calloc_callback(1000, sizeof(char));
	ft_calloc_callback(1 << 30, 1 << 30);
}

void	test_ft_strdup(void)
{
	printf("\nTesting ft_strdup\n");
	const char *test = "this is a test";
	char *dup;
	dup = ft_strdup(test);
	if(dup != NULL)
		printf("Original string: '%s', copy: '%s'\n", test, dup);
	else
		printf("NULL\n");
	free(dup);
}

void	test_ft_substr(void)
{
	size_t start = 3;
	size_t len = 5;
	const char *str = "Hello, World!";
	printf("\nTesting ft_substr\n");
	printf("Original string: %s\n", str);
	char *sub = ft_substr(str, start, len);
	if (sub != NULL)
		printf("Substring start %zu len %zu\n%s\n",start , len, sub);
	else
		printf("NULL");
	free(sub);
}

void test_ft_strjoin(void)
{
	printf("\nTesting ft_strjoin\n");
	const char *s1 = "Hello ";
	const char *s2 = "World!";
	printf("s1: '%s', s2: '%s'\n", s1, s2);
	char *new = ft_strjoin(s1, s2);
	if(new != NULL)
		printf("%s\n", new);
	else
		printf("NULL\n");
	size_t i = 0;
	while (new[i])
	{
		i++;
	}
	free(new);
}

void test_ft_strtrim(void)
{
	printf("\nTesting ft_strtrim\n");
	char const *s1 = "!!!Hello,!!Wor&ld!&&&";
	char const *set = "!&";
	printf("Initial string: '%s', set: '%s'\n", s1, set);
	char *new = ft_strtrim(s1, set);
	if(new != NULL)
		printf("New string: '%s'\n", new);
	free(new);
}

void test_ft_split(void)
{
	printf("\nTesting ft_split\n");
	char *test = " this is a test   ";
	char sep = ' ';
	char **split;
	printf("string = '%s'\n", test);
	printf("Separator = ' '\n");
	split = ft_split(test, sep);
	int i = 0;
	if(split != NULL)
	{
		printf("split:\n");
		while(split[i])
		{
			printf("'%s'\n", split[i]);
			free(split[i]);
			i++;
		}
	}
	free(split);
}

void	test_ft_itoa(void)
{
	printf("\nTesting ft_itoa.c\n");
	int test = -2147483648;
	char *res = ft_itoa(test);
	printf("%s\n", res);
	free(res);
}

static char toupperv2(unsigned int index, char c)
{
	if(index % 2 == 0)
		return ('0');
	return (c);
}

void test_ft_strmapi(void)
{
	printf("\nTesting ft_strmapi\n");
	const char *s = "Hello, World!";
	char *test;
	printf("Original string is '%s'\n", s);
	printf("Replacing every even index by '0'\n");
	test = ft_strmapi(s, toupperv2);
	if(test != NULL)
		printf("%s\n", test);
	free(test);
}

static void upper_to_zero(unsigned int index, char *s)
{
	if(*s >= 'A' && *s <= 'Z')
	{
		if (index % 2 == 0)
			*s = '1';
		else
			*s = '0';
	}
}

void test_ft_striteri(void)
{
	printf("\nTesting ft_striteri\n");
	char s[14] = "This Is A tEst";
	printf("Original string: '%s'\n", s);
	printf("Replacing Even index uppercase by 0, odd by 1\n");
	ft_striteri(s, upper_to_zero);
	printf("%s\n", s);
}

void test_ft_putchar_fd(void)
{
	printf("\nTesting ft_putchar_fd\n");
	printf("Printing 'A' on fd 1 (stdout)\n");
	ft_putchar_fd('A', 1);
	printf("\n");
	printf("Printing 'B' on fd 2 (stderr)\n");
	ft_putchar_fd('B', 2);
	printf("\n");
}

void	test_ft_putstr_fd(void)
{
	char string[14] = "Hello, World!";
	printf("\nTesting ft_putstr_fd\n");
	printf("Printing %s on fd 1\n", string);
	ft_putstr_fd(string, 1);
	printf("\n");
	printf("Printing %s on fd 2\n", string);
	ft_putstr_fd(string, 2);
	printf("\n");
}

void	test_ft_putendl_fd(void)
{
	char *string = "Hello, World!";
	printf("\nTesting ft_putendl_fd\n");
	printf("Printing %s followed by \\n on fd 1\n", string);
	ft_putstr_fd(string, 1);
	printf("\n");
	printf("Printing %s followed by \\n on fd 2\n", string);
	ft_putstr_fd(string, 2);
	printf("\n");
}

void test_ft_putnbr_fd(void)
{
	int a = -2147483648;
	int b = 2147483647;
	int c = 0;

	printf("\nTesting ft_putnbr_fd\n");
	printf("printing %d on fd 1\n", a);
	ft_putnbr_fd(a, 1);
	printf("\n");
	printf("printing %d on fd 2\n", b);
	ft_putnbr_fd(b, 2);
	printf("\n");
	printf("printing %d on fd 1\n", c);
	ft_putnbr_fd(c, 1);
	printf("\n");
}

void	test_ft_lstnew(void)
{
	printf("\nTesting ft_lstnew\n");
	t_list *test;
	int a = 1;
	printf("a = %d\n", a);
	printf("Calling ft_lstnew(&a)\n");
	test = ft_lstnew(&a);
	printf("test->content = %d\n", *(int *)test->content);
	if (test->next == NULL)
		printf("test->next = NULL\n");
	free(test);
	t_list *test2;
	char b = 'Z';
	printf("b = %c\n", b);
	printf("Calling ft_lstnew(&a)\n");
	test2 = ft_lstnew(&b);
	printf("test2->content = %c\n", *(char *)test2->content);
	if (test2->next == NULL)
		printf("test2->next = NULL\n");
	free(test2);
}

void	test_ft_lstadd_front(void)
{
	printf("\nTesting ft_lstadd_front\n");
	t_list *head = NULL;
	t_list *elem1 = ft_lstnew("elem1");
	t_list *elem2 = ft_lstnew("elem2");
	ft_lstadd_front(&head, elem1);
	printf("First element: %s\n", (char *)head->content);
	ft_lstadd_front(&head, elem2);
	printf("New first element: %s\n", (char *)head->content);
	free(elem1);
	free(elem2);
}

void	test_ft_lstsize(void)
{
	printf("\nTesting ft_lstsize\n");
	int depth = 0;
	t_list *elem1 = ft_lstnew("Firt elem");
	t_list *elem2 = ft_lstnew("Second elem");
	t_list *elem3 = ft_lstnew("Third elem");
	printf("elem1->content = %s\n", (char *)elem1->content);
	printf("elem2->content = %s\n", (char *)elem2->content);
	printf("elem3->content = %s\n", (char *)elem3->content);
	elem1->next = elem2;
	elem2->next = elem3;
	depth = ft_lstsize(elem1);
	printf("Calling ft_lstsize\n");
	printf("Size = %d\n", depth);
	free(elem1);
	free(elem2);
	free(elem3);
}

void	test_ft_lstlast(void)
{
	printf("\nTesting ft_lstlast\n");
	t_list *last = NULL;
	t_list *elem1 = ft_lstnew("Firt elem");
	t_list *elem2 = ft_lstnew("Second elem");
	t_list *elem3 = ft_lstnew("Third elem");
	printf("elem1->content = %s\n", (char *)elem1->content);
	printf("elem2->content = %s\n", (char *)elem2->content);
	printf("elem3->content = %s\n", (char *)elem3->content);
	elem1->next = elem2;
	elem2->next = elem3;
	printf("Calling ft_last\n");
	last = ft_lstlast(elem1);
	if (last)
		printf("last->content: %s\n", (char *)last->content);
	free(elem1);
	free(elem2);
	free(elem3);
}

void	test_ft_lstadd_back(void)
{
	printf("\nTesting ft_lstadd_back\n");
	t_list *head = NULL;
	t_list *new = ft_lstnew("New");
	t_list *elem1 = ft_lstnew("Firt elem");
	t_list *elem2 = ft_lstnew("Second elem");
	t_list *elem3 = ft_lstnew("Third elem");
	head = elem1;
	printf("elem1->content = %s\n", (char *)elem1->content);
	printf("elem2->content = %s\n", (char *)elem2->content);
	printf("elem3->content = %s\n", (char *)elem3->content);
	elem1->next = elem2;
	elem2->next = elem3;
	printf("Before ft_lstadd_back\n");
	printf("elem3->content: %s\n", (char *)elem3->content);
	if(elem3->next == NULL)
		printf("elem3->next = NULL\n");
	printf("After ft_lstadd_back\n");
	ft_lstadd_back(&head, new);
	t_list	*last = ft_lstlast(head);
	if(elem3->next)
    {
        printf("elem3->next is not NULL\n");
		printf("last->content: %s\n", (char *)last->content);
    }
	free(elem1);
	free(elem2);
	free(elem3);
	free(last);
}

static void del(void *content)
{
	free(content);
}

void test_ft_lstclear(void)
{
	printf("\nTesting ft_lstclear\n");
	t_list *list = ft_lstnew(malloc(20));
	ft_strlcpy((char *)list->content, "First", 20);
	list->next = ft_lstnew(malloc(20));
	ft_strlcpy((char *)list->next->content, "Second", 20);
	list->next->next = ft_lstnew(malloc(20));
	ft_strlcpy((char *)list->next->next->content, "Third", 20);
	t_list *current = list;
	printf("Before clear:\n");
	while (current)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
	printf("Calling ft_lstclear\n");
	ft_lstclear(&list, del);
	if (list == NULL)
	{
		printf("List cleared.\n");
	}
	else
	{
		printf("List is still present.\n");
	}
}

static void	toupper_str(void *content)
{
	char	*str = (char *)content;
	int		i;

	i = 0;
	while(str[i])
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
}

static void	f(void *content)
{
	toupper_str(content);
}

void test_ft_lstiter(void)
{	
	printf("\nTesting ft_lstiter\n");
	t_list	*ptr;
	t_list	*elem1 = ft_lstnew(malloc(20));
	ft_strlcpy((char *)elem1->content, "One", ft_strlen("One") + 1);
	t_list	*elem2 = ft_lstnew(malloc(20));
	ft_strlcpy((char *)elem2->content, "Two", ft_strlen("Two") + 1);
	t_list	*elem3 = ft_lstnew(malloc(20));
	ft_strlcpy((char *)elem3->content, "Three", ft_strlen("Three") + 1);
	elem1->next = elem2;
	elem2->next = elem3;
	printf("Before ft_lstiter\n");
	ptr = elem1;
	while (ptr)
	{
		printf("%s\n", (char *)ptr->content);
		ptr = ptr->next;
	}
	printf("After ft_lstiter\n");
	ft_lstiter(elem1, f);
	ptr = elem1;
	while(ptr)
	{
		printf("%s\n", (char *)ptr->content);
		ptr = ptr->next;
	}
	ft_lstclear(&elem1, del);
}

static void *double_content(void *content)
{
	int *new_content;

	new_content = malloc(sizeof(int));
	if (new_content)
		*new_content = *(int *)content * 2;
	return (new_content);
}

void test_ft_lstmap(void)
{
    printf("\nTesting ft_lstmap\n");
	t_list *list = ft_lstnew(malloc(sizeof(int)));
	*(int *)(list->content) = 1;
	ft_lstadd_back(&list, ft_lstnew(malloc(sizeof(int))));
	*(int *)(list->next->content) = 2;
	ft_lstadd_back(&list, ft_lstnew(malloc(sizeof(int))));
	*(int *)(list->next->next->content) = 3;

	t_list *new_list = ft_lstmap(list, double_content, del);

	printf("Original list:\n");
	t_list *ptr = list;
	while (ptr) {
		printf("%d -> ", *(int *)(ptr->content));
		ptr = ptr->next;
	}
	printf("NULL\n");
	printf("New list after ft_lstmap:\n");
	ptr = new_list;
	while (ptr) {
		printf("%d -> ", *(int *)(ptr->content));
		ptr = ptr->next;
	}
	printf("NULL\n");

	ft_lstclear(&list, del);
	ft_lstclear(&new_list, del);
}

int main(void)
{
	test_char();
	test_ft_strlen();
	test_ft_memset();
	test_ft_bzero();
	test_ft_memcpy();
	test_ft_memmove();
	test_ft_strlcpy();
	test_ft_strlcat();
	test_ft_tolower();
	test_ft_toupper();
	test_ft_strchr();
	test_ft_strrchr();
	test_ft_strncmp();
	test_ft_memchr();
	test_ft_memcmp();
	test_ft_strnstr();
	test_ft_atoi();
	test_ft_calloc();
	test_ft_strdup();
	test_ft_substr();
	test_ft_strjoin();
	test_ft_strtrim();
	test_ft_split();
	test_ft_itoa();
	test_ft_strmapi();
	test_ft_striteri();
	test_ft_putchar_fd();
	test_ft_putstr_fd();
	test_ft_putendl_fd();
	test_ft_putnbr_fd();
	test_ft_lstnew();
	test_ft_lstadd_front();
	test_ft_lstsize();
	test_ft_lstlast();
	test_ft_lstadd_back();
	test_ft_lstclear();
	test_ft_lstiter();
	test_ft_lstmap();
	return (0);
}
*/