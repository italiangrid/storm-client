source clients-setup.sh
./autogen.sh
./configure CFLAGS=-g CXXFLAGS=-g
make clean
make
