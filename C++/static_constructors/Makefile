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
	clang++ -std=c++11 -S -fno-stack-protector main.cpp b4/C.cpp A.cpp b4/B.cpp -I./ -I./b4/
ex_six:
	clang++ -std=c++11 -g main.cpp b6/C.cpp A.cpp b6/B.cpp -I./ -I./b6/ -o main
ex_seven:
	clang++ -std=c++11 -g main_2.cpp b7/D.cpp b7/C.cpp A2.cpp b7/B.cpp -I./ -I./b7/ -o main_2

clean:
	rm main
	rm -r main.dSYM
