#!/bin/bash

# Define suppression rules
readline_supp=$(cat <<'END_SUPP'
{
   <readline>
   Memcheck:Leak
   ...
   fun:readline
   ...
}
END_SUPP
)

# Run valgrind with suppression rules
valgrind --suppressions=<(echo "$readline_supp") \
          --leak-check=full \
          --show-leak-kinds=all \
          --track-fds=yes \
          --trace-children=yes \
          -s -q ./minishell 2> >(grep -v "used_suppression" | \
                                   grep -v "FILE DESCRIPTORS" | \
                                   grep -v "Open file descriptor 63" | \
                                   grep -v "inherited from parent" | \
                                   grep -v "ERROR SUMMARY: 0 errors from 0 contexts" | \
                                   grep -v "^==[0-9]*==\s*$" | \
                                   grep -v "^--[0-9]*--\s*$")
