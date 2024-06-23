#!/ bin / bash

success=0
fail=0
DIFF_RES=""
file="test.txt"
echo "" > log_cat.txt

flags=(
  "-b"
  "-e"
  "-n"
  "-s"
  "-t"
  "-v"
#"-E"
#"-T"
#"--number-nonblank"
#"--number"
#"--squeeze-blank"
)

for var in "${flags[@]}"
do
          TEST1="$var $file"
          echo "$TEST1"
          ../s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( success++ ))
            else
              echo "$TEST1" >> log_cat.txt
              (( fail++ ))
          fi
          rm s21_cat.txt cat.txt
done

for var in "${flags[@]}"
do
  for var2 in "${flags[@]}"
  do
        if [ $var != $var2 ]
        then
          TEST1="$var $var2 $file"
          echo "$TEST1"
          ../s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( success++ ))
            else
              echo "$TEST1" >> log_cat.txt
              (( fail++ ))
          fi
          rm s21_cat.txt cat.txt
        fi
  done
done

for var in "${flags[@]}"
do
  for var2 in "${flags[@]}"
  do
      for var3 in "${flags[@]}"
      do
        if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ]
        then
          TEST1="$var $var2 $var3 $file"
          echo "$TEST1"
          ../s21_cat $TEST1 > s21_cat.txt
          cat $TEST1 > cat.txt
          DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
          if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
            then
              (( success++ ))
            else
              echo "$TEST1" >> log_cat.txt
              (( fail++ ))
          fi
          rm s21_cat.txt cat.txt

        fi
      done
  done
done

for var in "${flags[@]}"
do
  for var2 in "${flags[@]}"
  do
      for var3 in "${flags[@]}"
      do
          for var4 in "${flags[@]}"
          do
            if [ $var != $var2 ] && [ $var2 != $var3 ] && [ $var != $var3 ] && [ $var != $var4 ] && [ $var2 != $var4 ] && [ $var3 != $var4 ]
            then
              TEST1="$var $var2 $var3 $var4 $file"
              echo "$TEST1"
              ../s21_cat $TEST1 > s21_cat.txt
              cat $TEST1 > cat.txt
              DIFF_RES="$(diff -s s21_cat.txt cat.txt)"
              if [ "$DIFF_RES" == "Files s21_cat.txt and cat.txt are identical" ]
                then
                  (( success++ ))
                else
                  echo "$TEST1" >> log_cat.txt
                  (( fail++ ))
              fi
              rm s21_cat.txt cat.txt

            fi
          done
      done
  done
done

echo "SUCCESS: $success"
echo "FAIL: $fail"
