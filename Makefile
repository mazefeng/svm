CC = g++
CFLAGS = -shared -fPIC -Wno-deprecated

main : main.o libsvm.so
	$(CC) -o light-svm main.o -L. -lsvm
	cp libsvm.so test/
libsvm.so: svm_option.o svm_solver.o svm_common.o
	$(CC) $(CFLAGS) svm_option.o svm_solver.o svm_common.o -o libsvm.so
svm_option.o : svm_option.h svm_option.cpp
	$(CC) $(CFLAGS) -c svm_option.cpp
svm_solver.o : svm_solver.h svm_solver.cpp
	$(CC) $(CFLAGS) -c svm_solver.cpp
svm_common.o : svm_common.h svm_common.cpp
	$(CC) $(CFLAGS) -c svm_common.cpp
main.o: main.cpp svm_option.h svm_solver.h svm_common.h
	$(CC) $(CFLAGS) -c main.cpp
clean:
	rm -rf *.o *.so light-svm test/libsvm.so
