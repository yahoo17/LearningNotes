//#include <mutex>
//#include <thread>
//#include <iostream>
//#include <atomic>
//using namespace std;
//
//atomic<bool> ready = false;
//atomic_flag flag;
//void beginRun(int id)
//{
//	while (!ready)
//	{
//		this_thread::yield();
//	}
//	for (int i = 0; i < 10000; i++)
//		;
//	if(!flag.test_and_set())
//		printf(" %d ÊÇ¹Ú¾ü\n", id);
//
//		
//	
//}
//int main()
//{
//
//	thread threadArray[100];
//	for (int i = 0; i < 100; i++)
//	{
//		threadArray[i] = thread(beginRun,i);
//
//	}
//	ready.store(true);
//	for (int i = 0; i < 100; i++)
//		threadArray[i].join();
//
//}