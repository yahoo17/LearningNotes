//#include <iostream>
//#include <condition_variable>
//#include <thread>
//#include <vector>
//#include <chrono>
//using namespace std;
//int i = 0;
//mutex m1;
//condition_variable cv;
//void wait()
//{
//	{
//		unique_lock<mutex> waitul(m1);
//		cout<<"waiting \n";
//		cv.wait(waitul, [] {return i == 1; });
//		printf(" finish wait\n");
//	}
//
//}
//void Notify()
//{
//	this_thread::sleep_for(chrono::seconds(1));
//	{
//		lock_guard<mutex> lk(m1);
//		
//		//
//		printf("notify once\n");
//		
//		
//	}
//	cv.notify_all();
//	this_thread::sleep_for(chrono::seconds(1));
//	{
//		lock_guard<mutex> lk(m1);
//		i = 1;
//		
//		
//		printf("notify second\n");
//		
//	}
//	cv.notify_all();
//}
//int main()
//{
//	
//	vector<thread> threadpool;
//	for (int i=0; i < 3; i++)
//	{
//		threadpool.push_back(thread(wait));
//	}
//	threadpool.push_back(thread(Notify));
//	for (int i = 0; i < 4; i++)
//	{
//		threadpool[i].join();
//	}
//}