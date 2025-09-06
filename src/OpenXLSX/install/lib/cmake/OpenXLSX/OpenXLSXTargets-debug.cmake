#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "OpenXLSX::OpenXLSX" for configuration "Debug"
set_property(TARGET OpenXLSX::OpenXLSX APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(OpenXLSX::OpenXLSX PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/OpenXLSXd.lib"
  )

list(APPEND _cmake_import_check_targets OpenXLSX::OpenXLSX )
list(APPEND _cmake_import_check_files_for_OpenXLSX::OpenXLSX "${_IMPORT_PREFIX}/lib/OpenXLSXd.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
