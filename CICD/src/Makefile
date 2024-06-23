CC_FLAGS = -Wall -Wextra -Werror

all: s21_cat s21_grep

s21_cat: cat/s21_cat.c cat/file_work.c cat/flags.c
	gcc $(CC_FLAGS) cat/s21_cat.c cat/file_work.c cat/flags.c -o s21_cat

s21_grep: grep/s21_grep.c grep/file_work.c grep/flags.c
	gcc $(CC_FLAGS) grep/s21_grep.c grep/file_work.c grep/flags.c -o s21_grep

create_ascii: create_ascii.c
	gcc $(CC_FLAGS) create_ascii.c -o create_ascii

clean:
	rm -rf s21_cat s21_grep create_ascii
	rm -f cat/*.o cat/*.gch grep/*.o grep/*.gch *.o *.gch

clang-format:
	cp ../materials/linters/.clang-format .
	clang-format -i */*.c
	rm -f .clang-format

rebuild: clean all

tests: test-cat test_grep

test-cat:
	cd cat && bash test_cat.sh

test_grep:
	cd grep && bash test_grep.sh

push:
	cd .. && git add . && git commit -m "finish" && git push origin develop
