width=30
height=30

image_dir_list=(
"images/pos.30x30"
)

echo "create pos.txt"

imagelist_file="pos.txt"
rm -rf $imagelist_file
touch $imagelist_file
for image_dir in ${image_dir_list[*]}
do
	for imagepath in `find $image_dir -name "*" | grep -i -E "bmp|jpg|png"`
	do
		echo $imagepath 1 0 0 $width $height >> pos.txt
	done
done

echo "finish."