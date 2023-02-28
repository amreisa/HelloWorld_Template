cmake_minimum_required( VERSION 3.6 FATAL_ERROR )

project( HelloWorld_Template LANGUAGES CXX )

set ( CMAKE_CXX_STANDARD 17 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )

set ( wxBUILD_SHARED OFF )
set ( wxBUILD_CXX_STANDARD 17 )

add_subdirectory( "Code/ThirdParty/wxWidgets" )

set( SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/Code/StartUpPoint/main.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Code/StartUpPoint/main.cpp"
)

if ( APPLE )
    # create bundle on apple compiles
    add_executable( ${PROJECT_NAME} MACOSX_BUNDLE ${SRCS} )

    # Set a custom plist file for the app bundle - needed for Mac OS Retina display
    set_target_properties( ${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist )
elseif( WIN32 )
    # the WIN32 is needed for Windows in order for it to look for WinMain
    # instead of the main function. This is ignored on other systems,
    # so it works on all platforms
    add_executable( ${PROJECT_NAME} WIN32 ${SRCS} ${PROJECT_NAME}.exe.manifest )
else()
    add_executable( ${PROJECT_NAME} ${SRCS} )
endif()

target_link_libraries( ${PROJECT_NAME} PRIVATE wx::net wx::core wx::base )

install( TARGETS ${PROJECT_NAME} BUNDLE DESTINATION . LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} )
