# 🐚 Minishell - Guía de Implementación & Evaluación

Este documento sigue el flujo de la hoja de corrección de 42.
**Leyenda:** `[ ]` Pendiente | `[x]` Hecho | `[~]` En testing

---

## 🏗️ Fase 1: Compilación y Estructura (Mandatory)
*Requisitos previos para que te corrijan.*

- [ ] **Makefile**
    - [ ] `make` compila sin relink.
    - [ ] `make all`, `make clean`, `make fclean`, `make re` funcionan.
    - [ ] Flags obligatorias: `-Wall -Wextra -Werror`.
- [ ] **Variables Globales**
    - [ ] Revisar que SOLO se usa 1 variable global (generalmente para recibir señales).
    - [ ] Justificar su uso (señales) si preguntan.
- [ ] **Memoria (Leaks)**
    - [ ] `malloc` protegido (si falla, no crashea).
    - [ ] Cero leaks al salir (usar `valgrind --leak-check=full`).
    - [ ] FDs cerrados correctamente (revisar con `lsof`).

---

## 🧠 Fase 2: Parser & Comillas (Input)
*Antes de ejecutar, hay que entender qué escribió el usuario.*

- [ ] **Comando Simple & Argumentos**
    - [ ] Ejecutar comando sin args: `ls`.
    - [ ] Ejecutar comando con args: `ls -la`.
    - [ ] Múltiples espacios entre args: `ls        -la`.
- [ ] **Comillas Simples (' ')**
    - [ ] `echo '$USER'` -> imprime `$USER` (no expande).
    - [ ] `echo 'hola mundo'` -> imprime un solo argumento.
- [ ] **Comillas Dobles (" ")**
    - [ ] `echo "$USER"` -> imprime tu usuario (expande).
    - [ ] `echo "$USER '$USER'"` -> expande el primero, literal el segundo (según bash).
- [ ] **Mezcla de Comillas**
    - [ ] `echo "'$USER'"` -> imprime `'pepe'`.
    - [ ] `echo '"$USER"'` -> imprime `"$USER"`.

---

## 🛠️ Fase 3: Builtins (Comandos Internos)
*Deben funcionar exactamente igual que en bash.*

- [ ] **echo**
    - [ ] `echo hola` (con salto de línea).
    - [ ] `echo -n hola` (sin salto de línea).
    - [ ] `echo -n -n -n hola` (válido).
- [ ] **cd**
    - [ ] `cd` (va a HOME).
    - [ ] `cd RutaRelativa` y `cd /Ruta/Absoluta`.
    - [ ] Actualiza `$PWD` y `$OLDPWD` en el env.
- [ ] **pwd**
    - [ ] Imprime la ruta actual.
- [ ] **export**
    - [ ] `export` (sin args): lista variables ordenadas alfabéticamente.
    - [ ] `export VAR=valor`: añade la variable.
    - [ ] `export VAR`: añade la variable sin valor (si no existe).
- [ ] **unset**
    - [ ] `unset VAR`: borra la variable.
    - [ ] `unset` de una variable que no existe no hace nada (no error).
- [ ] **env**
    - [ ] Imprime variables de entorno con valor.
- [ ] **exit**
    - [ ] Sale del shell con el status correcto.
    - [ ] `exit 123` (sale con 123).
    - [ ] `exit abc` (error numérico).

---

## 🚀 Fase 4: Ejecución (Binarios)
*El corazón del shell.*

- [ ] **Path Finding ($PATH)**
    - [ ] `ls` (busca en /bin, /usr/bin, etc.).
    - [ ] Si borras el PATH (`unset PATH`), `ls` no debe funcionar, pero `/bin/ls` sí.
- [ ] **Rutas relativas/absolutas**
    - [ ] `./minishell` (ejecuta el binario local).
    - [ ] `/bin/echo` (ejecuta desde ruta absoluta).
- [ ] **Valores de Retorno ($?)**
    - [ ] `ls` -> `echo $?` imprime 0.
    - [ ] `comando_falso` -> `echo $?` imprime 127.
    - [ ] `cat` (y Ctrl+C) -> `echo $?` imprime 130.

---

## 🚦 Fase 5: Redirecciones (Files)
*Manejo de entrada y salida.*

- [ ] **Redirección de Entrada (<)**
    - [ ] `grep a < archivo.txt`.
    - [ ] Error si el archivo no existe.
- [ ] **Redirección de Salida (>)**
    - [ ] `ls > out.txt` (crea o trunca).
- [ ] **Append (>>)**
    - [ ] `ls >> out.txt` (añade al final).
- [ ] **Heredoc (<<)**
    - [ ] `<< EOF` lee input hasta que escribas `EOF`.
    - [ ] No debe actualizar el historial.
    - [ ] Si hay comillas en el delimitador `<< "EOF"`, no expande variables dentro.

---

## 🔗 Fase 6: Pipes (|)
*El boss final del proyecto.*

- [ ] **Pipes Simples**
    - [ ] `ls | wc`.
- [ ] **Pipes Múltiples**
    - [ ] `ls | cat | grep c | wc`.
- [ ] **Mezcla con Redirecciones**
    - [ ] `ls > out | wc` (ojo, esto suele ser tricky).
    - [ ] `< in cat | wc > out`.

---

## ⚡ Fase 7: Señales (Signals)
*Ctrl+C, Ctrl+D, Ctrl+\*

- [ ] **En Prompt Vacío**
    - [ ] `Ctrl+C`: Nuevo prompt, código salida 1.
    - [ ] `Ctrl+D`: Escribe "exit" y sale.
    - [ ] `Ctrl+\`: Ignorar.
- [ ] **Durante Ejecución (Blocking)**
    - [ ] Ejecuta `cat` (se queda esperando).
    - [ ] `Ctrl+C`: Mata a `cat`, vuelve al prompt.
    - [ ] `Ctrl+\`: Quit (Core Dumped).
    - [ ] `Ctrl+D`: Envía EOF (cierra `cat`).

---

## 🔥 Fase 8: Tests de Estrés ("Go Crazy")
*Cosas que rompen tu shell y te suspenden.*

- [ ] **Comandos vacíos:** Envía una línea vacía (solo enter).
- [ ] **Espacios:** `          ls             -la`.
- [ ] **Argumentos locos:** `echo -nnnnnnn hola`.
- [ ] **Variables raras:** `echo $?????` (debe imprimir el PID del shell si implementado, o nombre del shell, o literal).
- [ ] **Minishell dentro de Minishell:** `./minishell` -> `ls` -> `exit`.
