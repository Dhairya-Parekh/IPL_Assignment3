cd $(dirname $0)
rm -rf asm/ output/ stdout/ debug/
make clean
GCC="gcc -fno-asynchronous-unwind-tables -fno-exceptions -fno-pic -fno-stack-protector -mpreferred-stack-boundary=2 -m32"
mkdir -p  ./asm/ ./output/ ./stdout/ ./debug/
make
for testpath in ./tests/*.c; do
    testname=$(basename $testpath .c)
    echo "Testing $testname"
    ./iplC ./tests/$testname.c > ./asm/our_$testname.s 2> ./debug/iplC_asm_$testname.txt
    $GCC ./asm/our_$testname.s -o ./output/our_$testname.o 2> ./debug/iplC_o_$testname.txt
    ./output/our_$testname.o > ./stdout/our_$testname.txt
    sed -i '1i #include <stdio.h>' ./tests/$testname.c
    $GCC -Werror -S ./tests/$testname.c -o ./asm/gcc_$testname.s 2> ./debug/gcc_asm_$testname.txt
    $GCC ./asm/gcc_$testname.s -o ./output/gcc_$testname.o 2> ./debug/gcc_o_$testname.txt
    ./output/gcc_$testname.o > ./stdout/gcc_$testname.txt
    sed -i '1d' ./tests/$testname.c
done