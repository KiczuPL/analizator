a.out: main.c parser.o fun_stack.o store.o keyword.o alex.o def_end.o inc.o
	#$(CC) $^
	cc main.c parser.o fun_stack.o store.o keyword.o alex.o def_end.o inc.o -ggdb
main.o: parser.h fun_stack.h store.h keyword.h alex.h def_end.h
parser.o: parser.h fun_stack.h store.h keyword.h alex.h def_end.h
	cc -c parser.c parser.h fun_stack.h store.h keyword.h alex.h def_end.h -ggdb
fun_stack.o: fun_stack.h
	cc -c fun_stack.c fun_stack.h -ggdb
store.o: store.h
	cc -c store.c store.h -ggdb
keyword.o: keyword.h
	cc -c keyword.c keyword.h -ggdb
alex.o: alex.h keyword.h
	cc -c alex.c alex.h keyword.h -ggdb
def_end.o: def_end.h
	cc -c def_end.c def_end.h -ggdb
inc.o: inc.h
	cc -c inc.c inc.h -ggdb
