set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(example
    PRIVATE
    "${DIR}/main.h"
    "${DIR}/gamecamera.h"
    "${DIR}/systems.h"
    "${DIR}/blocksystem.h"
    "${DIR}/simplex.h"
)
target_include_directories(example PRIVATE "${example_SOURCE_DIR}/include")
