svm_demo : svm_demo.o libsmo.so
	g++ -o svm_demo svm_demo.o -L. -lsmo
libsmo.so: smo.h smo.o common.o
	g++ smo.o common.o -shared -fPIC -o libsmo.so
smo.o : smo.h smo.cpp
	g++ -fPIC -Wno-deprecated -c smo.cpp
common.o : common.cpp
	g++ -fPIC -Wno-deprecated -c common.cpp
svm_demo.o: svm_demo.cpp smo.h
	g++ -fPIC -Wno-deprecated -c svm_demo.cpp
clean:
	rm -rf *.o *.so svm_demo 
