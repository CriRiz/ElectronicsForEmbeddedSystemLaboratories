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