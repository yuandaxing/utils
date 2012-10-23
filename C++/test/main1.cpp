//
//  main.cpp
//  thread_test
//
//  Created by 肖 博 on 12-3-31.
//  Copyright (c) 2012年 华中科技大学. All rights reserved.
//

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <future>
#include <utility>

int twoTimes(int x) { 
    std::this_thread::sleep_for(std::chrono::seconds(5));
    return x << 2 ; 
}

void test_mutex_guarded(std::mutex& m) {
    
    //lock guard is exception safe
    // basically the same as follow
    //    try {
    //        m.lock()
    //        do something here...
    //    } catch (...) {
    //        deal with exceptions
    //    }
    //    finally { /*if there were finally*/
    //        m.unlock();
    //    }
    std::lock_guard<std::mutex> gaurd(m);

    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "thread id: " << std::this_thread::get_id() << std::endl;

}

int main(int argc, const char * argv[])
{

    // demostrate future
    std::vector<std::future<int> > fv;
    for (int i = 0; i < 5; ++i) {
        // demonstrate async launch
        fv.push_back(std::async(std::launch::async, twoTimes, i));
    }
    
    for (int i = 0; i < 5; ++i) {
            std::cout << fv.at(i).get() << std::endl;
    }
    
    // force serial execution
    std::mutex m;
    
    // launch 4 threads
    std::thread t1(test_mutex_guarded, std::ref(m));
    std::thread t2(test_mutex_guarded, std::ref(m));
    std::thread t3(test_mutex_guarded, std::ref(m));
    std::thread t4(test_mutex_guarded, std::ref(m));
    
    // join
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    
    std::cout << "Hello, World!\n";
    return 0;
}
