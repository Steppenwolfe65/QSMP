#ifndef QSC_TIMEREX_H
#define QSC_TIMEREX_H

/*
* Copyright (c) 2023 Quantum Secure Cryptographic Solutions QSCS Corp. (QSCS.ca).
* This file is part of the QSC Cryptographic library.
* The QSC library was written as a prototyping library for post-quantum primitives,
* in the hopes that it would be useful for educational purposes only.
* Any use of the QSC library in a commercial context, or reproduction of original material
* contained in this library is strictly forbidden unless prior written consent is obtained
* from the QSCS Corporation.
*
* The AGPL version 3 License (AGPLv3)
* This program is free software : you can redistribute it and / or modify
* it under the terms of the GNU Affero General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
* See the GNU Affero General Public License for more details.
*
* You should have received a copy of the GNU Affero General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "common.h"
#include <time.h>

/**
* \file timerex.h
* \brief This file contains common time measurement functions
*/

/*!
* \def QSC_TIMEREX_TIME_STAMP_MAX
* \brief The maximum time-stamp array size
*/
#define QSC_TIMEREX_TIMESTAMP_MAX 80

/**
* \brief Get the calendar date from the current locale
*
* \param output: The output date string
* \return 
*/
QSC_EXPORT_API void qsc_timerex_get_date(char output[QSC_TIMEREX_TIMESTAMP_MAX]);

/**
* \brief Get the calendar date and time from the current locale
*
* \param output: The output time and date string
* \return
*/
QSC_EXPORT_API void qsc_timerex_get_datetime(char output[QSC_TIMEREX_TIMESTAMP_MAX]);

/**
* \brief Get the local time
*
* \param output: The output time string
*/
QSC_EXPORT_API void qsc_timerex_get_time(char output[QSC_TIMEREX_TIMESTAMP_MAX]);

/**
* \brief Returns the clock time at the start of a timed operation
*
* \return The starting clock time
*/
QSC_EXPORT_API uint64_t qsc_timerex_stopwatch_start();

/**
* \brief Returns the time difference between the start and current time in milliseconds
*
* \return The time difference in milliseconds
*/
QSC_EXPORT_API uint64_t qsc_timerex_stopwatch_elapsed(uint64_t start);

#if defined(QSC_DEBUG_MODE)
/**
* \brief Print timer function values
*/
QSC_EXPORT_API void qsc_timerex_print_values();
#endif

#endif
