//
// Created by wex on 9/15/19.
//

#include <utility/logger.hpp>
#include <cstdio>
#include <cassert>

// __PUBLIC__

Logger::Logger( const Logger::Level level ) : level_( level ) {

}

Logger::~Logger() = default;

void Logger::Log( const Logger::Level level, const char *format, ... ) const {
    if ( level <= level_ ) {
        va_list args;
        va_start( args, format );
        if ( level <= Warning ) {
            std::vfprintf( stderr, format, args );
            if ( level == Critical ) {
                assert( false );
            }
        } else {
            std::vfprintf( stdout, format, args );
        }

        va_end( args );
    }
}