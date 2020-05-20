//// this_thread::yield example
//#include <iostream>       // std::cout
//#include <thread>         // std::thread, std::this_thread::yield
//#include <atomic>         // std::atomic
//#include <vector>
//using namespace std;
//atomic<bool> ready=false;
//atomic_flag winner = ATOMIC_FLAG_INIT;
//void count1m(int id) {
//	while (!ready)
//	{
//		this_thread::yield();
//	}
//	for (int i = 0; i < 100000; i++)
//	{
//
//	}
//	if (!winner.test_and_set())
//	{
//		printf("选手%d获得了胜利\n", id);
//	}
//
//}
//
//int main()
//{
//	vector<thread> vec;
//	for(int i=0;i<100;i++)
//		vec.push_back(thread(count1m, i));
//	ready = true;
//	for (int i = 0; i < 100; i++)
//		vec[i].join();
//	return 0;
//  
//}