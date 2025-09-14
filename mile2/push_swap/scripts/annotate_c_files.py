#!/usr/bin/env python3
import os
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

def find_c_files(base: Path):
    for p in base.rglob('*.c'):
        yield p

HEADER_END_RE = re.compile(r"\*/\s*$")
INCLUDE_RE = re.compile(r"^\s*#\s*include\s+[<\"]([^>\"]+)[>\"]")
HAS_TAG_RE = re.compile(r"/\*\s*(Resumen|Requiere)\s*:")

# Short descriptions by filename patterns (best effort)
DESCR_MAP = {
    'checker.c': 'Checker: aplica operaciones y valida pilas',
    'checker_utils.c': 'Utilidades del checker',
    'push_swap.c': 'Programa principal push_swap',
}

def short_desc_for(path: Path) -> str:
    name = path.name
    if name in DESCR_MAP:
        return DESCR_MAP[name]
    # libft naming heuristic
    if name.startswith('ft_') and name.endswith('.c'):
        func = name[:-2]
        return f"Implementación de {func}"
    # generic
    return f"Archivo {name} del proyecto"


def annotate_file(path: Path) -> bool:
    try:
        text = path.read_text(encoding='utf-8', errors='ignore')
    except Exception:
        return False

    if HAS_TAG_RE.search(text):
        return False  # already annotated

    lines = text.splitlines(True)

    # Find insertion point: after 42 header and includes block
    idx = 0
    # Skip 42 header if present
    while idx < len(lines) and not HEADER_END_RE.search(lines[idx]):
        idx += 1
    if idx < len(lines):
        idx += 1  # move past header end line
    # Skip blank lines
    while idx < len(lines) and lines[idx].strip() == '':
        idx += 1
    # Collect includes block
    last_inc = -1
    includes = []
    j = idx
    while j < len(lines):
        m = INCLUDE_RE.match(lines[j])
        if not m:
            break
        includes.append(m.group(1))
        last_inc = j
        j += 1
    insert_at = j if last_inc >= 0 else idx

    resumen = short_desc_for(path)
    reqs = ', '.join(includes) if includes else 'ninguna'

    comment = (
        f"/* Resumen: {resumen} */\n"
        f"/* Requiere: {reqs} */\n\n"
    )

    new_text = ''.join(lines[:insert_at]) + comment + ''.join(lines[insert_at:])

    if new_text != text:
        path.write_text(new_text, encoding='utf-8')
        return True
    return False


def main():
    base = ROOT
    changed = 0
    for cfile in find_c_files(base):
        if annotate_file(cfile):
            changed += 1
    print(f"Annotated {changed} files.")

if __name__ == '__main__':
    main()
