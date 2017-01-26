gcc -o test *.c `pkg-config --cflags --libs cairo` -lxcb -Wextra -Wall -Wno-incompatible-pointer-types -g
