//#include <thread>
//#include <atomic>
//#include <mutex>
//#include <functional>
//using namespace std;
//class FizzBuzz {
//private:
//    int n;
//    atomic<int> count;
//public:
//    FizzBuzz(int n) :count(1) {
//        this->n = n;
//    }
//
//     printFizz() outputs "fizz".
//    void fizz(function<void()> printFizz) {
//        while (count.load() <= n)
//        {
//            if (count % 3 == 0 && count % 5)
//            {
//                printFizz();
//                count++;
//
//            }
//            this_thread::yield();
//        }
//
//
//
//    }
//
//     printBuzz() outputs "buzz".
//    void buzz(function<void()> printBuzz) {
//        while (count.load() <= n) {
//            if (count % 3 && count % 5 == 0)
//            {
//                printBuzz();
//                count++;
//
//            }
//            this_thread::yield();
//        }
//
//    }
//
//     printFizzBuzz() outputs "fizzbuzz".
//    void fizzbuzz(function<void()> printFizzBuzz) {
//        while (count.load() <= n) {
//            if (count % 3 == 0 && count % 5 == 0)
//            {
//                printFizzBuzz();
//                count++;
//
//            }
//            this_thread::yield();
//        }
//
//    }
//
//     printNumber(x) outputs "x", where x is an integer.
//    void number(function<void(int)> printNumber) {
//        while (count.load() <= n)
//        {
//            if (count % 3 && count % 5)
//            {
//                printNumber(count.load());
//                count++;
//
//            }
//            this_thread::yield();
//        }
//
//    }
//};