#pragma once

#include <QtGlobal>

#if defined(CHEATSH_LIBRARY)
#  define CHEATSHSHARED_EXPORT Q_DECL_EXPORT
#else
#  define CHEATSHSHARED_EXPORT Q_DECL_IMPORT
#endif
