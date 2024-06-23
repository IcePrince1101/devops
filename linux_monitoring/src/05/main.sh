#!/bin/bash

dirname=$1

if [[ $# != 1 ]]
then
    echo "Need 1 args"
    exit 1
elif [[ ${dirname: -1} != "/" ]]
then
    echo "Arg must end with '/'"
    exit 1
fi


start=`date +%s.%N`

#1 count of folders
count_folders=$(find $dirname -type d | wc -l)
echo -n "Count of folders: "
echo $count_folders

#2 Top 5 folders by size (desc)
top_5_folders=$(sudo du -Sh $dirname | sort -rh | head -5 | cat -n | awk '{print $1" - "$3", "$2}')
echo "TOP 5 folders of maximum size arranged in descending order (path and size):"
echo "$top_5_folders"

#3 total count of files
count_files=$(find $dirname -type f | wc -l)
echo -n "Count of files: "
echo $count_files

#4 Number of:
#4.1 .conf files
count_conf=$(find $dirname -name "*.conf" | wc -l)
echo -n "Configuration files (with the .conf extension) = "
echo $count_conf

#4.2 text files
count_text=$(find $dirname -name "*.txt" | wc -l)
echo -n "Text files = "
echo $count_text

#4.3 executable files
count_exec=$(find $dirname -executable -type f | wc -l)
echo -n "Executable files = "
echo $count_exec

#4.4 log files
count_log=$(find $dirname -name "*.log" | wc -l)
echo -n "Log files (with the extension .log) = "
echo $count_log

#4.5 archive files
count_archive=$(find $dirname -name "*.tar" -o -name "*.gz" -o -name "*.zip" | wc -l)
echo -n "Archive files = "
echo $count_archive

#4.5 synmbolic files
count_symbolic=$(find $dirname -type l | wc -l)
echo -n "Symbolic links = "
echo $count_symbolic

#5 TOP 10 files of maximum size arranged in descending order
top_10_files=$(find $dirname -type f -exec du -Sh {} +  | sort -rh | head -10 | cat -n | awk '{print $1" - "$3", "$2}')
echo "TOP 10 files of maximum size arranged in descending order (path, size and type):"
echo "$top_10_files"

#6 TOP 10 executable files of the maximum size arranged in descending order
top_10_exec=$(find $dirname -type f -exec du -Sh {} + | grep .exe | sort -hr | head -10 | cat -n | awk '{print $1" - "$3", "$2}')
echo "TOP 10 executable files of maximum size arranged in descending order (path, size and MD5 hash of file):"
echo "$top_10_exec"

end=`date +%s.%N`
runtime=$(echo "$end - $start" | bc -l )
echo "Script execution time (seconds): $runtime"