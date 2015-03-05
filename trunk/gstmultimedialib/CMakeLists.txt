cmake_minimum_required(VERSION 2.8) 
SET( CMAKE_CXX_COMPILER clang++ )
project(gstmultimedialib)

add_subdirectory(Utilities)
add_subdirectory(GLEngine)
#add_subdirectory(gmock-1.6.0)

add_subdirectory(Multimedia)
add_subdirectory(TestMultimedia)
add_subdirectory(GstPlayer)
add_subdirectory(assimp-3.1.1)
#add_subdirectory(assimp)