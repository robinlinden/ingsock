include(FetchContent)

FetchContent_Declare(Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG b3fb4b9feafcd8d91c5cb510a4775143fdbef02f # v3.11.0
)
FetchContent_MakeAvailable(Catch2)

FetchContent_GetProperties(Catch2
    SOURCE_DIR Catch2_SOURCE_DIR
)

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/contrib)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} PARENT_SCOPE)
