# Find the WordNet includes and library
#
# This module defines
# LIBWORDNET_INCLUDE_DIR, where to find WordNet include files, etc.
# LIBWORDNET_LIBRARIES, the libraries to link against to use WordNet.
# LIBWORDNET_FOUND, If false, do not try to use WordNet.

# also defined, but not for general use are
# LIBWORDNET_LIBRARY, where to find the WordNet library.

#MESSAGE("Searching for wordnet library")

FIND_PATH(LIBWORDNET_INCLUDE_DIR wn.h
  /usr/local/include
  /usr/include
  /opt/local/include
)

FIND_LIBRARY(LIBWORDNET_LIBRARY wn
  /usr/local/lib
  /usr/lib
  /opt/local/lib
)

IF(LIBWORDNET_INCLUDE_DIR)
  IF(LIBWORDNET_LIBRARY)
    SET(LIBWORDNET_FOUND TRUE)
    SET(LIBWORDNET_LIBRARIES ${LIBWORDNET_LIBRARY})
	ELSE(LIBWORDNET_LIBRARY)
    SET(LIBWORDNET_FOUND FALSE)
  ENDIF(LIBWORDNET_LIBRARY)
ENDIF(LIBWORDNET_INCLUDE_DIR)

IF (LIBWORDNET_FOUND)
   IF (NOT WordNet_FIND_QUIETLY)
      MESSAGE(STATUS "Found WordNet: ${LIBWORDNET_LIBRARIES}" )
   ENDIF (NOT WordNet_FIND_QUIETLY)
ELSE (LIBWORDNET_FOUND)
   IF (WordNet_FIND_REQUIRED)
      MESSAGE(SEND_ERROR "Could NOT find WordNet")
   ENDIF (WordNet_FIND_REQUIRED)
ENDIF (LIBWORDNET_FOUND)

MARK_AS_ADVANCED(LIBWORDNET_INCLUDE_DIR LIBWORDNET_LIBRARIES)
