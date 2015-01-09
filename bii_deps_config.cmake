SET(LOG_LEVEL 10 CACHE INT "Logging level" FORCE)
SET(CMAKE_BUILD_TYPE RELEASE CACHE STRING "Release type" FORCE)

if(MSVC)
  IF(CMAKE_BUILD_TYPE STREQUAL "DEBUG")
	  TARGET_COMPILE_OPTIONS(hjiang_jsonxx_interface INTERFACE "/MTd")
  ELSE()
	  TARGET_COMPILE_OPTIONS(hjiang_jsonxx_interface INTERFACE "/MT")
  ENDIF()
endif()