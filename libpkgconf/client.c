/*
 * client.c
 * libpkgconf consumer lifecycle management
 *
 * Copyright (c) 2016 pkgconf authors (see AUTHORS).
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * This software is provided 'as is' and without any warranty, express or
 * implied.  In no event shall the authors be liable for any damages arising
 * from the use of this software.
 */

#include <libpkgconf/libpkgconf.h>

void
pkgconf_client_init(pkgconf_client_t *client, pkgconf_error_handler_func_t error_handler)
{
	client->error_handler = error_handler;
	client->auditf = NULL;
}

pkgconf_client_t *
pkgconf_client_new(pkgconf_error_handler_func_t error_handler)
{
	pkgconf_client_t *out = calloc(sizeof(pkgconf_client_t), 1);
	pkgconf_client_init(out, error_handler);
	return out;
}

void
pkgconf_client_deinit(pkgconf_client_t *client)
{
	pkgconf_tuple_free_global(client);
	pkgconf_path_free(&client->dir_list);
}

void
pkgconf_client_free(pkgconf_client_t *client)
{
	pkgconf_client_deinit(client);
	free(client);
}
