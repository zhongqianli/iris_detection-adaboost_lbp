mkdir data_dir.lbp
pos_num=18
neg_num=54
threads_num=4
width=30
height=30
opencv_traincascade -data data_dir.lbp -vec pos.vec -bg neg.txt -numPos $pos_num -numNeg $neg_num -numStages 20 -precalcValBufSize 2048 -precalcIdxBufSize 2048 -numThreads $threads_num -featureType LBP -w $width -h $height
