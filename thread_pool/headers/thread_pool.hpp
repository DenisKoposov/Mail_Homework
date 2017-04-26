#pragma once

#include <iostream>
#include <condition_variable>
#include <thread>
#include <queue>
#include <atomic>
#include <mutex>
#include <functional>
#include <random>
#include <error_codes.hpp>

struct probability_calculator
{
    void operator() ( int );
};

class thread_pool
{
private:
    std::condition_variable handlers;
    std::mutex work_mtx, queue_mtx;
    std::unique_lock<std::mutex> work_lck;
    std::queue<std::function<void()>> postponed;
    std::queue<std::thread> threads;
    std::atomic<int> stop_flag;
public:
    thread_pool( int thread_num );
    ~thread_pool();
    void run();
    void push( std::function<void()> );
};
