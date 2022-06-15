#inlcude "main.h"

/**
* read_input - function
* Return: 0 (Exit Success)
*/
char *read_input(void)
{
char *line = NULL;
size_t input_size = 0;
ssize_t read;

read = getline(&line, &input_size, stdin);
printf("%s", line);
if (read == EOF)
{
if (isatty(STDIN_FILENO))
write(STDIN_FILENO, "\n", 1);
free(line);
exit(EXIT_SUCCESS);
}

if (read == 1)
{
free(line);
if (isatty(STDIN_FILENO))
write(STDIN_FILENO, "$ ", 2);
return (NULL);
}
return (line);
}

/**
 * print_env - prints environment
 * @env: environment list
 */
void print_env(char **env)
{
int a = 0, l = 0;
char *string = NULL;

while (env[a] != NULL)
{
string = env[a];
l = _strlen(string);
write(STDOUT_FILENO, string, l);
write(STDOUT_FILENO, "\n", 1);
a++;
}

if (isatty(STDOUT_FILENO))
write(STDOUT_FILENO, "$ ", 2);
}

/**
 * pathandfree - creates path list
 * @arg: input argument to check
 * Return: string if successful, NULL otherwise
 */
char *pathandfree(char *arg)
{
list_p *pathy;
char *str;

pathy = pathlist();
str = pathchecker(&pathy, arg);
if (str == NULL)
{
free_list(pathy);
free(str);
return (NULL);
}
else
{
free_list(pathy);
return (str);
}
}

/**
* _halt - function
* @sig: signal to look for
* Description: function to catch SIGINT ^C
* Return: 0
*/
void _halt(int sig)
{
if (sig == SIGINT)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "\n$ ", 3);
}
}
/**
* freeptrarrayandexit - function
* @str: arg to free and exit
* @stat: status counter from waitpid command
* Return: 0
*/
void freeptrarrayandexit(char **str, int stat)
{
int s = 0;

if (str[1] != NULL)
{
s = atoi(str[1]);
if (s < 0 || s >= 125)
{
freeptrarray(str);
perror("Error: illegal number\n");
exit(EXIT_SUCCESS);
}
}
else
s = WEXITSTATUS(stat);
freeptrarray(str);
exit(s);
}
