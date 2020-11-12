#pragma once
#ifndef MYTIME_H
#define MYTIME_H

#include <time.h>
#include <string>
#include <chrono>
#include <sstream>
#include <iomanip>

#ifdef _WIN32
#include <windows.h>
#pragma warning(disable:4996)// 加上可去掉unsafe,使用localtime_s的编译报错  
#else
#include <sys/time.h>
#endif

const std::string c_strDefaultFormat = "%Y-%m-%d %H:%M:%S";
const std::string c_str_Format = "%Y_%m_%d_%H_%M_%S";
const std::string c_strYmdFormat = "%Y-%m-%d";
const std::string c_strHMSFormat = "%H:%M:%S";

const std::string c_strSysFormat = "%04ld-%02ld-%02ld %02ld:%02ld:%02ld.%03ld";
const std::string c_strSys_Format = "%04ld_%02ld_%02ld_%02ld_%02ld_%02ld.%03ld";

class myTime
{
public:
    // 按格式获取当前时间,默认Y-m-d H:M:S
    static std::string getCurrentTime(const std::string& sFormat = c_strDefaultFormat)
    {
        time_t timep;
        time(&timep);
        char tmp[64];
        strftime(tmp, sizeof(tmp), sFormat.c_str(), localtime(&timep));
        return tmp;
    }

    // 获取指定时间,默认当前时间Y-m-d H:M:S,offset为偏移数据以分钟为单位,向后三个小时 offset = 60*3,向前2小时,offset = -2*60
    static std::string getCustomTime(int offset = 0, const std::string& sFormat = c_strDefaultFormat) // offset + 向后偏移 - 向前偏移 以分钟数为单位
    {
        time_t timep;
        time(&timep);
        char tmp[64];
        timep += (1 * 60 * offset);
        strftime(tmp, sizeof(tmp), sFormat.c_str(), localtime(&timep));
        return tmp;
    }

    // 获取指定时间,默认当前时间Y-m-d H:0:0,offset为偏移数据以分钟为单位,向后三个小时 offset = 60*3,向前2小时,offset = -2*60
    static std::string getCustomDateTime(int offset = 0, const std::string& sFormat = c_strDefaultFormat) // offset + 向后偏移 - 向前偏移 以分钟数为单位
    {
        time_t timep;
        time(&timep);
        char tmp[64];
        timep += (1 * 60 * offset);
        tm* tms = localtime(&timep);
        tms->tm_min = 0;
        tms->tm_sec = 0;
        strftime(tmp, sizeof(tmp), sFormat.c_str(), tms);
        return tmp;
    }

    // 获取time_t
    static time_t getTime_t()
    {
        time_t timep;
        time(&timep);
        return timep;
    }

    // 获取之前一个小时的时间
    static std::string getLastHourTime(const std::string& sFormat = c_strDefaultFormat)
    {
        time_t timep;
        time(&timep);
        char tmp[64];
        timep -= 3600; // 当前时间减去3600s
        strftime(tmp, sizeof(tmp), sFormat.c_str(), localtime(&timep));
        return tmp;
    }

    // 获取年月日
    static std::string getYearMonthDay(const std::string& sFormat = c_strYmdFormat)
    {
        time_t timep;
        time(&timep);
        char tmp[64];
        strftime(tmp, sizeof(tmp), sFormat.c_str(), localtime(&timep));
        return tmp;
    }

    // 获取时分秒
    static std::string getHourMinSec(const std::string& sFormat = c_strHMSFormat)
    {
        time_t timep;
        time(&timep);
        char tmp[64];
        strftime(tmp, sizeof(tmp), sFormat.c_str(), localtime(&timep));
        return tmp;
    }

    // 获取时间的 tm* 结构体
    static tm* getTm()
    {
        time_t timep;
        time(&timep);
        return localtime(&timep);
    }

    // 获取年
    static int getYear()
    {
        time_t timep;
        time(&timep);
        tm* tmp = localtime(&timep);
        return tmp->tm_year + 1900;
    }

    // 获取月
    static int getMonth()
    {
        time_t timep;
        time(&timep);
        tm* tmp = localtime(&timep);
        return tmp->tm_mon;
    }

