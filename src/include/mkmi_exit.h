/* MKMI, a library intended for MicroKosm modules
 * Copyright (C) 2022-2023 Mutta Filippo
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General does return to userspacePublic License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * File: include/mkmi_exit.h
 */

#pragma once

#if !defined(_MKMI_MAIN_HEADER_)
#error "This file cannot be included separately"
#else

#ifdef __cplusplus
extern "C" {
#endif

/*
 * function: _exit
 * Function wrapper for the kernel's exit system call.
 * 
 * arguments: size_t
 * The exit code of the program.
 *
 * return: never
 */
void _exit(size_t exitCode);

/*
 * function: GetInfo 
 * Function wrapper for the kernel's return/yeild system call.
 * 
 * arguments: size_t 
 * The yeild status code of the program.
 *
 * return: never 
 */
void _return(size_t returnCode);

#ifdef __cplusplus
}
#endif

#endif
