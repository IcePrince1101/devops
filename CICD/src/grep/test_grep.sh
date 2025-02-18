#!/ bin / bash

fails=0
success=0

pattern='Hello'
pattern_file='pattern.txt'
file='test.txt'
non_file='nonfile.txt'
second_pattern='aaa'

echo "" > log_grep.txt

flags=(
  "c"
  "h"
  "i"
  "n"
  "s"
  "v"
)

echo "____TESTING_SINGLE_GREP_FLAGS____"

for flag in "${flags[@]}"
do
    grep "-$flag" $pattern $file > grep.txt
    ../s21_grep "-$flag" $pattern $file > s21_grep.txt
    diff -q grep.txt s21_grep.txt
    if [ $? -eq 0 ]
    then
        (( success++ ))
        echo "OK: grep -$flag $pattern $file"
    else
        echo "../s21_grep -$flag $pattern $file" >> log_grep.txt
        (( fails++ ))
        echo "FAIL: grep -$flag $pattern $file"
    fi
done

echo "____TESTING_GREP_2_PATTERNS____"

for flag in "${flags[@]}"
do
    grep "-$flag" $pattern $file > grep.txt
    ../s21_grep "-$flag" $pattern $file > s21_grep.txt
    diff -q grep.txt s21_grep.txt
    if [ $? -eq 0 ]
    then
        (( success++ ))
        echo "OK: grep -$flag $pattern $second_pattern $file"
    else
        echo "../s21_grep -$flag $pattern $second_pattern $file" >> log_grep.txt
        (( fails++ ))
        echo "FAIL: grep -$flag $pattern $second_pattern $file"
    fi
done

for flag in "${flags[@]}"
do
    grep "-$flag" $pattern $file > grep.txt
    ../s21_grep "-$flag" $pattern $file > s21_grep.txt
    diff -q grep.txt s21_grep.txt
    if [ $? -eq 0 ]
    then
        (( success++ ))
        echo "OK: grep -$flag -e $pattern -e $second_pattern $file"
    else
        echo "../s21_grep -$flag -e $pattern -e $second_pattern $file" >> log_grep.txt
        (( fails++ ))
        echo "FAIL: grep -$flag -e $pattern -e $second_pattern $file"
    fi
done

echo "____TESTING_GREP_FLAGS_PAIRS____"

for flag1 in "${flags[@]}"
do
    for flag2 in "${flags[@]}"
    do
        if [ $flag1 != $flag2 ]
        then
            grep "-$flag1$flag2" $pattern $file > grep.txt
            ../s21_grep "-$flag1$flag2" $pattern $file > s21_grep.txt
            diff -q grep.txt s21_grep.txt
            if [ $? -eq 0 ]
            then
                (( success++ ))
                echo "OK: grep -$flag1$flag2 $pattern $file"
            else
                echo "../s21_grep -$flag1$flag2 $pattern $file" >> log_grep.txt
                (( fails++ ))
                echo "FAIL: grep -$flag1$flag2 $pattern $file"
            fi
        fi
    done
done

grep "-o" $pattern $file > grep.txt
../s21_grep "-o" $pattern $file > s21_grep.txt
diff -q grep.txt s21_grep.txt
if [ $? -eq 0 ]
then
    (( success++ ))
    echo "OK: -o $pattern $file"
else
    echo "../s21_grep -o $pattern $file" >> log_grep.txt
    (( fails++ ))
    echo "FAIL: -o $pattern $file"
fi

echo "____TESTING_GREP_FLAG_F____"

grep "-f" $pattern_file $file > grep.txt
../s21_grep "-f" $pattern_file $file > s21_grep.txt
diff -q grep.txt s21_grep.txt
if [ $? -eq 0 ]
then
    (( success++ ))
    echo "OK: -f $pattern_file $file"
else
    echo "../s21_grep -f $pattern_file $file" >> log_grep.txt
    (( fails++ ))
    echo "FAIL: -f $pattern_file $file"
fi


echo "SUCCESS: $success"
echo "FAIL $fails"



rm -f grep.txt s21_grep.txt

exit 0