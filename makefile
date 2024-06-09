all: oiak_c_bb

oiak_c_bb: oiak_c_bb.o
	ld oiak_c_bb.o -o oiak_c_bb

oiak_c_bb.o: oiak_c_bb.s
	as -oiak_c_bb.s -o oiak_c_bb.o