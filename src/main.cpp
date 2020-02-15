//
// Created by wex on 2/15/20.
//

#include <cstdio>

#include <utility/logger.hpp>

int main() {
    Logger logger;

    LOG( logger, Logger::Level::Info, "Hello world" );

    return 0;
}
