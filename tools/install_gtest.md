# Install GTest Packages

In running the test applications we may need gtest if the gtest is not
already installed. 

## Ubuntu 16.04 Installation

This will install the gtest development pacakges.

	sudo apt-get install libgtest-dev

Then cmake must be used to build the source packages.
If you don't have cmake please install it first. 

	sudo apt-get install cmake
	

Then move to the gtest folder

	cd /usr/src/gtest

After that use cmake to make the list

	sudo cmake CMakeLists.txt
	sudo make
	
After compiling copy the files to /usr/lib folder
	
	sudo co *.a /usr/lib
