cmake_minimum_required (VERSION 3.5)

project(decodertest)

message(build dir:${CURL_BUILD_DIR}, top dir )

include_directories(
	${T507_SDK_INCLUDE_DIRS}
	${CMAKE_CURRENT_LIST_DIR}/include
)
link_directories(
	${T507_SDK_LINK_DIRS}
	${CMAKE_CURRENT_LIST_DIR}/lib
)
add_executable(decodertest main.cpp)
target_link_libraries(decodertest TTARtspPusher DjiRtspImageSource)


# ------------------------------- install script -------------------------------
install(
TARGETS ${PROJECT_NAME}
RUNTIME DESTINATION bin/test
)

