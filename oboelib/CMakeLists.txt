cmake_minimum_required(VERSION 3.4.1)

add_library(oboe-kit
            SHARED
            src/main/cpp/OboeKit.cpp
            src/main/cpp/Oscillator.cpp
            src/main/cpp/AudioEngine.cpp
            src/main/cpp/SoundRecording.cpp
            src/main/cpp/SoundRecordingUtilities.cpp
        )


set(OBOE_DIR src/main/cpp/oboe)
add_subdirectory(${OBOE_DIR} src/main/cpp/oboe)

include_directories(${OBOE_DIR}/include)

find_library(log-lib
            log)

target_link_libraries(oboe-kit
                      aaudio
                    ${log-lib})