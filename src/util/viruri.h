/*
 * viruri.h: internal definitions used for URI parsing.
 *
 * Copyright (C) 2012 Red Hat, Inc.
 *
 * See COPYING.LIB for the License of this software
 */

#ifndef __VIR_URI_H__
# define __VIR_URI_H__

# include <libxml/uri.h>

# include "internal.h"

typedef struct _virURI virURI;
typedef virURI *virURIPtr;

struct _virURI {
    char *scheme;       /* the URI scheme */
    char *server;       /* the server part */
    char *user;         /* the user part */
    int port;           /* the port number */
    char *path;         /* the path string */
    char *query;        /* the query string */
    char *fragment;     /* the fragment string */
};

virURIPtr virURIParse(const char *uri)
    ATTRIBUTE_NONNULL(1);
char *virURIFormat(virURIPtr uri)
    ATTRIBUTE_NONNULL(1);

void virURIFree(virURIPtr uri);

#endif /* __VIR_URI_H__ */
