# Cowsay Project 

## Overview

This project is a custom implementation of a **C-based Cowsay-style program** with multiple cow personalities and behaviors. It combines C programs and shell scripts to simulate different cow modes (school levels, smart cow, crazy cow, wild cow, etc.).

The goal of the project is to:

* Practice C programming (strings, I/O, structures, modular code)
* Use shell scripting to automate execution
* Experiment with different behavioral variations of a base program

---

## Project Structure

```
cowsay/
│
├── reading_cow.c
├── wild_cow.c
├── tamagoshi cow.c
├── newcow.c
│
├── cow_primaryschool.sh
├── cow_highschool.sh
├── cow_college.sh
├── cow_university.sh
├── smart_cow.sh
├── crazy_cow.sh
│
├── readingcowTxt
├── exemple-reaadingcow.mov
├── Commentaire sur chaque partie.pdf
```

### C Source Files

* `reading_cow.c` – Base cow that reads text and displays it.
* `wild_cow.c` – Variation with modified behavior/output style.
* `tamagoshi cow.c` – Interactive or evolving cow version.
* `newcow.c` – Alternative cow implementation.

### Shell Scripts

* `cow_primaryschool.sh`
* `cow_highschool.sh`
* `cow_college.sh`
* `cow_university.sh`
* `smart_cow.sh`
* `crazy_cow.sh`

These scripts likely:

* Compile the corresponding C file
* Execute it with specific arguments
* Customize the output style

### Additional Files

* `readingcowTxt` – Input text example
* `exemple-reaadingcow.mov` – Demonstration video
* `Commentaire sur chaque partie.pdf` – Code explanation

---

## Compilation

To compile a C file manually:

```bash
gcc reading_cow.c -o reading_cow
```

Example for another version:

```bash
gcc wild_cow.c -o wild_cow
```

---

## Execution

Run a compiled cow program:

```bash
./reading_cow "Hello World"
```

Or execute a shell script:

```bash
bash cow_university.sh
```

If scripts are executable:

```bash
chmod +x cow_university.sh
./cow_university.sh
```

---

## Features

* ASCII cow rendering
* Custom speech bubble
* Multiple personalities
* Script-based automation
* Modular C structure

Possible advanced features depending on implementation:

* File input reading
* Interactive mode
* Randomized responses
* Behavioral state simulation (Tamagoshi style)

---

## Requirements

* GCC compiler
* Unix/Linux or WSL environment
* Bash shell

Install GCC (Ubuntu):

```bash
sudo apt update
sudo apt install build-essential
```

---

## Educational Objectives

This project demonstrates:

* String manipulation in C
* Command-line arguments handling
* File reading in C
* Shell scripting basics
* Program modularization
* Multi-version program design

---

## Possible Improvements

* Add Makefile for easier compilation
* Add argument parsing with flags
* Improve ASCII formatting
* Add color support (ANSI escape codes)
* Add unit tests

---

## Author

Student project – C programming and scripting practice.

---

## License

Educational use only.
