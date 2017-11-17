add_definitions(
  -W
  #-pedantic
  #-Wall
)
link_directories(
  ${GLIB_LIBRARY_DIRS}  ${GTK_LIBRARY_DIRS}  ${GLADE_LIBRARY_DIRS} 
  )
#link_directories(
#    ${GTK_LIBRARY_DIRS} )
#link_directories(
#    ${GLADE_LIBRARY_DIRS} )
include_directories(
  ${GLIB_INCLUDE_DIRS} ${GTK_INCLUDE_DIRS} ${GLADE_INCLUDE_DIRS} 
  )
#include_directories(
#    ${GTK_INCLUDE_DIRS}  )
#include_directories(
#    ${GLADE_INCLUDE_DIR}  )
add_executable(../../bin/match
  match.c
)

add_executable(../../bin/game # name of the executable on Windows will be example.exe 
  game.c
  )


add_executable(../../bin/ichimanyenide # name of the executable on Windows will be example.exe 
  ichimanyen.c
  ichimanyen.h
  file_menu_hundlers.c
  file_menu_hundlers.h
  compiling_hundlers.c 
  compiling_hundlers.h 
  rules_applications.c
  rules_applications.h
  )

target_link_libraries(../../bin/game 
    ${GTK_LIBRARIES}  ${GLIB_LIBRARIES}
    )

#target_link_libraries(../bin/game 
#    ${GLIB_LIBRARIES} 
#    )

target_link_libraries(../../bin/ichimanyenide
    ${GTK_LIBRARIES}  ${GLADE_LIBRARIES})

#target_link_libraries(../bin/ichimanyenide
#    ${GLADE_LIBRARIES} )
