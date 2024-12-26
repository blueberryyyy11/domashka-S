#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <random>
#include <chrono>

void sum_array_section(const std::vector<int>& array, size_t start, size_t end, uint64_t& result) {
    result = std::accumulate(array.begin() + start, array.begin() + end, uint64_t(0));
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <array_size> <num_threads>\n";
        return EXIT_FAILURE;
    }

    size_t array_size = std::stoull(argv[1]);
    size_t num_threads = std::stoull(argv[2]);

    // Initialize the array with random values
    std::vector<int> array(array_size);
    std::mt19937_64 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 100);
    for (auto& element : array) {
        element = dist(rng);
    }

    // Sum the array without threads
    auto start_time = std::chrono::high_resolution_clock::now();
    uint64_t total_sum = std::accumulate(array.begin(), array.end(), uint64_t(0));
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_single = end_time - start_time;

    // Sum the array with multiple threads
    start_time = std::chrono::high_resolution_clock::now();
    std::vector<std::thread> threads;
    std::vector<uint64_t> partial_sums(num_threads, 0);
    size_t block_size = array_size / num_threads;
    for (size_t i = 0; i < num_threads; ++i) {
        size_t start = i * block_size;
        size_t end = (i == num_threads - 1) ? array_size : start + block_size;
        threads.emplace_back(sum_array_section, std::cref(array), start, end, std::ref(partial_sums[i]));
    }
    for (auto& t : threads) {
        t.join();
    }
    uint64_t parallel_sum = std::accumulate(partial_sums.begin(), partial_sums.end(), uint64_t(0));
    end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_multi = end_time - start_time;

    // Output the results
    std::cout << "Time spent without threads: " << duration_single.count() << " seconds\n";
    std::cout << "Time spent with " << num_threads << " threads: " << duration_multi.count() << " seconds\n";

    return EXIT_SUCCESS;
}

