#!/bin/bash

# List of extensions to track
EXTENSIONS=("pdf" "docx" "wav" "mp3" "mp4" "xlsx" "png" "jpg" "jpeg" "zip" "rar")

# Loop through extensions and add files to DVC
for ext in "${EXTENSIONS[@]}"; do
    # Find all files with the extension, excluding .dvc folder
    find . -type f -name "*.$ext" -not -path "./.dvc/*" | while read file; do
        echo "Adding $file to DVC..."
        git rm --cached "$file"
        dvc add "$file"
    done
done

# Add all .dvc files to Git
git add *.dvc

echo "All files added to DVC and .dvc files staged for Git."
echo "Remember to commit the changes: git commit -m 'Add large files to DVC'"