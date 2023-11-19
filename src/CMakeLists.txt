project(Clogger-pp)

add_library(Cloggerpp SHARED
    Clogger.cpp
    TUI.cpp
)
add_library(Cloggerpp::Cloggerpp ALIAS Cloggerpp)

target_include_directories(Cloggerpp SYSTEM PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/)
target_link_libraries(Cloggerpp PRIVATE ncurses)

install(
    TARGETS Cloggerpp
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
