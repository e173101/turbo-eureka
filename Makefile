TEST_DIR = ./test
LIBS=-lgtest -lpthread


TESTS =\
	${TEST_DIR}/dataset \
	${TEST_DIR}/model_1

# ${TEST_DIR}/%: %.o %_test.o 
	# $(CXX) -o $@ $^ ${LIBS}
all: ${TESTS}

${TEST_DIR}/dataset: dataset.o dataset_test.o
	$(CXX) -o $@ $^ ${LIBS}

${TEST_DIR}/model_1: model_1.o model_1_test.o dataset.o
	$(CXX) -o $@ $^ ${LIBS}

%.o: %.cpp
	$(CXX) -o $@ -c $<


clean:
	@rm -f ${TESTS}
