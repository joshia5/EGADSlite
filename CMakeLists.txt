################################
# GLOBAL CONFIGURATION VARIABLES
################################

cmake_minimum_required (VERSION 3.20.0)
set (EGADSlite_VERSION_MAJOR 1)
set (EGADSlite_VERSION_MINOR 19)
project(EGADSlite VERSION ${libMeshb_VERSION_MAJOR}.${libMeshb_VERSION_MINOR}
  LANGUAGES C CXX)

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif ()

if (CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)
endif ()

list (APPEND CMAKE_PREFIX_PATH "${CMAKE_INSTALL_PREFIX}")

#[[
if(WITH_AIO)
   set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWITH_AIO")
   IF(${CMAKE_SYSTEM_NAME} MATCHES Linux)
      set(AIO_LIBRARIES rt)
   endif()
endif()


#######################################
# SET FILES AND DIRECTORIES TO BE BUILT
#######################################

include_directories (${PROJECT_SOURCE_DIR}/sources)
include_directories (${PROJECT_SOURCE_DIR}/utilities)
add_subdirectory (sources)
add_subdirectory (examples)
add_subdirectory (utilities)

install (FILES LICENSE.txt copyright.txt DESTINATION share/libMeshb)
install (DIRECTORY sample_meshes DESTINATION share/libMeshb)


######################################
# SET PACKAGE AND DEPLOYMENT VARIABLES
######################################

if (WITH_CPACK)
   include (InstallRequiredSystemLibraries)
   set (CPACK_GENERATOR TXZ)
   set (CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/copyright.txt)
   set (CPACK_PACKAGE_VERSION_MAJOR ${libMeshb_VERSION_MAJOR})
   set (CPACK_PACKAGE_VERSION_MINOR ${libMeshb_VERSION_MINOR})
   set (CPACK_COMPONENTS_ALL applications examples libraries headers)
   include (CPack)
endif ()


##################################
# EXPORT CMAKE PACKAGE INFORMATION
##################################

include(CMakePackageConfigHelpers)
file(WRITE ${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
"include(\${CMAKE_CURRENT_LIST_DIR}/meshb-target.cmake)
include(\${CMAKE_CURRENT_LIST_DIR}/libMeshb-target.cmake)
set(libMeshb_INCLUDE_DIRS ${CMAKE_INSTALL_PREFIX}/include)
set(libMeshb_LINK_DIRS ${CMAKE_INSTALL_PREFIX}/lib)
set(libMeshb_LIBRARIES Meshb.7 ${AIO_LIBRARIES})
set(libMeshb_Fortran_LIBRARIES Meshbf.7 ${AIO_LIBRARIES})
set(libMeshb_FOUND TRUE)
")
write_basic_package_version_file(
   "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
   VERSION ${PROJECT_VERSION}
   COMPATIBILITY SameMajorVersion)
install(FILES
   "${PROJECT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
   "${PROJECT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
   DESTINATION lib/cmake/${PROJECT_NAME})


##################################
# PRINT OPERATIONS TO BE CONDUCTED
##################################

message("-- Build mode            : " ${CMAKE_BUILD_TYPE})
message("-- cpack target enabled  : " ${WITH_CPACK})
message("-- Asynchronous IO       : " ${WITH_AIO})
message("-- Install directory     : " ${CMAKE_INSTALL_PREFIX})
]]
