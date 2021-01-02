a.out: main.c parser.o fun_stack.o store.o keyword.o alex.o
	#$(CC) $^
	cc main.c parser.o fun_stack.o store.o keyword.o alex.o -ggdb
main.o: parser.h fun_stack.h store.h keyword.h alex.h
parser.o: parser.h fun_stack.h store.h keyword.h alex.h
	cc -c parser.c parser.h fun_stack.h store.h keyword.h alex.h -ggdb
fun_stack.o: fun_stack.h
	cc -c fun_stack.c fun_stack.h -ggdb
store.o: store.h
	cc -c store.c store.h -ggdb
keyword.o: keyword.h
	cc -c keyword.c keyword.h -ggdb
alex.o: alex.h keyword.h
	cc -c alex.c alex.h keyword.h -ggdb

