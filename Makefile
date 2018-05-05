CC = gcc
FLAGS = -g 
OBJ = atob.o btoa.o jabber.o wocky.o 
EXEC = atob btoa jabber wocky test-me 
TEST_ASCII = hollow

all: $(EXEC)

test-me: jabber wocky atob btoa
	./atob $(TEST_ASCII).txt bit-$(TEST_ASCII).txt;
	./jabber bit-$(TEST_ASCII).txt zap-$(TEST_ASCII).txt;
	./wocky zap-$(TEST_ASCII).txt kapow-$(TEST_ASCII).txt;
	./btoa kapow-$(TEST_ASCII).txt out.txt;
	diff $(TEST_ASCII).txt out.txt

jabber: jabber.o 
	$(CC) $(FLAGS) -o jabber jabber.o 

wocky: wocky.o
	$(CC) $(FLAGS) -o wocky wocky.o

atob: atob.o 
	$(CC) $(FLAGS) -o atob atob.o

btoa: btoa.o 
	$(CC) $(FLAGS) -o btoa btoa.o 

jabber.o: jabber.c
	$(CC) $(FLAGS) -c jabber.c

wocky.o: wocky.c
	$(CC) $(FLAGS) -c wocky.c

atob.o: atob.c
	$(CC) $(FLAGS) -c atob.c

btoa.o: btoa.c
	$(CC) $(FLAGS) -c btoa.c

clean:
	rm -f $(OBJ) $(EXEC) bit-$(TEST_ASCII).txt zap-$(TEST_ASCII).txt kapow-$(TEST_ASCII).txt out.txt

