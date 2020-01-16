set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(example
    PRIVATE
    "${DIR}/gamecamera.h"
    "${DIR}/systems.h"
    "${DIR}/blocksystem.h"
    "${DIR}/simplexsystem.h"
    "${DIR}/simplexcomponent.h"
)
target_include_directories(example PRIVATE "${example_SOURCE_DIR}/include")
