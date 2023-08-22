# Minishell Project Readme

Welcome to the Minishell project! This is a simple shell implementation that provides basic command execution and shell functionalities. It allows users to interact with the operating system by entering commands just like they would in a typical terminal.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Building](#building)
  - [Running](#running)
- [Usage](#usage)
- [Supported Commands](#supported-commands)
- [Contributing](#contributing)
- [License](#license)

## Features

- Command execution and basic shell functionalities.
- Support for simple command chaining using `;`.
- Input and output redirection using `<` and `>`.
- Pipelining of commands using `|`.
- Environment variable handling.
- Signal handling for interrupt signals (e.g., Ctrl+C).

## Getting Started

### Prerequisites

- A Unix-like operating system (Linux/macOS).
- GCC (GNU Compiler Collection) or a compatible C compiler.

### Building

1. Clone the repository:

   ```bash
   git clone https://github.com/your-username/minishell.git

2. Navigate to the project directory
   ```bash
   cd minishell

3. Compile the source code:
   ```bash
   make

### Running

1. Execute the compiled binary:
   ```bash
   ./minishell
2. You should now see the minishell prompt. You can start entering commands.

### Usage

- To chain commands, separate them with ;. For example: ls -l ; echo Hello.
- To redirect input or output, use < and >. For example: cat < input.txt > output.txt.
- To pipe commands, use |. For example: ls -l | grep ".txt".

Have fun!
