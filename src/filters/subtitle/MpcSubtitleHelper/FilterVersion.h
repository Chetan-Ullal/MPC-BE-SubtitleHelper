/*
 * (C) 2006-2024 see Authors.txt
 *
 * This file is part of MPC-BE.
 *
 * MPC-BE is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * MPC-BE is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#pragma once

#include "Version.h"

#ifndef FILTER_VERSION_MAJOR
#define FILTER_VERSION_MAJOR 0
#endif

#ifndef FILTER_VERSION_MINOR
#define FILTER_VERSION_MINOR 0
#endif

#ifndef FILTER_VERSION_PATCH
#define FILTER_VERSION_PATCH 0
#endif

#define FILTER_VERSION_REV 0

#define FILTER_VERSION_FULL_NUM    FILTER_VERSION_MAJOR,FILTER_VERSION_MINOR,FILTER_VERSION_PATCH,FILTER_VERSION_REV
#define FILTER_VERSION_FULL_STR    MAKE_STR(FILTER_VERSION_MAJOR) "." MAKE_STR(FILTER_VERSION_MINOR) "." MAKE_STR(FILTER_VERSION_PATCH) "." MAKE_STR(FILTER_VERSION_REV)
#define FILTER_VERSION_FULL_WSTR   _CRT_WIDE(FILTER_VERSION_FULL_STR)
