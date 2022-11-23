#define _WIN32_WINNT 0x0500

/*
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch"
#pragma GCC diagnostic ignored "-Wshadow"
#pragma GCC diagnostic ignored "-Weffc++"
#pragma GCC diagnostic ignored "-Wunused-variable"
#pragma GCC diagnostic ignored "-Wunused-function"
#pragma GCC diagnostic ignored "-Wconversion-null"
*/
#include <DynRPG/DynRPG.h>
//#pragma GCC diagnostic pop
#include <sstream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#define null NULL
#include "Common/Dialog.cpp"
#include "../AwesomeInnocentiaPlugin/DebugTools/ConsoleLogger.cpp"
#include "../AwesomeInnocentiaPlugin/DebugTools/CortiLog.cpp"
#include "CustomCrit.cpp"

// DynRPG Callbacks
#include "Callbacks//onSystem.cpp"
#include "Callbacks//onBattlerAction.cpp"
#include "Callbacks//onBattlerDrawn.cpp"
#include "Callbacks//onFrame.cpp"
#include "Callbacks//onDrawBattleActionWindow.cpp"
#include "Callbacks//onComment.cpp"
