CC_FLAGS = -Wall -Wextra -Werror

all: s21_cat create_ascii test

s21_cat: s21_cat.c file_work.c flags.c
	gcc $(CC_FLAGS) s21_cat.c file_work.c flags.c -o s21_cat

create_ascii: create_ascii.c
	gcc $(CC_FLAGS) create_ascii.c -o create_ascii

test:
	bash test_cat.sh

clean:
	rm -rf s21_cat create_ascii
	rm -f *.o *.gch

rebuild: clean all