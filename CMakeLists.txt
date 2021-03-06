####################################################################
#   Project configuration
####################################################################
cmake_minimum_required(VERSION 3.4 FATAL_ERROR)

project (PhoenixStrategie)
set     (PhoenixStrategie_VERSION_MAJOR 0)
set     (PhoenixStrategie_VERSION_MINOR 1)

include(${GenericCmakeLists})

####################################################################
#   Library modules
####################################################################
# "Double syntax" nécessaire pour les projets en-dehors de ce dossier
# La source est à l'extérieur de ce dossier, mais la compilation s'effectue ici.
# EXCLUDE_FROM_ALL : ne pas compiler les targets des sous-projets par défaut
add_subdirectory(
    ${CMAKE_CURRENT_SOURCE_DIR}/../board-carte_kiwi
    ${CMAKE_CURRENT_BINARY_DIR}/board-carte_kiwi
    EXCLUDE_FROM_ALL)

####################################################################
#   Source
####################################################################
add_executable(${PROJECT_NAME}
    ${CMAKE_CURRENT_SOURCE_DIR}/main.c
    # ${CMAKE_CURRENT_SOURCE_DIR}/mandel.c
)
add_executable(main_binary ALIAS ${PROJECT_NAME})

include_directories(
    ${PROJECT_SOURCE_DIR}/
    $<TARGET_PROPERTY:PhoenixBoard_CarteKiwiLib,INTERFACE_INCLUDE_DIRECTORIES>
)


target_link_libraries(${PROJECT_NAME}
    # la_super_librairieLib
    PhoenixBoard_CarteKiwiLib
    ${Toolchain_LFlags}
)
