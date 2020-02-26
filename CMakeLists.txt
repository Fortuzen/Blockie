cmake_minimum_required(VERSION 3.0.0)
project(Blockie)

#Game source
include_directories(Blockie)
file(GLOB SOURCES "Blockie/*.cpp" "Blockie/*.h")

add_executable(Blockie ${SOURCES})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_LIST_DIR}")

#SDL2 libraries
if(WIN32)
    find_package(SDL2 PATHS libs REQUIRED)
    include_directories(${SDL2_INCLUDE})
    include_directories(${SDL2_IMAGE_INCLUDE})
    include_directories(${SDL2_MIXER_INCLUDE})
    include_directories(${SDL2_TTF_INCLUDE})
    target_link_libraries(Blockie ${SDL2_LIBRARIES} ${SDL2_IMAGE} ${SDL2_MIXER} ${SDL2_TTF})
elseif(UNIX)
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
    find_package(SDL2_ttf REQUIRED)
    find_package(SDL2_mixer REQUIRED)
    include_directories(${SDL2_INCLUDE_DIR})
    include_directories(${SDL2_IMAGE_INCLUDE_DIR})
    include_directories(${SDL2_MIXER_INCLUDE_DIR})
    include_directories(${SDL2_TTF_INCLUDE_DIR})
    target_link_libraries(Blockie ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES}
                                     ${SDL2_MIXER_LIBRARIES} ${SDL2_TTF_LIBRARIES})

endif()




