cmake_minimum_required(VERSION 2.6)
project(ICHIMANYEN)

find_package(PkgConfig)
pkg_check_modules(GTK gtk+-2.0) # look into FindPkgConfig.cmake, 
pkg_check_modules(GLADE libglade-2.0) # look into FindPkgConfig.cmake, 
pkg_check_modules(GLIB glib-2.0) # look into FindPkgConfig.cmake, 
if(GLADE_NOT_FOUND)
  message("truc qui cloche")
endif(GLADE_NOT_FOUND)
                      
                                          # it contains documentation
# Now the variables GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES 
# contain what you expect 

add_subdirectory(src) 
#add_subdirectory(bin)
