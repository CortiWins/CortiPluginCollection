

namespace CortiFile
{
// TRACE
// ERROR
// EVENT


#define TRACELINE(stream){ std::ostringstream parameterStream; parameterStream << stream; CortiFile::LogLine("TRACE", parameterStream.str()); }

#define ERRORLINE(stream){ std::ostringstream parameterStream; parameterStream << stream; CortiFile::LogLine("ERROR", parameterStream.str()); }

#define EVENTLINE(stream){ std::ostringstream parameterStream; parameterStream << stream; CortiFile::LogLine("EVENT", parameterStream.str()); }

const std::string GetDateTime(const char* timeFormat )
{
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);

    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime for more information about date/time format
    strftime(buf, sizeof(buf), timeFormat, &tstruct);

    return buf;
}

const std::string GetDateTimeSeconds()
{
    return GetDateTime("%Y.%m.%d-%H:%M:%S");
}

// Zugriff auf Datei.
std::ofstream fileWriter;

void LogLine(std::string category, std::string logline)
{
    fileWriter << GetDateTimeSeconds() << " ["<< category << "] " << logline << std::endl;
}

void Init()
{
    CreateDirectory("CortiEventTrace", NULL);

    std::ostringstream nameStream;
    nameStream << "CortiEventTrace\\CortiEventTrace_" << GetDateTime("%Y.%m.%d-%H.%M.%S") << ".txt";

    fileWriter.open(nameStream.str().c_str(), std::ios::out | std::ios::app);
    LogLine("TRACE","File created.");
}

void Exit()
{
    fileWriter.close();
}

bool IsOpen()
{
    return fileWriter.is_open();
}

}
