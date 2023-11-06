cmake_minimum_required(VERSION 3.7.2)


SET(CMAKE_C_STANDARD 11)

# SET(CMAKE_C_COMPILER   /usr/bin/gcc)
# SET(CMAKE_CXX_COMPILER   /usr/bin/g++)

project(log_tree)

aux_source_directory(. main)

add_executable(log_tree ${main})

# TARGET_LINK_LIBRARIES(TEST
#     SRC
#     # paho-mqtt3c-static
#     paho-mqtt3a-static
#     cJSON
#     AES
# )
