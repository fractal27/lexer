# lexer

lexer project implemented in c that provides an example for a shared library lexer.
Turns a string(array of char), into an array of `token_t` in C using the as-type-defined struct `lexer_t` as a building block.

---

## Installing

Installation is made using the `install_sh` program.

```bash
$ sudo ./install_sh

[ $${\color{lightblue}WARNING}$$       ] installing as root: using `/usr` path to install library.
[ $${\color{orange}PROCESS}\t] library directory: /usr/lib
[ $${\color{orange}PROCESS}\t] initializing installation
gcc -shared -o dest/liblexer.so dest/lexer.o
[ $${\color{lightgreen} OK}\t] Library successfully made.
[ $${\color{orange}PROCESS}\t] Transfering files.
copied 'dest/liblexer.so' -> '/usr/lib/liblexer.so'
'dest/liblexer.so' removed
[ $${\color{lightgreen} OK}\t] Succesfully moved [1] file(s)
```
it is also nicely colored

