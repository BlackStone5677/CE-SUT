#!/bin/bash

EXTENSIONS=("pdf" "docx" "wav" "mp3" "mp4" "xlsx" "png" "jpg" "jpeg" "zip" "rar")

for ext in "${EXTENSIONS[@]}"; do
    find . -type f -name "*.$ext" -not -path "./.dvc/*" | while read -r file; do
        if [ ! -f "$file.dvc" ]; then
            echo "DVC adding: $file"
            git rm --cached "$file"
            dvc add "$file"
        fi
    done
done

git add *.dvc

echo "Remember to commit the changes with git commit -m 'Add large files to DVC'"