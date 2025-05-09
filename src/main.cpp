#include <iostream>
#include "CustomLogger.hpp"
#include <memory>

int main()
{
    std::unique_ptr<CustomLogger::Logger> logger = std::make_unique<CustomLogger::Logger>();
    logger->writeLog("My First Log..", "LNX");
}