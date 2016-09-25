####################################################################
#   Project configuration
####################################################################
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

# Toolchain = architecture utilisée
include("${CMAKE_CURRENT_SOURCE_DIR}/../toolchains/${ARCH}.cmake")

project (PhoenixStrategie)
set     (PhoenixStrategie_VERSION_MAJOR 0)
set     (PhoenixStrategie_VERSION_MINOR 1)

####################################################################
#   Library modules
####################################################################
# "Double syntax" nécessaire pour les projets en-dehors de ce dossier
# La source est à l'extérieur de ce dossier, mais la compilation s'effectue ici.
# EXCLUDE_FROM_ALL : ne pas compiler les targets des sous-projets par défaut
# add_subdirectory(
#     ${CMAKE_CURRENT_SOURCE_DIR}/../librairie
#     ${CMAKE_CURRENT_BINARY_DIR}/librairie
#     EXCLUDE_FROM_ALL)

add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../cartographie
    ${CMAKE_CURRENT_BINARY_DIR}/cartographie
    EXCLUDE_FROM_ALL)

####################################################################
#   Source
####################################################################

set(STRATEGIE_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
)

include_directories(
    ${PROJECT_SOURCE_DIR}/
    # $<TARGET_PROPERTY:la_super_librairieLib,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:cartographieLib,INTERFACE_INCLUDE_DIRECTORIES>
)

add_executable(strategie
    ${STRATEGIE_SRC}
)

target_link_libraries(strategie
    # la_super_librairieLib
    cartographieLib
)
