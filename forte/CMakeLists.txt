# Eclipse 4diac FORTE 3.3.0 with the filling module's block types (exported by the 4diac IDE into
# types/) linked in. Built by the Dockerfile; FORTE_SOURCE is the patched FORTE checkout.
cmake_minimum_required(VERSION 3.30)
project(forte-filling-module CXX)
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

add_subdirectory(${FORTE_SOURCE} ${CMAKE_CURRENT_BINARY_DIR}/forte EXCLUDE_FROM_ALL)

# The module-independent library (occupation, module state, skill state machine, IO primitives)
# and the filling module's own types (equipment and skill primitives).
foreach(types IN ITEMS modlib filling)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/types/${types} ${CMAKE_CURRENT_BINARY_DIR}/types-${types})
endforeach()

install(TARGETS forte DESTINATION bin)
