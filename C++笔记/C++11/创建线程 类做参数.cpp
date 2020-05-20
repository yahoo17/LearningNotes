//#include <iostream>
//#include <thread>
//#include <mutex>
//#include <atomic>
//void inc(std::mutex& mutex, int loop, int& counter);
//class A
//{
//public:
//    void print()
//    {
//        printf("a");
//    }
//};
//int main() {
//    std::thread threads[5];
//    std::mutex mutex;
//    int counter = 0;
//
//    for (std::thread& thr : threads) {
//        thr = std::thread(inc, std::ref(mutex), 1000, std::ref(counter));
//    }
//    //std::refҲ��C++11���÷�
//    for (std::thread& thr : threads) {
//        thr.join();
//    }
//    A a;
//    std::thread athread(&A::print, a);
//    athread.join();
//    // �����5000�����inc�е��õ���try_lock����˴����ܻ�<5000
//    std::cout << counter << std::endl;
//
//    return 0;
//}
////: g++ -std=c++11 main.cpp
//void inc(std::mutex& mutex, int loop, int& counter) {
//    for (int i = 0; i < loop; i++) {
//        mutex.lock();
//        ++counter;
//        mutex.unlock();
//    }
//    for (int i = 0; i < loop; i++)
//    {
//        {
//            std::lock_guard<std::mutex> lock(mutex);
//            ++counter;
//        }
//
//    }
//}