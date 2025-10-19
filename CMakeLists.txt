cmake_minimum_required( VERSION 3.6 FATAL_ERROR )

project( HelloWorld_Template LANGUAGES CXX )

set ( CMAKE_CXX_STANDARD 23 )
set ( CMAKE_CXX_STANDARD_REQUIRED ON )

set ( wxBUILD_SHARED OFF )
set ( wxBUILD_CXX_STANDARD 23 )

add_subdirectory( "Code/ThirdParty/wxWidgets" )

# إنشاء ملف الmanifest
if ( WIN32 )
    set(MANIFEST_CONTENT "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>\n<assembly xmlns=\"urn:schemas-microsoft-com:asm.v1\" manifestVersion=\"1.0\" xmlns:asmv3=\"urn:schemas-microsoft-com:asm.v3\">\n  <asmv3:application>\n    <asmv3:windowsSettings>\n      <dpiAware xmlns=\"http://schemas.microsoft.com/SMI/2005/WindowsSettings\">true</dpiAware>\n      <dpiAwareness xmlns=\"http://schemas.microsoft.com/SMI/2016/WindowsSettings\">PerMonitorV2</dpiAwareness>\n    </asmv3:windowsSettings>\n  </asmv3:application>\n</assembly>")
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.exe.manifest" "${MANIFEST_CONTENT}")
endif()

# إنشاء ملف Info.plist
if ( APPLE )
    set(PLIST_CONTENT "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<!DOCTYPE plist PUBLIC \"-//Apple Computer//DTD PLIST 1.0//EN\" \"http://www.apple.com/DTDs/PropertyList-1.0.dtd\">\n<plist version=\"1.0\">\n<dict>\n    <key>CFBundleIdentifier</key>\n    <string>com.example.${PROJECT_NAME}</string>\n\t<key>CFBundleDevelopmentRegion</key>\n\t<string>English</string>\n    <key>CFBundlePackageType</key>\n\t<string>APPL</string>\n    <key>NSPrincipalClass</key>\n    <string>NSApplication</string>\n    <key>NSHighResolutionCapable</key>\n    <true/>\n</dict>\n</plist>")
    file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/Info.plist" "${PLIST_CONTENT}")
endif()

set( SRCS
    "${CMAKE_CURRENT_SOURCE_DIR}/Code/StartUpPoint/main.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/Code/StartUpPoint/main.cpp"
)

if ( APPLE )
    # create bundle on apple compiles
    add_executable( ${PROJECT_NAME} MACOSX_BUNDLE ${SRCS} )

    # Set a custom plist file for the app bundle - needed for Mac OS Retina display
    set_target_properties( ${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_BINARY_DIR}/Info.plist" )
elseif( WIN32 )
    file( WRITE "${CMAKE_CURRENT_BINARY_DIR}/resources.rc" "#include \"wx/msw/wx.rc\"\n" )
        set( SRCS ${SRCS} "${CMAKE_CURRENT_BINARY_DIR}/resources.rc" )
    # the WIN32 is needed for Windows in order for it to look for WinMain
    # instead of the main function. This is ignored on other systems,
    # so it works on all platforms
    add_executable( ${PROJECT_NAME} WIN32 ${SRCS} "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.exe.manifest" )
else()
    add_executable( ${PROJECT_NAME} ${SRCS} )
endif()

target_link_libraries( ${PROJECT_NAME} PRIVATE wx::net wx::core wx::base )

install( TARGETS ${PROJECT_NAME} BUNDLE DESTINATION . LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} )
