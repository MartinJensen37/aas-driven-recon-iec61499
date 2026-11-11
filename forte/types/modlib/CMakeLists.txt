# This file was generated using the 4DIAC FORTE Export Filter 3.2.0.202607081531!

cmake_minimum_required(VERSION 3.30)
project(forte-modlib
        DESCRIPTION "0.1.0"
        VERSION "0.1.0"
        LANGUAGES C CXX
)

if (NOT TARGET forte)
        find_package(forte 3.0 REQUIRED)
endif ()

add_library(forte-modlib)
target_link_libraries(forte-modlib PUBLIC forte-core)
get_target_property(forte_IMPORTED forte IMPORTED)
if (NOT forte_IMPORTED)
        target_link_libraries(forte PUBLIC $<IF:$<BOOL:${BUILD_SHARED_LIBS}>,forte-modlib,$<LINK_LIBRARY:WHOLE_ARCHIVE,forte-modlib>>)
endif ()

add_subdirectory(include)
add_subdirectory(src)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

set(ConfigPackageLocation lib/cmake/forte-modlib-${PROJECT_VERSION})

configure_package_config_file(
        forte-modlib-config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/forte-modlib-config.cmake
        INSTALL_DESTINATION ${ConfigPackageLocation}
)

write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/forte-modlib-config-version.cmake
        COMPATIBILITY AnyNewerVersion
)

install(TARGETS forte-modlib EXPORT forte-modlib-export FILE_SET HEADERS)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/forte-modlib-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/forte-modlib-config-version.cmake
        DESTINATION ${ConfigPackageLocation}
)

install(EXPORT forte-modlib-export
        DESTINATION ${ConfigPackageLocation}
        EXPORT_LINK_INTERFACE_LIBRARIES
)

# Added by validate.ps1: headers of standard FBs used inside the composites (the IO blocks set up
# their GPIO line or PWM channel: the Linux modules, or their stand-ins elsewhere).
foreach (lib forte-events forte-net forte-gpiochip forte-pwmsysfs forte-iostubs)
        if (TARGET ${lib})
                target_link_libraries(forte-modlib PUBLIC ${lib})
        endif ()
endforeach ()
target_link_libraries(forte-modlib PUBLIC )
