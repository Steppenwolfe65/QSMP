/* 2022 Digital Freedom Defense Incorporated
* All Rights Reserved.
*
* NOTICE:  All information contained herein is, and remains
* the property of Digital Freedom Defense Incorporated.
* The intellectual and technical concepts contained
* herein are proprietary to Digital Freedom Defense Incorporated
* and its suppliers and may be covered by U.S. and Foreign Patents,
* patents in process, and are protected by trade secret or copyright law.
* Dissemination of this information or reproduction of this material
* is strictly forbidden unless prior written permission is obtained
* from Digital Freedom Defense Incorporated.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

/**
* \file appsrv.h
* \brief The server application
* Version 1.2a: 2022-05-01
*/

#ifndef QSMP_SERVER_APP_H
#define QSMP_SERVER_APP_H

#include "common.h"
#include "../../QSC/QSC/socketbase.h"
#include "../../QSC/QSC/socketserver.h"

#define QSMP_SERVER_MAX_CLIENTS 8192

static const char QSMP_PUBKEY_NAME[] = "server_public_key.qpkey";
static const char QSMP_PRIKEY_NAME[] = "server_secret_key.qskey";
static const char QSMP_APP_PATH[] = "QSMP";

#endif
