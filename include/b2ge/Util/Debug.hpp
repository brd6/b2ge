//
// Created by brd6 on 03/02/17.
//

#ifndef _Debug_H_
# define _Debug_H_

#include <iostream>
#include <sstream>
#include "Singleton.hpp"

namespace b2ge
{
  class Debug :
   public Singleton<Debug>
  {
   public:
    enum class DebugType
    {
      Error,
      Warning,
      Info
    };

   private:
    DebugType mType;
    static std::ostream *mOs;
    std::stringstream mSs;
    std::string currentPrefix;

   public:
    static void init(Debug::DebugType type, std::ostream &os = std::cerr);

    Debug &setType(DebugType type);

    template <typename TPrintable>
    Debug &operator<<(TPrintable const &obj)
    {
      log(obj);
      return *this;
    }

    Debug &operator <<(std::ostream& (*os)(std::ostream&))
    {
#if DEBUG
      *mOs << getCurrentDateTime() << " " << currentPrefix << mSs.str() << std::endl;

      mType = Debug::DebugType::Info;
      mSs.str("");
#endif
      return *this;
    }
    template <typename TPrintable>
    Debug &log(TPrintable const &obj)
    {
      return log(obj, mType);
    }

    template <typename TPrintable>
    Debug &logWarning(TPrintable const &obj)
    {
      writeMessage("[Warning] ", obj);
      return *this;
    }

    template <typename TPrintable>
    Debug &logError(TPrintable const &obj)
    {
      writeMessage("[Error] ", obj);
      return *this;
    }

    template <typename TPrintable>
    Debug &logInfo(TPrintable const &obj)
    {
      writeMessage("[Info] ", obj);
      return *this;
    }

    explicit Debug(DebugType type = DebugType::Info);

   private:
    template <typename TPrintable>
    Debug &log(TPrintable const &obj, DebugType type)
    {
      switch (type)
	{
	  case DebugType::Error :
	    Debug::logError(obj);
	  break;
	  case DebugType::Warning:
	    Debug::logWarning(obj);
	  break;
	  default:
	    logInfo(obj);
	  break;
	}
      return *this;
    }

    std::string getCurrentDateTime();


    template <typename TPrintable>
    void writeMessage(std::string const &prefix, TPrintable const &obj)
    {
#if DEBUG
      currentPrefix = prefix;
      mSs << obj;
#else
      (void)obj;
	(void)prefix;
#endif // DEBUG
    }
  };
}

namespace b2ge
{
  #define LOG Debug::getInstance()
  #define LOG_ERR Debug::getInstance().setType(b2ge::Debug::DebugType::Error)
  #define LOG_WARN Debug::getInstance().setType(b2ge::Debug::DebugType::Warning)
  #define LOG_INFO Debug::getInstance().setType(b2ge::Debug::DebugType::Info)
}

#endif /* !_Debug_H_ */