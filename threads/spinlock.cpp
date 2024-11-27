#include <atomic>

class SpinLock {
    private:
    std::atomic_flag flag = ATOMIC_FLAG_INIT;
    public:
        void lock() {
            while(flag.test_and_set());
        } 
        void unlock(){
            flag.clear();
        }
};

class SpinLockCounter {
private:
    int counter;
    SpinLock lock;

public:
    SpinLockCounter(int init = 0) : counter(init) {}

    void increment() {
        lock.lock();
        ++counter;  
        lock.unlock();
    }

    int get_value() {
        lock.lock(); // тут можно не делать лок так как записей не происходит
        int value = counter;
        lock.unlock();
        return value;
    }

    void reset() {
        lock.lock();
        counter = 0;
        lock.unlock();
    }
};

