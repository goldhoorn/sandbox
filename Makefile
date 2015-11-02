all: test1

test1:
	g++ -shared -fPIC -o libmyLib.so Lib.cpp  main.cpp -O2
	g++ -o main -std=c++11 main.cpp -L. -l myLib
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:. ./main

test2:
	g++ -shared -fPIC -o libmyLib.so Lib.cpp  main.cpp 
	g++ -o main -std=c++11 main.cpp -L. -l myLib
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:. ./main

test3:
	g++ -shared -fPIC -std=c++11 -o libmyLib.so Lib.cpp  main.cpp -O2
	g++ -o main -std=c++11 main.cpp -L. -l myLib
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:. ./main

test4:
	g++ -shared -fPIC -o libmyLib.so Lib.cpp  main.cpp -O2
	g++ -o main main.cpp -L. -l myLib
	LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:. ./main
