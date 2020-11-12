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
#include "thread.h"

using namespace std;

atomic_bool g_run_flag(false);
void print()
{
    std::this_thread::sleep_for(std::chrono::seconds(1/10));
    while(g_run_flag)
    {
        cout << __func__ << " " << __LINE__ << " " << myTime::getTimeString() << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    cout << "... print ..." << endl;
}
void Seconds12()
{
    std::this_thread::sleep_for(std::chrono::seconds(1/24));
    while(g_run_flag)
    {
        cout << __func__ << " " << __LINE__ << " " << myTime::getTimeString() << endl;
        std::this_thread::sleep_for(std::chrono::seconds(12));
    }

    cout << "... 12 ..." << endl;
}

void Seconds4()
{
    std::this_thread::sleep_for(std::chrono::seconds(1/4));
    thread th(print);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    while(g_run_flag)
    {
        cout << __func__ << " " << __LINE__ << " " << myTime::getTimeString() << endl;
        std::this_thread::sleep_for(std::chrono::seconds(4));
    }

    cout << "... 4 ..." << endl;
    if(th.joinable())
    {
        th.join();
        cout << " join .... " << endl;
    }
    
    cout << "... 4 exit ..." << endl;
}

void Seconds1()
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    while(g_run_flag)
    {
        cout << __func__ << " " << __LINE__ << " " << myTime::getTimeString() << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    cout << "... 1 ..." << endl;
}

void PorcQuit(int sig)
{
    g_run_flag = false;
    std::cout << "Signal " << sig << " ...Quit!" << std::endl;
}

int main()
{
    signal(SIGTERM, PorcQuit);
    signal(SIGINT, PorcQuit);
#ifdef WIN32
    signal(SIGBREAK, PorcQuit);
#endif 

    g_run_flag = true;

    thread th1(Seconds1);
    thread th4(Seconds4);
    thread th12(Seconds12);

    MyThread thdMy;
    thdMy.Start();

    std::this_thread::sleep_for(std::chrono::seconds(1));
    while(g_run_flag)
    {
        cout << __func__ << " " << __LINE__ << " " << myTime::getTimeString() << endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    thdMy.Stop();

    if(th1.joinable())
        th1.join();

    if(th4.joinable())
        th4.join();

    if(th12.joinable())
        th12.join();

    return 0;
}

