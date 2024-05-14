<div align="center">
    <img src="https://github.com/15Galan/42_project-readmes/blob/master/banners/cursus/projects/minishell-light.png?raw=true#gh-light-mode-only" alt="Banner (claro)" />
    <img src="https://github.com/15Galan/42_project-readmes/blob/master/banners/cursus/projects/minishell-dark.png?raw=true#gh-dark-mode-only" alt="Banner (oscuro)" />
    <br>
    This project is about creating a simple shell. Yes, your own little bash. You will learn a lot about processes and file descriptors
    <br>
	<table>
	<tr><th>Albagar4 (Built-ins, Environment variables)</th>
		<td><a href='https://profile.intra.42.fr/users/albagar4' target="_blank">
        <img alt='42 (oscuro)' src='https://img.shields.io/badge/Málaga-black?style=flat&logo=42&logoColor=white'/></td>
	</tr>
	<tr><th>Alvega-g (Parser-lexer, Executor)</th>
		<td><a href='https://profile.intra.42.fr/users/alvega-g' target="_blank">
        <img alt='42 (oscuro)' src='https://img.shields.io/badge/Málaga-black?style=flat&logo=42&logoColor=white'/><br></td>
	</tr>
	</table>    
    <img src="https://img.shields.io/badge/score- 101%20%2F%20100-success?color=%2312bab9&style=flat" />
    </a>

</div>

---

# Mandatory part

<table>
  <tr>
    <th>Program name</th>
    <td><em>minishell</em></td>
  </tr>
  <tr>
    <th>Turn in files</th>
    <td><code>Makefile, *.h, *.c</code></td>
  </tr>
  <tr>
    <th>Makefile</th>
    <td><code>NAME, all, clean, fclean, re</code></td>
  </tr>
  <tr>
	<th>Arguments</th>
  </tr>
  <tr>
    <th>External functions</th>
    <td><code>readline, rl_clear_history, rl_on_new_line,
			rl_replace_line, rl_redisplay, add_history,
			printf, malloc, free, write, access, open, read,
			close, fork, wait, waitpid, wait3, wait4, signal,
			sigaction, sigemptyset, sigaddset, kill, exit,
			getcwd, chdir, stat, lstat, fstat, unlink, execve,
			dup, dup2, pipe, opendir, readdir, closedir,
			strerror, perror, isatty, ttyname, ttyslot, ioctl,
			getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
			tgetnum, tgetstr, tgoto, tputs</code></td>
  </tr>
  <tr>
	<th>Libft authorized</th>
	<td>Yes</td>
  </tr>
  <tr>
    <th>Description</th>
    <td>Write a shell</td>
  </tr>
</table>

Your shell should:
- Display a __prompt__ when waiting for a new command.
- Have a working __history__.
- Search and launch the right executable (based on the ``PATH`` variable or using a
relative or an absolute path).
- Avoid using more than __one global variable__ to indicate a received signal. Consider
the implications: this approach ensures that your signal handler will not access your
main data structures.

### Be careful. This global variable cannot provide any other information or data access than the number of a received signal. Therefore, using "norm" type structures in the global scope is forbidden.

- Not interpret unclosed quotes or special characters which are not required by the
subject such as \ (backslash) or ; (semicolon).
- Handle ’ (single quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence.
- Handle " (double quote) which should prevent the shell from interpreting the metacharacters in the quoted sequence except for $ (dollar sign).
- Implement __redirections__:
	- < should redirect input.
	- \> should redirect output.
	- << should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
	- \>> should redirect output in append mode.
- Implement __pipes__ (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.
- Handle __environment variables__ ($ followed by a sequence of characters) which
should expand to their values.
- Handle ``$?`` which should expand to the exit status of the most recently executed
foreground pipeline.
- Handle ``ctrl-C``, ``ctrl-D`` and ``ctrl-\`` which should behave like in ``bash``.
- In interactive mode:
	- ``ctrl-C`` displays a new prompt on a new line.
	- ``ctrl-D`` exits the shell.
	- ``ctrl-\`` does nothing.
- Your shell must implement the following __builtins__:
	- ``echo`` with option ``-n``
	- ``cd`` with only a relative or absolute path
	- ``pwd`` with no options
	- ``export`` with no options
	- ``unset`` with no options
	- ``env`` with no options or arguments
	- ``exit`` with no options

The ``readline()`` function can cause memory leaks. You don’t have to fix them. But that __doesn’t mean your own code, yes the code you wrote, can have memory leaks.__

### You should limit yourself to the subject description. Anything that is not asked is not required. If you have any doubt about a requirement, take [bash](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/) as a reference.

# Bonus part

Your program has to implement:
- ``&&`` and ``||`` with parenthesis for priorities.
- Wildcards * should work for the current working directory.
- Correct implementation of single and double quotes when expanding variables and nesting quotes.

# How to run

Clone this repository to your working directory by running the following commands:

```bash
git clone https://github.com/ColmiiK/minishell.git
cd minishell
make
./minishell
```

### The readline library is required to run this program.