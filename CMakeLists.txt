cmake_minimum_required (VERSION 3.10.2)
project (ArenaSDK)

include_directories(include)
include_directories(include/Arena)
include_directories(include/GenTL)
include_directories(include/Save)
include_directories(include/GenICam)

link_directories(lib)
link_directories(lib/GenICam)
link_directories(lib/ffmpeg)

set(GENICAMLIB
        GCBase_gcc421_v3_0
        GenApi_gcc421_v3_0
        Log_gcc421_v3_0
        log4cpp_gcc421_v3_0
        MathParser_gcc421_v3_0
        NodeMapData_gcc421_v3_0
        XmlParser_gcc421_v3_0)

set(FFMPEGLIB
        avcodec
        avdevice
        avfilter
        avformat
        avutil
        swresample
        swscale)

add_executable (example 
    src/main.cpp )

target_link_libraries (example 
    arena 
    save 
    gentl 
    ${GENICAMLIB} 
    ${FFMPEGLIB})
