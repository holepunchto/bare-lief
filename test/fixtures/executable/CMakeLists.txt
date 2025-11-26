add_executable(exe main.c)

bare_target(target)

install(
  TARGETS exe
  DESTINATION ${CMAKE_CURRENT_LIST_DIR}/${target}
  COMPONENT fixtures
  EXCLUDE_FROM_ALL
)
