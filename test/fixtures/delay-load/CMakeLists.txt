add_library(delay_load SHARED lib.c)

target_link_libraries(delay_load PRIVATE user32 delayimp)

target_link_options(delay_load PRIVATE /DELAYLOAD:user32.dll)

set_target_properties(
  delay_load
  PROPERTIES
  OUTPUT_NAME lib
  MSVC_RUNTIME_LIBRARY MultiThreaded
)

bare_target(target)

install(
  TARGETS delay_load
  DESTINATION ${CMAKE_CURRENT_LIST_DIR}/${target}
  COMPONENT fixtures
  EXCLUDE_FROM_ALL
)
