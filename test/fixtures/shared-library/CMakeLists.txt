add_library(lib SHARED lib.c)

bare_target(target)

install(
  TARGETS lib
  DESTINATION ${CMAKE_CURRENT_LIST_DIR}/${target}
)
