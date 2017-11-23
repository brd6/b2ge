include(FindPackageHandleStandardArgs)

# Search for the header file
find_path(B2GE_INCLUDE_DIR xyginext/b2ge.hpp PATH_SUFFIXES include)

# Search for the library
find_library(B2GE_LIBRARIES NAMES b2ge PATH_SUFFIXES lib)

# Did we find everything we need?
FIND_PACKAGE_HANDLE_STANDARD_ARGS(b2ge DEFAULT_MSG B2GE_LIBRARIES B2GE_INCLUDE_DIR)