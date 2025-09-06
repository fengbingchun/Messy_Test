#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "OpenXLSX::OpenXLSX" for configuration "Release"
set_property(TARGET OpenXLSX::OpenXLSX APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(OpenXLSX::OpenXLSX PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/OpenXLSX.lib"
  )

list(APPEND _cmake_import_check_targets OpenXLSX::OpenXLSX )
list(APPEND _cmake_import_check_files_for_OpenXLSX::OpenXLSX "${_IMPORT_PREFIX}/lib/OpenXLSX.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
