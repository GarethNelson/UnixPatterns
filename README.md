# UnixPatterns
For the hell of it, implementation of some unix design patterns inspired by ESR's text "the art of unix programming":

* Filter pattern - a tool that takes stuff in on stdin and spits it out on stdout

* Cantrip pattern - a tool that only returns a value, does not take params or talk to stdio at all

* Source pattern - a tool that just spits stuff out to stdout

* Sink pattern - a tool that reads stuff in from stdin and does stuff with it

* Sponge pattern - a tool that reads the whole of stdin and does stuff with it

* Compiler pattern - a tool that reads a file, does something with it, and spits out another file

* Ed pattern - a command-line tool similar to ed (or more modern: gdb and friends)

* Roguelike pattern - a full-screen CURSES program (like rogue, or vim, or whatever)

# Why?

Partly boredom, and partly because these patterns are useful and so it makes sense to have some templates.

