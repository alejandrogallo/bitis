include ../config.mk
CXXFLAGS += -I../src/

TEST_SOURCES = $(wildcard test_*.cpp)
TEST_BIN = $(patsubst %.cpp,%.bin,$(TEST_SOURCES))
TEST_OUT = $(patsubst %.cpp,%.out,$(TEST_SOURCES))
TEST_DIFF = $(patsubst %.cpp,%.diff,$(TEST_SOURCES))

.PHONY: all clean bin out

all: report
bin: $(TEST_BIN)
out: $(TEST_OUT)

report: $(TEST_DIFF)
	echo > $@
	for out in $(TEST_DIFF); do du $$out >> $@; done

clean:
	-@rm -v $(TEST_DIFF) $(TEST_OUT) $(TEST_BIN) report

test_%.bin: test_%.o
	$(CXX) $(CXXFLAGS) $< -o $@

test_%.out: test_%.bin
	./$< > $@

test_%.diff: test_%.out test_%.correct
	diff $? > $@

