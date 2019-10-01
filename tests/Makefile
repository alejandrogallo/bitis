include ../config.mk
CXXFLAGS += -I../src/

TEST_SOURCES = $(wildcard test_*.cpp)
TEST_BIN = $(patsubst %.cpp,%,$(TEST_SOURCES))
TEST_OUT = $(patsubst %.cpp,%.out,$(TEST_SOURCES))
TEST_DIFF = $(patsubst %.cpp,%.diff,$(TEST_SOURCES))

.PHONY: all clean bin out

bin: $(TEST_BIN)
out: $(TEST_OUT)

report: $(TEST_DIFF)
	-@rm $@
	for out in $(TEST_DIFF); do du $$out >> $@; done

all: report

clean:
	-@rm -v $(TEST_DIFF) $(TEST_OUT) $(TEST_BIN)

test_%: test_%.o
	$(CXX) $(CXXFLAGS) $< -o $@

test_%.out: test_%
	./$< > $@

test_%.diff: test_%.out test_%.correct
	diff $? > $@

