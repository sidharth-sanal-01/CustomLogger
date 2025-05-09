 #include "CustomLogger.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <semaphore.h>
#include <fcntl.h>
#include <ctime>

CustomLogger::Logger::Logger()
{
    std::cout << "Logger Initiated.." << std::endl;
    std::cout << "No Custom Path provided..Writing Logs to /home/sidharth/Desktop" << std::endl;
    LogFile.open("/home/sidharth/Desktop/LogFile.txt", std::ios::app);
    if (!LogFile.is_open())
    {
        std::cerr << "Could not open Log File..." << std::endl;
    }
    std::cout << "Log File Ready to write" << std::endl;
}

CustomLogger::Logger::Logger(std::string LogPath)
{
    if (!fs::exists(LogPath))
    {
        std::cerr << "Cannot Open Log File Path, Log File does not exist" << std::endl;
    }
    LogFile.open(LogPath, std::ios::app);
    if (!LogFile.is_open())
    {
        std::cerr << "Could not open Log File.." << std::endl;
    }
    std::cout << "Log File Ready to write" << std::endl;
}

sem_t *CustomLogger::Logger::getNamedMutex()
{
    sem_t *mutex = sem_open(MUTEX_NAME, O_CREAT | O_EXCL, 0666);
    if (mutex == SEM_FAILED)
    {
        if (errno == EEXIST)
        {
            mutex = sem_open(MUTEX_NAME, 0);
        }
        else
        {
            std::cerr << "sem allocation Failed" << std::endl;
        }
    }
    else
    {
        std::cerr << "sem initialization Failed" << std::endl;
    }
    return mutex;
}

int CustomLogger::Logger::writeLog(std::string message, std::string APP_ID)
{
    auto mutex = getNamedMutex();
    if (message == "" || APP_ID == "")
    {
        std::cout << "No information provided in the logs.." << std::endl;
        return -1;
    }
    std::string currentTime = getCurrentTime();
    std::string LogToWrite = "[ " + currentTime + " ]: " + message + APP_ID + "\n";
    try
    {
        sem_wait(mutex);       // waiting for the mutex
        LogFile << LogToWrite; // writing to the file
        sem_post(mutex);       // releasing the mutex
        return 1;
    }
    catch (...)
    {
        std::cerr << "Writing to File Failed" << std::endl;
        return -1;
    }
}

std::string CustomLogger::Logger::getCurrentTime()
{
    auto now = std::chrono::system_clock::now();
    auto now_time = std::chrono::system_clock::to_time_t(now);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&now_time), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
