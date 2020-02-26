cmake_minimum_required(VERSION 3.0.0)
project(Blockie)

#SDL2 libraries
if(WIN32)
    find_package(SDL2 PATHS libs REQUIRED)
    include_directories(${SDL2_INCLUDE})
    include_directories(${SDL2_IMAGE_INCLUDE})
    include_directories(${SDL2_MIXER_INCLUDE})
    include_directories(${SDL2_TTF_INCLUDE})
elseif(UNIX)
    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
    include_directories(${SDL2_IMAGE_INCLUDE})
    include_directories(${SDL2_MIXER_INCLUDE})
    include_directories(${SDL2_TTF_INCLUDE})
endif()

#Game source
include_directories(Blockie)
file(GLOB SOURCES "Blockie/*.cpp" "Blockie/*.h")

add_executable(Blockie ${SOURCES})
target_link_libraries(Blockie ${SDL2_LIBRARIES} ${SDL2_IMAGE} ${SDL2_MIXER} ${SDL2_TTF})