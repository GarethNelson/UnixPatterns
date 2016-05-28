filter_tool: src/filter.c
	cc src/filter.c -o bin/filter_tool

cantrip_tool:

source_tool:

sink_tool:

sponge_tool:

compiler_tool:

ed_tool:

roguelike_tool:

all: filter_tool cantrip_tool source_tool sink_tool sponge_tool compiler_tool ed_tool roguelike_tool

clean:
	rm bin/*
