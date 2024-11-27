#include <mutex>

class MutexCounter {
private:
    int counter;
    std::mutex mtx;

public:
    MutexCounter() : counter(0) {}

    void increment() {
        std::lock_guard<std::mutex> lock(mtx);
        ++counter;
    }

    int get_value() {
        std::lock_guard<std::mutex> lock(mtx);
        return counter;
    }

    void reset() {
        std::lock_guard<std::mutex> lock(mtx);
        counter = 0;
    }
};

