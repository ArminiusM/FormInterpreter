CC	= g++
CFLAGS	= -g -std=c++0x
LD	= $(CC)
LDFLAGS	=
RM	= rm

OBJS	= ${SRCS:.cpp=.o}

.cpp.o :
	$(CC) $(CFLAGS) -c $<

libFormInterpreter.a:	FormInterpreter.cpp FormInterpreter.h
	$(CC) $(CFLAGS) -c FormInterpreter.cpp
	ar rcs libFormInterpreter.a FormInterpreter.o

test :	main.cpp FormInterpreterFunctions.cpp libFormInterpreter.a
	$(CC) $(CFLAGS) -c main.cpp
	$(CC) $(CFLAGS) -c FormInterpreterFunctions.cpp
	$(LD) -o $@ main.o FormInterpreterFunctions.o libFormInterpreter.a

exa1 :	exa1.cpp libFormInterpreter.a
	$(CC) $(CFLAGS) -c exa1.cpp
	$(LD) -o $@ exa1.o libFormInterpreter.a

exa2 :	exa2.cpp libFormInterpreter.a
	$(CC) $(CFLAGS) -c exa2.cpp
	$(LD) -o $@ exa2.o libFormInterpreter.a

exa3 :	exa3.cpp libFormInterpreter.a
	$(CC) $(CFLAGS) -c exa3.cpp
	$(LD) -o $@ exa3.o libFormInterpreter.a

exa4 :	exa4.cpp libFormInterpreter.a
	$(CC) $(CFLAGS) -c exa4.cpp
	$(LD) -o $@ exa4.o libFormInterpreter.a

exa4a :	exa4a.cpp libFormInterpreter.a
	$(CC) $(CFLAGS) -c exa4a.cpp
	$(LD) -o $@ exa4a.o libFormInterpreter.a

exa5 :	exa5.cpp libFormInterpreter.a
	$(CC) $(CFLAGS) -c exa5.cpp
	$(LD) -o $@ exa5.o libFormInterpreter.a

exa6 :	exa6.cpp libFormInterpreter.a
	$(CC) $(CFLAGS) -c exa6.cpp
	$(LD) -o $@ exa6.o libFormInterpreter.a

exa7 :	exa7.cpp libFormInterpreter.a
	$(CC) $(CFLAGS) -c exa7.cpp
	$(LD) -o $@ exa7.o libFormInterpreter.a

clean :
	-$(RM) -f $(OBJS)

