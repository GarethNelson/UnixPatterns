CCFLAGS=-Wall

all: filter_tool cantrip_tool source_tool sink_tool sponge_tool compiler_tool ed_tool roguelike_tool

clean:
	rm bin/*

filter_tool: src/filter.c
	cc ${CCFLAGS} src/filter.c -o bin/filter_tool

cantrip_tool:
	cc ${CCFLAGS} src/cantrip.c -o bin/cantrip_tool

source_tool:
	cc ${CCFLAGS} src/source.c -o bin/source_tool

sink_tool:
	cc ${CCFLAGS} src/sink.c -o bin/sink_tool

sponge_tool:
	cc ${CCFLAGS} src/sponge.c -o bin/sponge_tool

compiler_tool:
	cc ${CCFLAGS} src/compiler.c -o bin/compiler_tool

ed_tool:
	cc ${CCFLAGS} src/ed.c -o bin/ed_tool

roguelike_tool:
	cc ${CCFLAGS} src/roguelike.c -lcurses -o bin/roguelike_tool

