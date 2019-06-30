TEST_DIR = ./test
LIBS=-lgtest -lpthread
LIBS_UI=-lncurses

TESTS =\
	${TEST_DIR}/dataset \
	${TEST_DIR}/model_1

all: ${TESTS} exe/demo

${TEST_DIR}/dataset: dataset.o dataset_test.o
	$(CXX) -o $@ $^ ${LIBS}

${TEST_DIR}/model_1: model_1.o model_1_test.o dataset.o
	$(CXX) -o $@ $^ ${LIBS}

exe/demo: demo.o dataset.o model_1.o
	$(CXX) -o $@ $^ ${LIBS_UI}

%.o: %.cpp %.h
	$(CXX) -o $@ -c $<

clean:
	@rm -f ${TESTS}
