#!/bin/bash

path="$1"
str="$2"
new_str="$3"

if [[ -n "$path" && -e "$path" ]]; then
	echo "Получил путь $path"
else
	echo "Введен неверный путь"
	exit
fi

if [ -n "$str" ]; then
	echo "Строка $str принята"
else
	echo "Строка не введена"
	exit
fi

if grep -q "$str" "$path"; then
	sed -i ".bak" "s/$str/$new_str/g" $path
	if grep -q "$str" "$file"; then
		echo "Замена не удалась"
		exit
	else
		echo "Замена успешна"
	fi
else 
	echo "Текст не найден"
	exit
fi

echo "Заменил строку $str на $new_str в файле $path"

file_wc=$(wc -c $path | tr -s ' ')
echo "Получил $file_wc"
date=$(stat -f "%Sm" -t "%Y-%m-%d %H:%M" $path)
echo "Получил $date"
file_sha=$(shasum -a 256 $path | awk '{ print $1 }') 
echo "Получил $file_sha"
echo "$path - $file_wc - $date - $file_sha - sha256" >> "files.log"
