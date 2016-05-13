ex_one: 
	clang++ -std=c++11 -g main.cpp A.cpp b1/B.cpp -I./ -I./b1/ -o main
ex_two:
	clang++ -std=c++11 -g main.cpp A.cpp b2/B.cpp -I./ -I./b2/ -o main
ex_three:
	clang++ -std=c++11 -g main.cpp b3/C.cpp A.cpp b3/B.cpp -I./ -I./b3/ -o main
ex_four:
	clang++ -std=c++11 -g main.cpp b4/C.cpp A.cpp b4/B.cpp -I./ -I./b4/ -o main
ex_five:
	clang++ -std=c++11 -g main.cpp b5/C.cpp A.cpp b5/B.cpp -I./ -I./b5/ -o main
ex_four_assembly:
	clang++ -std=c++11 -S main.cpp b4/C.cpp A.cpp b4/B.cpp -I./ -I./b4/

clean:
	rm main
	rm -r main.dSYM
