CXX = g++
CXXFLAGS = -std=c++17  -g -O2 -pthread 

# sync_test 타겟 이름
SRC_SYNC = main.cpp spinlock.cpp sleep_mutex.cpp
TARGET_SYNC = sync_compare


all: $(TARGET_SYNC)

# sync_test 타겟 빌드 규칙
$(TARGET_SYNC): $(SRC_SYNC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# clean 시 두 타겟 모두 삭제
clean:
	rm -f $(TARGET_SYNC) 
