image_dir_list=(
"images/neg"
)

echo "create neg.txt"

imagelist_file="neg.txt"
rm -rf $imagelist_file
touch $imagelist_file
for image_dir in ${image_dir_list[*]}
do
	find $image_dir -name "*" | grep -i -E "bmp|jpg|png" >> $imagelist_file
done

echo "finish."