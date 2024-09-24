CXX=g++
BIN := ./bin

LDFLAGS=-lz -pthread -static
INCLUDE=-I./include
LIBS=-L./lib 

CXXFLAGS= -g  -O3  $(INCLUDE) $(LIBS)
#  you can add the [ -I /path/.../samtools-1.6/htslib-1.6   -L /path/.../samtools-1.6/htslib-1.6 ] here #no need by OligoReadCut


all: $(BIN)/OligoReadCut

$(BIN)/OligoReadCut: $(BIN)/../src/OligoReadCut.o 
	$(CXX)   $^ -o $@   $(LDFLAGS)  $(INCLUDE) $(LIBS)

$(BIN)/%.o: %.cpp
	$(CXX)  -c $(CXXFLAGS)  $< -o $@ 

clean:
	$(RM) $(BIN)/*.o  $(BIN)/../src/*.o

