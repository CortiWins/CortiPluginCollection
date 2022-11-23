namespace Log
{

std::fstream datei;
std::string filename = "d:\\debug.txt";

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string CurrentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

// F�gt der DebugDatei eine Zeile hinzu.
void LogLine(std::string line)
{
    datei << line << std::endl;
}

// F�gt der DebugDatei eine information �ber einen Raum hinzu.
void LogValue(std::string text, int value)
{
    std::stringstream streamStr;
    streamStr << text << ": " << value;
    LogLine(streamStr.str());
}

// F�gt der DebugDatei eine information �ber einen Raum hinzu.
void LogValue(std::string text, bool value)
{
    std::stringstream streamStr;
    streamStr << text << ": " << value;
    LogLine(streamStr.str());
}

// L�scht vorhandene Debugdatei und erstellt eine neue
void NewLog()
{

    // DeleteFile("d:\\debug.txt");
    datei.open(filename.c_str(), std::ios::out | std::ios::app );
    LogLine("NEW CORTIATBSPEED LOG ENTRY:");
    LogLine(CurrentDateTime());
}

void LogClose()
{
    datei.close();
}


}
