//
// Created by brd6 on 03/02/17.
//

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <string>

namespace b2ge
{
  class Debug
  {
   public:
    enum DebugType
    {
      Error,
      Warning,
      Info
    };

    static void log(std::string const &message, DebugType type = DebugType::Info);

    static void logWarning(std::string const &message);

    static void logError(std::string const &message);

   private:
    static void writeMessage(std::string const &message, DebugType type);

    static void writeMessageInColor(std::string const &message, DebugType type);
  };
}

#endif //_DEBUG_H_
