CXX = g++
CXXFLAGS = -Wall -Wno-uninitialized
BINARIES = testbst

all: $(BINARIES)
 
test: testbst.cpp intbst.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

testbst.cpp: testbst.o intbst.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	/bin/rm -f *.o $(BINARIES)

git:
	git status
	git add intbst.cpp
	git commit -m "intbst.cpp updated"
	git push origin main