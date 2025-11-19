#!/usr/bin/env bash
set -e

echo "[*] Aggiornamento lista pacchetti..."
sudo apt update

echo "[*] Installazione dipendenze TeX e Python..."
sudo apt install -y \
    texlive \
    texlive-latex-base \
    texlive-latex-extra \
    texlive-bibtex-extra \
    texlive-science \
    texlive-fonts-recommended \
    texlive-lang-european \
    python3-pygments

echo "[✓] Done. Controllo pygmentize..."
pygmentize -V
