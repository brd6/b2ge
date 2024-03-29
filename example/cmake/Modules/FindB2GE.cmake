include(FindPackageHandleStandardArgs)

find_path(B2GE_INCLUDE_DIR b2ge/b2ge.hpp PATH_SUFFIXES include)
find_library(B2GE_LIBRARIES NAMES b2ge PATH_SUFFIXES lib)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(b2ge DEFAULT_MSG B2GE_LIBRARIES B2GE_INCLUDE_DIR)