# lexer

lexer project implemented in c that provides an example for a shared library lexer.
Turns a string(array of char), into an array of `token_t` in C using the as-type-defined struct `lexer_t` as a building block.

---

## Installing

Installation is made using the `install_sh` program.

```bash
$ sudo ./install_sh

[ WARNING    ] installing as root: using `/usr` path to install library.
[ PROCESS    ] library directory: /usr/lib
[ PROCESS    ] initializing installation
gcc -shared -o dest/liblexer.so dest/lexer.o
[ OK   ] Library successfully made.
[ PROCESS    ] Transfering files.
copied 'dest/liblexer.so' -> '/usr/lib/liblexer.so'
'dest/liblexer.so' removed
[ OK   ] Succesfully moved [1] file(s)
```
It is also nicely colored with 'OK' being green, 'PROCESS' being orange and 'WARNING' being blue.
