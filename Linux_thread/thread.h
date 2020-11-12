#pragma once

#include <iostream>
#include <thread>
#include <string>
#include <limits>
#include <climits>
#include <atomic>
#include <chrono>
#include <future>
#include <functional>
#include <signal.h>
#include <locale.h>

#include "myTime.h"

using namespace std;

class MyThread
{
public:
	MyThread():m_Running(false)
    {
        std::lock_guard<std::mutex> lock(m_countMutex);
        m_count = 0;
    }
	~MyThread(){}
	
	void Start();
	void Stop();
private:
	void Test();
	void TestStr(const string& str);
	void TestInt(int n);
private:
	bool   m_Running;
	thread m_thdMy;
	
	mutex	m_countMutex;
	size_t  m_count;
};

void MyThread::Start()
{
	if(m_Running)
		return;

	m_Running = true;
	m_thdMy = thread(&MyThread::Test, this);
}

void MyThread::Stop()
{
	if(!m_Running)
		return;

	m_Running = false;
	if(m_thdMy.joinable())
		m_thdMy.join();
}

void MyThread::Test()
{
	thread th1(&MyThread::TestStr, std::ref(*this), "test");
	while(m_Running)
	{
		cout << __func__ << " " << __LINE__ << " " << myTime::getTimeString() << endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
		{
			std::lock_guard<std::mutex>	lock(m_countMutex);
			m_count++;
			thread th(&MyThread::TestInt, std::ref(*this), m_count);
			th.join();
		}

	}
	if(th1.joinable())
		th1.join();
}

void MyThread::TestStr(const string& str)
{
	cout << __func__ << " " << __LINE__ << " " << myTime::getTimeString() << " str:" << str << endl;
}

void MyThread::TestInt(int n)
{
	cout << __func__ << " " << __LINE__ << " " << myTime::getTimeString() << " count:" << n << endl;
}
