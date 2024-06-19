obj-m = multifile.o
multifile-objs = file1.o file2.o

modules:
	make -C /lib/modules/`uname -r`/build M=`pwd` modules

clean:
	make -C /lib/modules/`uname -r`/build M=`pwd` clean
