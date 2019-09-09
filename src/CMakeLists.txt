set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(example
    PRIVATE
        "${DIR}/main.cpp"
        "${DIR}/cube.cpp"
        "${DIR}/gamecamera.cpp"
        "${DIR}/plane.cpp"
)
