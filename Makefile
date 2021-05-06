LINK_TARGET = test_sequential

OBJS = \
       test_sequential.o \
       Graph.o \
       Arc.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

all: $(LINK_TARGET)

clean:
	rm -f $(REBUILDABLES)

test_sequential: test_sequential.o Graph.o Arc.o
	g++ -g -o  test_sequential test_sequential.o Graph.o Arc.o

test_sequential.o: test_sequential.cpp
	g++ -c -g -Werror test_sequential.cpp

Graph.o: Graph.cpp
	g++ -c -g -Werror Graph.cpp

Arc.o: Arc.cpp
	g++ -c -g -Werror Arc.cpp

git:
	git add --all;git commit -m "Automatic git";git push
