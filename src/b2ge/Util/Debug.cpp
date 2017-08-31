//
// Created by brd6 on 03/02/17.
//

#include <iostream>

#if WIN32

#include <windows.h>

#endif // WIN32

#include "Util/Debug.hpp"

namespace b2ge
{
  void Debug::log(std::string const &message, DebugType type)
  {
    switch (type)
      {
	case DebugType::Error :
	  Debug::logError(message);
	break;
	case DebugType::Warning:
	  Debug::logWarning(message);
	break;
	default:
	  writeMessage("[Info] " + message, DebugType::Info);
	break;
      }
  }

  void Debug::logWarning(std::string const &message)
  {
    writeMessage("[Warning] " + message, DebugType::Warning);
  }

  void Debug::logError(std::string const &message)
  {
    writeMessage("[Error] " + message, DebugType::Error);
  }

  void Debug::writeMessage(std::string const &message, DebugType type)
  {
#if WIN32
    writeMessageInColor(message, type);
#else
    std::cout << message << std::endl;
#endif // WIN32
  }

  void Debug::writeMessageInColor(std::string const &message, DebugType type)
  {
#if WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorCmp;

    switch (type)
      {
	// foreground + background * 16
	case DebugType::Error:
	  colorCmp = 12 + 0 * 16;
	break;
	case DebugType::Warning:
	  colorCmp = 14 + 0 * 16;
	break;
	case DebugType::Info:
	  colorCmp = 15 + 0 * 16;
	break;
	default:
	  break;
      }
    SetConsoleTextAttribute(hConsole, colorCmp);
    std::cout << message << std::endl;
#endif // WIN32
  }
}