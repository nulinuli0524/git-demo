#!/bin/bash
mkdir -p pclm_output
for file in pdfs/*.pdf; do
  filename=$(basename "$file" .pdf)
  gs -dBATCH -dNOPAUSE -sDEVICE=pclm \
    -sOutputFile="pclm_output/${filename}.pclm" "$file"
done
