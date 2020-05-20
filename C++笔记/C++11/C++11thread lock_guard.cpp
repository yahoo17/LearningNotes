//#include <thread>
//#include <mutex>
//#include <vector>
//#include <atomic>
//using namespace std;
//
//class A
//{
//private:
//	mutex mutexVariable;
//	mutex mutexVariable2;
//	int i = 0;
//	int hhh = 80;
//public:
//
//	void thread1()
//	{
//
//		for (i = 0; i < 10; i++)
//		{
//			lock_guard<mutex> mylock(mutexVariable);
//			hhh++;
//			printf("thread 1 正在执行 %d\n", hhh);
//
//		}
//
//	}
//	void thread2(int a)
//	{
//
//
//		for (i = 0; i < 10; i++)
//		{
//			lock_guard<mutex> mylock(mutexVariable2);
//			hhh++;
//			printf("thread 2 正在%d执行 %d\n", a, hhh);
//
//		}
//
//
//	}
//};
//
//int main()
//{
//	A a;
//	thread t1(&A::thread1,&a);
//	thread t2(&A::thread1,&a);
//	t1.join();
//	if (t2.joinable())
//	{
//		t2.join();
//	}
//	
//	
//
//}