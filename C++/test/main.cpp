//
//  main.cpp
//  smartptr_test
//
//  Created by 肖 博 on 21/3/12.
//  Copyright (c) 2012 华中科技大学. All rights reserved.
//

// clang -std=c++0x -stdlib=libc++ main.cpp
// gcc -std=c++0x main.cpp (gcc version above 4.6, 4.7 is better)


// demostrate smart_ptr(s) and bind/function as well as lambda

#include <iostream>
#include <memory> // std::shared_ptr std::weak_ptr std::unique_ptr, new in C++11
#include <utility> // for std::bind
#include <functional> // for std::function
#include <vector>
using namespace std;

struct test_unique_ptr_class {
    test_unique_ptr_class(){std::cout << "constructor invoked" <<std::endl;}
    ~test_unique_ptr_class() {
        std::cout << "test_unique_ptr_class destructor invoked" << std::endl;
    }
};

struct test_class :public std::enable_shared_from_this<test_class> {
    
    // unique_ptr garuantees varible lives within scopes. There is no need to 
    // care about its lifecyle management, it is even exception safe.
    // unique_ptr simplifies pimpl idiom.
    std::unique_ptr<test_unique_ptr_class> test_unique_ptr;

    test_class():test_unique_ptr(new test_unique_ptr_class){}
    void function1(int param_a, float param_b) {
        std::cout << param_a << "," << param_b << std::endl;
    }
    
    ~test_class(){
        std::cout <<"test_class destructor invoked\n";
    }
};

typedef std::shared_ptr<test_class> test_class_shared_ptr;

void apply_func1_shared_obj(test_class_shared_ptr obj_ptr,int a,float b) {
    obj_ptr->function1(a, b);
}

int main(int argc, const char * argv[])
{
    
    test_class tcobj;
    std::vector<test_unique_ptr_class> v;
    test_unique_ptr_class tupc;
    v.push_back(tupc);
    auto&& rrtupc = tupc;
    v.push_back(rrtupc);
    v.emplace_back();
    // shared_ptr manage tcobj's lifecycle.
    // No need to care about deleting pointers.
    test_class_shared_ptr ptcobj = 
     std::make_shared<test_class>(/*constructor params if any*/);
    
    apply_func1_shared_obj(ptcobj, 1, 1.0f);
    
    // weak_ptr hold a weak reference to the object ptcobj points to.
    std::weak_ptr<test_class> wptcobj = ptcobj;
    
    // weak_ptr should not be expired.
    std::cout << "weak_ptr expired: " << wptcobj.expired() << std::endl;
    
    // lock weak_ptr to hold a strong reference and then use it.
    auto strong_ref = wptcobj.lock();

    try {
        // test for null
        if (!strong_ref) {
            // should not happen.
            throw;
        }
        strong_ref->function1(2, 2.0f);
        
    } catch (...) {
        std::cout << "should not reach here, but anyway, no memory leaks." 
                  << std::endl;
    }

    
    
    // bind/function examples, much better than inheritance and those shitty
    // WTF design patterns.
    
    // bind all params
    std::function<void()> f1 = std::bind(&test_class::function1, 
                                                 std::ref(tcobj), 
                                                 5,
                                                 10.0f);
    
    // don't bind any params, only bind obj to on which to invoke method 
    // and the method to invoke
    std::function<void(int, float)> f2 = std::bind(&test_class::function1,
                                                std::ref(tcobj), 
                                                std::placeholders::_1,
                                                std::placeholders::_2);
    
    // demonstrate auto type deduction
    auto test_class_ptr = std::make_shared<test_class>();
    //std::shared_ptr<test_class>(new test_class) is also correct, 
    // but the above code makes it more like a "factory".
    
    // demonstrate partially applied functions, 
    // very common in functional programming languages.
    auto g = std::bind(&test_class::function1, 
                       test_class_ptr, 
                       3,// partially aplly the first parameter 
                       std::placeholders::_1);// apply this parameter later
    
    //demonstrate lambda
    
    // capture in-scope variables into closure by assignment by default
    // so that we can hold a strong reference to the underlying object.
    //    auto lambda = ([=](int a, float b) {
    //        test_class_ptr->function1(a, b);
    //    });
    //above code causes clang seg fault due to a compiler bug.

    f1();
    f2(2,3.0);
    g(67676.0);
    //    lambda(123,123.0f);

    return 0;
}

