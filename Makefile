all: submission

submission: shirley_wang_C++.cpp
	g++ -Wall -o submission shirley_wang_C++.cpp

clean: 
	rm -f shirley_wang_C++.tar.gz
	rm -rf *.o submission *out.
