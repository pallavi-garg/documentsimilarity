#CXXFLAGS=-ggdb -std=c++11 -Wpedantic -Wall -Wextra -Werror -Wzero-as-null-pointer-constant
CXXFLAGS=-std=c++11 #-Wpedantic -Wall -Wextra -Werror -Wzero-as-null-pointer-constant -O3

INC = -I include
SRCS = $(wildcard src/*.cpp)

all: $(SRCS)
	@echo ----------------compiling executable program comparator--------------------
	g++ $(CXXFLAGS) $(SRCS) $(INC) -o comparator 

clean:
	@echo ----------------removing executable program comparator--------------------
	rm comparator