    // 获取日
    static int getDay()
    {
        time_t timep;
        time(&timep);
        tm* tmp = localtime(&timep);
        return tmp->tm_mday;
    }

    // 获取指定天数
    static int getCustomDay(int offset = 0)  // offset + 向后偏移 - 向前偏移 以天数为单位
    {
        time_t timep;
        time(&timep);
        timep += (1 * 60 * 60 * 24 * offset);// 天 * offset
        tm* tmp = localtime(&timep);
        return tmp->tm_mday;
    }

    // 获取前一天
    static int getLastDay()
    {
        time_t timep;
        time(&timep);
        timep -= (1 * 60 * 60 * 24);// 秒
        tm* tmp = localtime(&timep);
        return tmp->tm_mday;
    }

    // 获取当前小时
    static int getHour()
    {
        time_t timep;
        time(&timep);
        tm* tmp = localtime(&timep);
        return tmp->tm_hour;
    }

    // 获取指定小时数
    static int getCustomHour(int offset = 0)  // offset + 向后偏移 - 向前偏移 以分钟数为单位
    {
        time_t timep;
        time(&timep);
        timep += (1 * 60 * offset);// 秒
        tm* tmp = localtime(&timep);
        return tmp->tm_hour;
    }

    // 获取之前一小时数
    static int getLastHour()
    {
        time_t timep;
        time(&timep);
        timep -= (1 * 60 * 60);// 秒
        tm* tmp = localtime(&timep);
        return tmp->tm_hour;
    }

    // 获取分钟数
    static int getMinute()
    {
        time_t timep;
        time(&timep);
        tm* tmp = localtime(&timep);
        return tmp->tm_min;
    }

    //获取前一分钟
    static int getLastMin()
    {
        time_t timep;
        time(&timep);
        timep -= (1 * 60);// 秒
        tm* tmp = localtime(&timep);
        return tmp->tm_min;
    }

    // 获取系统时间
    static std::string getSystemTimeString(const std::string& sFormat = c_strSysFormat)
    {
        char timeChar[128] = { 0 };
#ifdef _WIN32
        SYSTEMTIME sysTime;
        GetLocalTime(&sysTime);
        sprintf(timeChar, sFormat.c_str(),
            sysTime.wYear,
            sysTime.wMonth,
            sysTime.wDay,
            sysTime.wHour,
            sysTime.wMinute,
            sysTime.wSecond,
            sysTime.wMilliseconds);
#else
        struct tm* pTempTm;
        struct timeval time;

        gettimeofday(&time, nullptr);
        pTempTm = localtime(&time.tv_sec);
        if (nullptr != pTempTm)
        {
            snprintf(timeChar, 128, sFormat.c_str(),
                pTempTm->tm_year + 1900,
                pTempTm->tm_mon + 1,
                pTempTm->tm_mday,
                pTempTm->tm_hour,
                pTempTm->tm_min,
                pTempTm->tm_sec,
                time.tv_usec / 1000);
        }
#endif

        return timeChar;
    }

    // 时间字符串(如：2020-06-06 14:40:31.015)
    static std::string getTimeString(const std::string& sFormat = c_strDefaultFormat, bool bLocal = true, bool bIncludeMS = true)
    {
        auto tNow = std::chrono::system_clock::now();
        auto tSeconds = std::chrono::duration_cast<std::chrono::seconds>(tNow.time_since_epoch());
        auto secNow = tSeconds.count();

        tm tmNow;

        if (bLocal)
        {
#ifdef _WIN32
            localtime_s(&tmNow, &secNow);
#else
            localtime_r(&secNow, &tmNow);
#endif
        }
        else
        {
#ifdef _WIN32
            gmtime_s(&tmNow, &secNow);
#else
            gmtime_r(&secNow, &tmNow);
#endif
        }

        std::ostringstream oss;
        oss << std::put_time(&tmNow, sFormat.c_str());
        if (bIncludeMS)
        {
            auto tMilli = std::chrono::duration_cast<std::chrono::milliseconds>(tNow.time_since_epoch());
            auto ms = tMilli - tSeconds;
            oss << "." << std::setfill('0') << std::setw(3) << ms.count();
        }

        return oss.str();
    }
};

#endif // !MYTIME_H