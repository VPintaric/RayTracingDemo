//
// Created by wex on 9/15/19.
//

#ifndef RAYTRACINGDEMO_LOGGER_HPP
#define RAYTRACINGDEMO_LOGGER_HPP

#include <stdarg.h>

#define LOG( logger, level, format, args... ) \
    logger.Log( level, "%s:%d:%s: " format "\n", __FILE__, __LINE__, __func__, ##args )

class Logger {
public:

    enum Level {
        Critical = 0,
        Error = 10,
        Warning = 20,
        Info = 30,
        Debug = 40,
    };

    explicit Logger( Level level = Level::Info );

    virtual ~Logger();

    void Log( Level level, const char *format, ... ) const;

private:

    Level level_;
};

#endif //RAYTRACINGDEMO_LOGGER_HPP
