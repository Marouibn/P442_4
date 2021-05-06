LINK_TARGET = test_sequential

OBJS = \
       test_sequential.o \
       Graph.o \

REBUILDABLES = $(OBJS) $(LINK_TARGET)

all: $(LINK_TARGET)

clean:
	rm -f $(REBUILDABLES)

test_sequential: test_sequential.o Graph.o
	g++ -g -o  test_sequential test_sequential.o Graph.o

test_sequential.o: test_sequential.cpp
	g++ -c -g -Werror test_sequential.cpp

Graph.o: Graph.cpp
	g++ -c -g -Werror Graph.cpp

git:
	git add --all;git commit -m "Automatic git";git push
