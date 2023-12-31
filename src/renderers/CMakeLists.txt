set(SDL2_DIR ${LIBS_DIR}/SDL2/cmake)

find_package(SDL2 REQUIRED)

target_sources(${PROJECT_NAME}
        PRIVATE
        fire-renderer-text.h
        fire-renderer-text.cpp
        fire-renderer-sdl.h
        fire-renderer-sdl.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        SDL2::SDL2)