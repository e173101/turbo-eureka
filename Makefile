EXE_DIR = ./exe
LIBS=-lgtest -lpthread

EXES =\
	${EXE_DIR}/dataset_test \
	${EXE_DIR}/model_1_test

${EXE_DIR}/dataset_test: dataset_test.cpp dataset.cpp
	$(CXX) dataset_test.cpp dataset.cpp -o $@ ${LIBS}

${EXE_DIR}/model_1_test: model_1_test.cpp dataset.cpp model_1.cpp
	$(CXX) model_1_test.cpp model_1.cpp dataset.cpp -o $@ ${LIBS}

all: ${EXES}
