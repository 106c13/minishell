# minishell

> A shell project built at [42](https://42.fr) by [azolotar](https://github.com/sjapi) and [haaghaja](https://github.com/106c13)

## 🧠 Project Overview

`minishell` is a minimalist UNIX shell created from scratch as part of the 42 school curriculum.

It replicates core features of common shells like bash/zsh, including command execution, environment handling, redirections, pipelines, and more.

---

## ⚙️ Architecture

Our processing pipeline: `input → validator → parser → expander → executor`

- **Input**  
  User input is read using `readline()` with history support.

- **Validator**  
  Checks for unmatched quotes, syntax errors, or invalid sequences.

- **Parser**  
  Turns the raw input into a structured format using `t_command` and `t_arg`.

- **Expander**  
  Processes:
  - Environment variables (`$VAR`)
  - Wildcards (`*`)
  - Quotes removal and expansion rules

- **Executor**  
  Executes built-ins directly or forks for external commands.  
  Handles redirections, heredocs, and pipes.

---

## 🧰 Built-in Commands

These are implemented internally (no `fork`):

- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `exit`

---

## 🧱 Operators & Redirections

### Logical Operators

- `|` — pipe
- `&&` — AND (execute next only if previous succeeded)
- `||` — OR (execute next only if previous failed)

### Redirections

- `>` — redirect output (overwrite)
- `>>` — redirect output (append)
- `<` — redirect input
- `<<` — **heredoc**

---

## 🚀 How to Run

```bash
make
./minishell
