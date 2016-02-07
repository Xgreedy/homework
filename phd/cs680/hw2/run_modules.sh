# run hello_(1,2,3).ko for C680 homework2
# Weiwei Jia <wj47@njit.edu>

make

for i in 1 2 3
do
	file="hello-$i.ko"
	sudo insmod $file
	sudo rmmod $file
done

make clean
