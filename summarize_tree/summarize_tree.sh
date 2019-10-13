directory=$1

dirNumber=$(find $directory -type d| wc -l |xargs)
regularFileNum=$(find $directory -type f| wc -l|xargs)
echo "There were" $dirNumber "directories."
echo "There were" $regularFileNum "regular files."
