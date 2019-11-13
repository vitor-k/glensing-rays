for oldFileName in *.tga; do
    [ -f "$oldFileName" ] || break         # Break out if no .tga files found.
    newFileName=${oldFileName//.tga/.png}
    magick $oldFileName $newFileName
    rm $oldFileName
    echo "Converted $oldFileName to $newFileName"
done