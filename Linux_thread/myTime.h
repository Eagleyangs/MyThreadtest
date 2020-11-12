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
#pragma warning(disable:4996)// ���Ͽ�ȥ��unsafe,ʹ��localtime_s�ı��뱨��  
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
    // ����ʽ��ȡ��ǰʱ��,Ĭ��Y-m-d H:M:S
    static std::string getCurrentTime(const std::string& sFormat = c_strDefaultFormat)
    {
        time_t timep;
        time(&timep);
        char tmp[64];
        strftime(tmp, sizeof(tmp), sFormat.c_str(), localtime(&timep));
        return tmp;
    }

    // ��ȡָ��ʱ��,Ĭ�ϵ�ǰʱ��Y-m-d H:M:S,offsetΪƫ�������Է���Ϊ��λ,�������Сʱ offset = 60*3,��ǰ2Сʱ,offset = -2*60
    static std::string getCustomTime(int offset = 0, const std::string& sFormat = c_strDefaultFormat) // offset + ���ƫ�� - ��ǰƫ�� �Է�����Ϊ��λ
    {
        time_t timep;
        time(&timep);
        char tmp[64];
        timep += (1 * 60 * offset);
        strftime(tmp, sizeof(tmp), sFormat.c_str(), localtime(&timep));
        return tmp;
    }

    // ��ȡָ��ʱ��,Ĭ�ϵ�ǰʱ��Y-m-d H:0:0,offsetΪƫ�������Է���Ϊ��λ,�������Сʱ offset = 60*3,��ǰ2Сʱ,offset = -2*60
    static std::string getCustomDateTime(int offset = 0, const std::string& sFormat = c_strDefaultFormat) // offset + ���ƫ�� - ��ǰƫ�� �Է�����Ϊ��λ
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

    // ��ȡtime_t
    static time_t getTime_t()
    {
        time_t timep;
        time(&timep);
        return timep;
    }

    // ��ȡ֮ǰһ��Сʱ��ʱ��
    static std::string getLastHourTime(const std::string& sFormat = c_strDefaultFormat)
    {
        time_t timep;
        time(&timep);
        char tmp[64];
        timep -= 3600; // ��ǰʱ���ȥ3600s
        strftime(tmp, sizeof(tmp), sFormat.c_str(), localtime(&timep));
        return tmp;
    }

    // ��ȡ������
    static std::string getYearMonthDay(const std::string& sFormat = c_strYmdFormat)
    {
        time_t timep;
        time(&timep);
        char tmp[64];
        strftime(tmp, sizeof(tmp), sFormat.c_str(), localtime(&timep));
        return tmp;
    }

    // ��ȡʱ����
    static std::string getHourMinSec(const std::string& sFormat = c_strHMSFormat)
    {
        time_t timep;
        time(&timep);
        char tmp[64];
        strftime(tmp, sizeof(tmp), sFormat.c_str(), localtime(&timep));
        return tmp;
    }

    // ��ȡʱ��� tm* �ṹ��
    static tm* getTm()
    {
        time_t timep;
        time(&timep);
        return localtime(&timep);
    }

    // ��ȡ��
    static int getYear()
    {
        time_t timep;
        time(&timep);
        tm* tmp = localtime(&timep);
        return tmp->tm_year + 1900;
    }

    // ��ȡ��
    static int getMonth()
    {
        time_t timep;
        time(&timep);
        tm* tmp = localtime(&timep);
        return tmp->tm_mon;
    }

    // ��ȡ��
    static int getDay()
    {
        time_t timep;
        time(&timep);
        tm* tmp = localtime(&timep);
        return tmp->tm_mday;
    }

    // ��ȡָ������
    static int getCustomDay(int offset = 0)  // offset + ���ƫ�� - ��ǰƫ�� ������Ϊ��λ
    {
        time_t timep;
        time(&timep);
        timep += (1 * 60 * 60 * 24 * offset);// �� * offset
        tm* tmp = localtime(&timep);
        return tmp->tm_mday;
    }

    // ��ȡǰһ��
    static int getLastDay()
    {
        time_t timep;
        time(&timep);
        timep -= (1 * 60 * 60 * 24);// ��
        tm* tmp = localtime(&timep);
        return tmp->tm_mday;
    }

    // ��ȡ��ǰСʱ
    static int getHour()
    {
        time_t timep;
        time(&timep);
        tm* tmp = localtime(&timep);
        return tmp->tm_hour;
    }

    // ��ȡָ��Сʱ��
    static int getCustomHour(int offset = 0)  // offset + ���ƫ�� - ��ǰƫ�� �Է�����Ϊ��λ
    {
        time_t timep;
        time(&timep);
        timep += (1 * 60 * offset);// ��
        tm* tmp = localtime(&timep);
        return tmp->tm_hour;
    }

    // ��ȡ֮ǰһСʱ��
    static int getLastHour()
    {
        time_t timep;
        time(&timep);
        timep -= (1 * 60 * 60);// ��
        tm* tmp = localtime(&timep);
        return tmp->tm_hour;
    }

    // ��ȡ������
    static int getMinute()
    {
        time_t timep;
        time(&timep);
        tm* tmp = localtime(&timep);
        return tmp->tm_min;
    }

    //��ȡǰһ����
    static int getLastMin()
    {
        time_t timep;
        time(&timep);
        timep -= (1 * 60);// ��
        tm* tmp = localtime(&timep);
        return tmp->tm_min;
    }

    // ��ȡϵͳʱ��
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

    // ʱ���ַ���(�磺2020-06-06 14:40:31.015)
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