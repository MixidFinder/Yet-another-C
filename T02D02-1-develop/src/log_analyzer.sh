#!bin/bash

log_file="$1"

if [ ! -f "$log_file" ]; then
    echo "Файл '$log_file' не найден."
    exit 
fi

total_records=$(wc -l < "$log_file")

unique_files=$(awk -F ' - ' '{print $1}' "$log_file" | sort | uniq | wc -l)

hash_changes=$(awk -F ' - ' '{if ($4 != "") print $4}' "$log_file" | sort | uniq | wc -l)

echo "Всего записей: $total_records Уникальных файлов: $unique_files Количество изменений: $hash_changes"
