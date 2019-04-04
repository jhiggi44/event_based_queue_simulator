make:
	clang++ -std=c++17 main.cpp Events.cpp -o runSim

test:
	chmod +x test.sh
	./test.sh
