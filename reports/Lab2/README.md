# LaTeX Project Setup

This project uses LaTeX with the **minted** package. That means you must have:

- **TeX Live** (or MacTeX)
- **python3**
- **pygments** (`pygmentize` binary)
- `latexmk`

The provided script `install_dependencies.sh` installs everything needed on a Debian/Ubuntu-based system.

---

## Installation

### 1. Make the installer executable
```bash
chmod +x install_dependencies.sh
./install_dependencies.sh
```

---

## Usage

### Compile the document once
```bash
make compile
```

### Watch mode with live PDF preview

Opens the PDF in Evince and recompiles automatically on file changes:
```bash
make watch
```

### Clean auxiliary files

Removes temporary LaTeX files (keeps the PDF):
```bash
make clean
```

### Clean everything

Removes all generated files including the PDF:
```bash
make cleanall
```
