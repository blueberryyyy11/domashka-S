#include <atomic>

class AtomicCounter {
private:
    std::atomic<int> counter;

public:
    AtomicCounter(int init) : counter(init) {}

    void increment() {
        counter.fetch_add(1);
    }

    int get_value() {
        return counter.load();
    }

    void reset() {
        counter.fetch_and(0);
    }
};

