project(Clogger-pp)

target_include_directories(Cloggerpp PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

target_sources(Cloggerpp PRIVATE
    Cloggerpp/Clogger.hpp
)

install(DIRECTORY Cloggerpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
