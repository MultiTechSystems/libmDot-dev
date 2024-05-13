#ifndef MTSLOG_H
#define MTSLOG_H

#include <string>

inline std::string className(const std::string& prettyFunction)
{
    size_t colons = prettyFunction.find_last_of("::");
    if (colons == std::string::npos)
        return std::string("");
    size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;
    size_t end = colons - begin;

    return std::string(prettyFunction.substr(begin,end));
}

#define __CLASSNAME__ className(__PRETTY_FUNCTION__).c_str()

#ifdef MTS_TIMESTAMP_LOG
#define __LOG__(logLevel, format, ...)                                   \
    mts::MTSLog::printMessage(logLevel, "%s| [%s] " format "\r\n", \
                              mts::MTSLog::getTime().c_str(), mts::MTSLog::getLogLevelString(logLevel), ##__VA_ARGS__)
#else
#define __LOG__(logLevel, format, ...)                                   \
    mts::MTSLog::printMessage(logLevel, "[%s] " format "\r\n", mts::MTSLog::getLogLevelString(logLevel), ##__VA_ARGS__)
#endif

#ifdef MTS_DEBUG
#define logFatal(format, ...) \
    mts::MTSLog::printMessage(mts::MTSLog::FATAL_LEVEL, "%s:%s:%d| [%s] " format "\r\n", __CLASSNAME__, __func__, __LINE__, mts::MTSLog::FATAL_LABEL, ##__VA_ARGS__)
#define logError(format, ...) \
    mts::MTSLog::printMessage(mts::MTSLog::ERROR_LEVEL, "%s:%s:%d| [%s] " format "\r\n", __CLASSNAME__, __func__, __LINE__, mts::MTSLog::ERROR_LABEL, ##__VA_ARGS__)
#define logWarning(format, ...) \
    mts::MTSLog::printMessage(mts::MTSLog::WARNING_LEVEL, "%s:%s:%d| [%s] " format "\r\n", __CLASSNAME__, __func__, __LINE__, mts::MTSLog::WARNING_LABEL, ##__VA_ARGS__)
#define logInfo(format, ...) \
    mts::MTSLog::printMessage(mts::MTSLog::INFO_LEVEL, "%s:%s:%d| [%s] " format "\r\n", __CLASSNAME__, __func__, __LINE__, mts::MTSLog::INFO_LABEL, ##__VA_ARGS__)
#define logDebug(format, ...) \
    mts::MTSLog::printMessage(mts::MTSLog::DEBUG_LEVEL, "%s:%s:%d| [%s] " format "\r\n", __CLASSNAME__, __func__, __LINE__, mts::MTSLog::DEBUG_LABEL, ##__VA_ARGS__)
#define logTrace(format, ...) \
    mts::MTSLog::printMessage(mts::MTSLog::TRACE_LEVEL, "%s:%s:%d| [%s] " format "\r\n", __CLASSNAME__, __func__, __LINE__, mts::MTSLog::TRACE_LABEL, ##__VA_ARGS__)
#elif defined(MTS_DEBUG_OFF)
#define logFatal(...)
#define logError(...)
#define logWarning(...)
#define logInfo(...)
#define logDebug(...)
#define logTrace(...)
#else
#define logFatal(format, ...) \
    __LOG__(mts::MTSLog::FATAL_LEVEL, format, ##__VA_ARGS__)
#define logError(format, ...) \
    __LOG__(mts::MTSLog::ERROR_LEVEL, format, ##__VA_ARGS__)
#define logWarning(format, ...) \
    __LOG__(mts::MTSLog::WARNING_LEVEL, format, ##__VA_ARGS__)
#define logInfo(format, ...) \
    __LOG__(mts::MTSLog::INFO_LEVEL, format, ##__VA_ARGS__)
#ifndef NDEBUG
#define logDebug(format, ...) \
    __LOG__(mts::MTSLog::DEBUG_LEVEL, format, ##__VA_ARGS__)
#define logTrace(format, ...) \
    __LOG__(mts::MTSLog::TRACE_LEVEL, format, ##__VA_ARGS__)
#else
#define logDebug(...)
#define logTrace(...)
#endif  // NDEBUG
#endif  // MTS_DEBUG

namespace mts {

class MTSLog
{
public:

    /** Enum of log levels.
     */
    enum logLevel {
        NONE_LEVEL = 0,
        FATAL_LEVEL = 1,
        ERROR_LEVEL = 2,
        WARNING_LEVEL = 3,
        INFO_LEVEL = 4,
        DEBUG_LEVEL = 5,
        TRACE_LEVEL = 6
    };

    /** Print log message.
     */
    static void printMessage(int level, const char* format, ...);

    /** Determine if the given level is currently printable.
     */
    static bool printable(int level);

    /** Set log level
     * Messages with lower priority than the current level will not be printed.
     * If the level is set to NONE, no messages will print.
     */
    static void setLogLevel(int level);

    /** Get the current log level.
     */
    static int getLogLevel();

    /** Get string representation of the current log level.
     */
    static const char* getLogLevelString();
    static const char* getLogLevelString(int level);

    /** Get a formatted time string as HH:MM:SS
     */
    static std::string getTime();

    static const char* NONE_LABEL;
    static const char* FATAL_LABEL;
    static const char* ERROR_LABEL;
    static const char* WARNING_LABEL;
    static const char* INFO_LABEL;
    static const char* DEBUG_LABEL;
    static const char* TRACE_LABEL;

private:

    /** Constructor
     */
    MTSLog();

    static int currentLevel;

};

}

#endif
