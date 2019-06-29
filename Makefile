EXE_DIR = ./exe
LIBS=-lgtest -lpthread

EXES =\
	${EXE_DIR}/dataset_test

${EXE_DIR}/dataset_test: dataset_test.cpp dataset.cpp
	$(CXX) dataset_test.cpp dataset.cpp -o $@ ${LIBS}

all: ${EXES}
