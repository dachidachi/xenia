/**
 ******************************************************************************
 * Xenia : Xbox 360 Emulator Research Project                                 *
 ******************************************************************************
 * Copyright 2013 Ben Vanik. All rights reserved.                             *
 * Released under the BSD license - see LICENSE in the root for more details. *
 ******************************************************************************
 */

#ifndef XENIA_CORE_SOCKET_H_
#define XENIA_CORE_SOCKET_H_

#include <xenia/common.h>
#include <xenia/core.h>


typedef intptr_t socket_t;
#define XE_INVALID_SOCKET -1


void xe_socket_init();

socket_t xe_socket_create_tcp();
void xe_socket_close(socket_t socket);

void xe_socket_set_keepalive(socket_t socket, bool value);
void xe_socket_set_reuseaddr(socket_t socket, bool value);
void xe_socket_set_nodelay(socket_t socket, bool value);
void xe_socket_set_nonblock(socket_t socket, bool value);

int xe_socket_bind(socket_t socket, uint32_t port);
int xe_socket_bind_loopback(socket_t socket);
int xe_socket_listen(socket_t socket);

typedef struct {
  socket_t  socket;
  char      addr[16];
} xe_socket_connection_t;
int xe_socket_accept(socket_t socket, xe_socket_connection_t* out_client_info);

int64_t xe_socket_send(socket_t socket, const uint8_t* data, size_t length,
                       int flags, int* out_error_code);
int64_t xe_socket_recv(socket_t socket, uint8_t* data, size_t length, int flags,
                       int* out_error_code);

typedef struct xe_socket_loop xe_socket_loop_t;
xe_socket_loop_t* xe_socket_loop_create(socket_t socket);
void xe_socket_loop_destroy(xe_socket_loop_t* loop);
int xe_socket_loop_poll(xe_socket_loop_t* loop,
                        bool check_read, bool check_write);
void xe_socket_loop_set_queued_write(xe_socket_loop_t* loop);
bool xe_socket_loop_check_queued_write(xe_socket_loop_t* loop);
bool xe_socket_loop_check_socket_recv(xe_socket_loop_t* loop);
bool xe_socket_loop_check_socket_send(xe_socket_loop_t* loop);


#endif  // XENIA_CORE_SOCKET_H_
