all: test_preprocessed 


#This Test is failing
test_preprocessed:
	g++ -shared -fPIC -o libmyLib.so LibPreprocessed.cpp  -O2
	g++ -o main -std=c++11 mainPreprocessed.cpp -L. -l myLib
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:. ./main

#This Test is failing
test1:
	g++ -shared -fPIC -o libmyLib.so Lib.cpp  -O2
	g++ -o main -std=c++11 main.cpp -L. -l myLib
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:. ./main

#This test runs only -O2 on the library removed
test2:
	g++ -shared -fPIC -o libmyLib.so Lib.cpp
	g++ -o main -std=c++11 main.cpp -L. -l myLib
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:. ./main

#This test is running (added c++11 to the lib)
test3:
	g++ -shared -fPIC -std=c++11 -o libmyLib.so Lib.cpp -O2
	g++ -o main -std=c++11 main.cpp -L. -l myLib
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:. ./main

#Test is running (removed c++11 from both)
test4:
	g++ -shared -fPIC -o libmyLib.so Lib.cpp -O2
	g++ -o main main.cpp -L. -l myLib
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:. ./main

#Failing too (as expected)
test5:
	g++ -shared -fPIC -o libmyLib.so Lib.cpp -O2 -D_GLIBCXX_USE_CXX11_ABI=1
	g++ -o main main.cpp -std=c++11 -L. -l myLib -D_GLIBCXX_USE_CXX11_ABI=1
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:. ./main

test6:
	clang++-3.4 -shared -fPIC -o libmyLib.so Lib.cpp -O2
	clang++-3.4 -o main main.cpp -std=c++11 -L. -l myLib
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:. ./main
