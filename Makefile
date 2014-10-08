CC = g++
CFLAGS = -shared -fPIC -Wno-deprecated

svm_demo : svm_demo.o libsmo.so
	$(CC) -o svm_demo svm_demo.o -L. -lsmo
libsmo.so: smo.h smo.o common.o
	$(CC) $(CFLAGS) smo.o common.o -o libsmo.so
smo.o : smo.h smo.cpp
	$(CC) $(CFLAGS) -c smo.cpp
common.o : common.cpp
	$(CC) $(CFLAGS) -c common.cpp
svm_demo.o: svm_demo.cpp smo.h
	$(CC) $(CFLAGS) -c svm_demo.cpp
clean:
	rm -rf *.o *.so svm_demo 
