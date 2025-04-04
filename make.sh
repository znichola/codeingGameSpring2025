CFLAGS="-Wall -Wextra -Werror"

rm -f ceph

g++ -std=c++17 $CFLAGS *.cpp -o ceph && \
echo 40 0 6 0 2 2 2 1 6 1 | ./ceph

