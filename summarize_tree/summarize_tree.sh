directory=$1
cd $directory

dirNumber=num_dirs=$(find . -type d | wc -l)
regularFileNum=$(find . -type f | wc -l)

echo "There were $dirNumber directories."
echo "There were $regularFileNum regular files."
