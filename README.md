# 🌀 Flux — A Minimal Shell in C

Flux is a minimal, dependency-light shell written in C for Unix-like operating systems (Linux, BSD, and others).  
It is designed to be **small**, **educational**, and **portable**.

---

## ✨ Features
- Flexible and customizable shell prompt (`~/.flux.conf`)
- Persistent command history (`~/.flux_history`)
- Lightweight — depends only on standard C and POSIX system calls
- Simple command execution via `execvp`
- Perfect for learning how shells work internally

---

## 🧩 Build & Run

```bash
git clone https://github.com/yourname/flux.git
cd flux/src
make
./flux
```

Or compile manually:
```bash
gcc -o flux flux.c internal/string_utils.c internal/shell_prompt.c
```

---

## ⚙️ Configuration
Flux reads your prompt style from:
```
~/.flux.conf
```

Example:
```
%U@%H:$ -> usernmae@hostname:$  
```

Command history is automatically saved to:
```
~/.flux_history
```

---

## 🧠 Why Flux?
Flux is intentionally minimal — not a full-featured shell,  
but a tool to **learn** how shells work under the hood: command parsing, forking, exec calls, and I/O redirection.

---

## 🗺️ Roadmap / TODO
- [ ] Add built-in commands (`cd`, `pwd`, `clear`)
- [ ] Add command auto-completion
- [ ] Add colored prompt support
- [ ] Improve history navigation (arrow keys)
- [ ] Add basic I/O redirection

---

## 📜 License
Flux is licensed under the GNU General Public License v3.0 (GPL-3.0).  
See the `LICENSE` file for details.

