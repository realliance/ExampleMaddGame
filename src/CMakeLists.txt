set(DIR ${CMAKE_CURRENT_LIST_DIR})
target_sources(example
    PRIVATE
        "${DIR}/main.cpp"
        "${DIR}/gamecamera.cpp"
        "${DIR}/blocksystem.cpp"
        "${DIR}/simplexsystem.cpp"
)
