# Manual Tests for Signal Handling (CTRL+C / SIGINT and CTRL+\ / SIGQUIT)

This document outlines manual tests to verify the correct behavior of CTRL+C in a minishell.

IMPORTANT: VSCode's integrated terminal and Oh My Zsh sometimes have different stty (terminal) settings that control whether control characters are echoed. The ^C display is controlled by the terminal's echoctl flag. Verify this by

```bash
stty -a
```

Look for echoctl in the output. If you see -echoctl, it means control character echoing is disabled.

In VSCode terminal, enable echoctl:
```bash
stty echoctl
```

---

### Test 1: CTRL+C on an Empty Prompt

**Purpose:** To ensure that pressing CTRL+C on an empty line doesn't crash the shell and correctly displays a new prompt.

**Steps:**
1. Run your minishell.
2. At the empty prompt, press `CTRL+C`.

**Expected Outcome:**
- A `^C` might be displayed (this is optional but common).
- The current line is cleared.
- A new, empty prompt is displayed on a new line.
- The shell does NOT exit.
- Check exit code `echo $?`. It must be 130.

---

### Test 2: CTRL+C with Text in the Prompt

**Purpose:** To ensure that pressing CTRL+C clears any text the user has typed.

**Steps:**
1. Run your minishell.
2. Type some text at the prompt (e.g., `echo hello world`) but DO NOT press Enter.
3. Press `CTRL+C`.

**Expected Outcome:**
- A `^C` might be displayed.
- The line with `echo hello world` is cleared.
- A new, empty prompt is displayed on a new line.
- The shell does NOT exit.
- Check exit code `echo $?`. It must be 130.

---

### Test 3: CTRL+C during Heredoc Input

**Purpose:** To test if CTRL+C correctly cancels a here-document (`<<`) input mode.

**Steps:**
1. Type a command that uses a heredoc, for example: `cat << EOF` and press Enter.
2. The shell should now be waiting for heredoc input (showing a `> ` prompt).
3. Type some text, like `hello`.
4. Press `CTRL+C`.

**Expected Outcome:**
- The heredoc input is immediately cancelled.
- The shell returns to a new, empty main prompt.
- The original command (`cat << EOF`) is not executed.
- The shell does NOT exit.

---

### Test 4: CTRL+C during a Child Process (Long-running command)

**Purpose:** To verify that CTRL+C terminates the running child process but not the parent shell. This is a critical test.

**Steps:**
1. Run your minishell.
2. Execute a command that takes time to run, for example: `sleep 5`.
3. While `sleep` is running (within the 5-second window), press `CTRL+C`.

**Expected Outcome:**
- The `sleep 5` command is terminated immediately.
- The shell displays a new, empty prompt.
- The shell does NOT exit.
- The exit code should be set to 130 (which is 128 + 2, where 2 is the signal number for SIGINT). You can check this by running `echo $?` immediately after.

---

### Test 5: CTRL+C during an interactive Child Process

**Purpose:** To test signal handling with an interactive command that reads from standard input.

**Steps:**
1. Run your minishell.
2. Run the command `cat` (with no arguments). The terminal will wait for input.
3. Press `CTRL+C`.

**Expected Outcome:**
- The `cat` process is terminated.
- The shell returns to a new, empty prompt.
- The shell does NOT exit.
- The exit code should be 130 (`echo $?`).

---

### Test 6: CTRL+\ on a heredoc

**Steps:**
1. Open heredoc `<< LIM`
2. Press Enter.
3. Press `CTRL+\`.

**Expected Outcome:**
- It is ignored.

---
