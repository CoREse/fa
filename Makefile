CC=g++
AR=ar
CPPFLAGS= -Wall -O3
LDFLAGS=
LIBS=

FA_OBJS=fa.o
FA_HEADERS=fa.h
EXAMPLE_OBJS=examples/example.o
FA=fa.a

libs:$(FA)

all: $(FA) example

$(FA):$(FA_OBJS)
	$(AR) -rc $@ $(FA_OBJS)

example: $(EXAMPLE_OBJS) $(FA)
	$(LINK.cpp) $^ -o $@

$(FA_OBJS):$(FA_HEADERS)

clean:
	rm *.o *.a examples/*.o example
