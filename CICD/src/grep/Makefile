CC_FLAGS = -Wall -Wextra -Werror

all: s21_grep test

s21_grep: s21_grep.c file_work.c flags.c
	gcc $(CC_FLAGS) s21_grep.c file_work.c flags.c -o s21_grep

test:
	bash test_grep.sh

clean:
	rm -rf s21_grep
	rm -f *.o *.gch

rebuild: clean all
