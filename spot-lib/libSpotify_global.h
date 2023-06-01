#ifndef LIBPORNO_GLOBAL_H
#define LIBSPOTIFY_GLOBAL_H 

#include <QtCore/qglobal.h>

#if defined(LIBSPOTIFY_LIBRARY)
#   define LIBSPOTIFYSHARED_EXPORT Q_DECL_EXPORT
#else
#   define LIBSPOTIFYSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif