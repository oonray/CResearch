#include <iostream>
#include <thread>
#include <mutex>
#include <algorithm>
#include <numeric>
#include <ranges>
#include <vector>

int data = 0;
std::recursive_mutex mute;

void inc_data(){
    mute.lock();
    data++;
    mute.unlock();
}

void threadd(){
    for(int i = 0; i< 10; i++){
        std::cout<< "Starting Thread: " << std::this_thread::get_id() << ", data is " << data << '\n';
        inc_data();
    }
}

int main(){
    std::vector<std::thread> v = {
        std::thread(threadd),
        std::thread(threadd),
        std::thread(threadd),
        std::thread(threadd),
        std::thread(threadd),
        std::thread(threadd),
        std::thread(threadd),
        std::thread(threadd),
        std::thread(threadd),
        std::thread(threadd)
    };

    std::cout << "data is " << data << '\n';
}

