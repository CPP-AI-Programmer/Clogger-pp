cmake_minimum_required(VERSION 3.22.1) # my version
project(Clogger-pp VERSION 1.0.8)

include(GNUInstallDirs)

add_library(Cloggerpp SHARED
    src/Clogger.cpp
)
add_library(Cloggerpp::Cloggerpp ALIAS Cloggerpp)

target_link_libraries(Cloggerpp PRIVATE ncurses)

target_include_directories(
    Cloggerpp
    PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
)

install(DIRECTORY include/Cloggerpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(TARGETS Cloggerpp
  EXPORT CloggerppTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Include the CMakePackageConfigHelpers module
include(CMakePackageConfigHelpers)

# Set some properties for your library target
set_property(TARGET Cloggerpp PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET Cloggerpp PROPERTY SOVERSION 1)
set_property(TARGET Cloggerpp PROPERTY
  INTERFACE_Cloggerpp_MAJOR_VERSION 1)
set_property(TARGET Cloggerpp APPEND PROPERTY
  COMPATIBLE_INTERFACE_STRING Cloggerpp_MAJOR_VERSION
)

# Generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/CloggerppConfigVersion.cmake"
  VERSION "${PROJECT_VERSION}"
  COMPATIBILITY AnyNewerVersion
)

# Create the config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/CloggerppConfig.cmake
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/CloggerppConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Cloggerpp
)

# Install the config and version files
install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/CloggerppConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/cmake/CloggerppConfigVersion.cmake"
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Cloggerpp
)

# Export the targets for the build tree
export(EXPORT CloggerppTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/CloggerppTargets.cmake"
  NAMESPACE Cloggerpp::
)

# Install the export set for the install tree
install(EXPORT CloggerppTargets
  FILE CloggerppTargets.cmake
  NAMESPACE Cloggerpp::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/Cloggerpp
)



