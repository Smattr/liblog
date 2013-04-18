# Bob Loblaw's Lib Log

Why should you write logging code that you don't want to? This library is
designed to implement basic logging for a C program, following Bob Loblaw's
no nonsense approach.\*

## Usage

Run `make` to build a static and dynamic library version of liblog. Include
log.h from your C program and link against either the static or dynamic
library.

Call `log_init` on startup, use `LOG` to write a message to the log and
`log_close` on shutdown. It's all pretty self-explanatory from the log.h
header. Feel free to ask me if you have questions.

## Licence
All files in this repository are in the public domain. Do whatever you like
with them.

\* No habla Español.
