add_subdirectory(fixtures/executable)
add_subdirectory(fixtures/shared-library)

if(WIN32)
  add_subdirectory(fixtures/delay-load)
endif()
