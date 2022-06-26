.PHONY = all clean

CC = gcc

deps = $(wildcard *.c)
BINS = $(deps:%.c=%.o)

all: ${BINS} game.exe

${BINS}: ${deps}
	@echo "\nGenerating binary objects"
	${CC} -c $^

game.exe: ${BINS}
	@echo "\nGenerating executable"
	${CC} $^ -o $@ ${LINKERS}
	@echo "\n"

clean:
	@echo "\nRemoving all binary and executable files\n"
	@rm -rvf *.o
	@rm -rvf *.exe
	@echo "\n"
