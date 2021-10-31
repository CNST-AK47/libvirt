/*
 * Copyright (C) 2019 Red Hat, Inc.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#pragma once
/**
 * @file glibcompat.h
 * @brief  glibcompat 相关函数封装文件
 * @details 
 * @author wangpengcheng  (wangpengcheng2018@gmail.com)
 * @version 1.0
 * @date 2021-10-20 00:51:43
 * @copyright Copyright (c) 2021  IRLSCU
 * 
 * @par 修改日志:
 * <table>
 * <tr>
 *    <th> Commit date</th>
 *    <th> Version </th> 
 *    <th> Author </th>  
 *    <th> Description </th>
 * </tr>
 * <tr>
 *    <td> 2021-10-20 00:51:43 </td>
 *    <td> 1.0 </td>
 *    <td> wangpengcheng </td>
 *    <td>内容</td>
 * </tr>
 * </table>
 */
#include <glib.h>
#include <glib/gstdio.h>

/**
 * @brief  获取完整的文件路径
 * @param  filename         文件名称
 * @param  relative_to      文件相对路径
 * @return gchar*  文件对应的绝对路径
 */
gchar * vir_g_canonicalize_filename(const gchar *filename,
                                    const gchar *relative_to);

/**
 * @brief  vir文件同步
 * @param  fd         文件句柄编号
 * @return gint         
 */
gint vir_g_fsync(gint fd);
char *vir_g_strdup_printf(const char *msg, ...)
    G_GNUC_PRINTF(1, 2);
char *vir_g_strdup_vprintf(const char *msg, va_list args)
    G_GNUC_PRINTF(1, 0);

#if !GLIB_CHECK_VERSION(2, 64, 0)
# define g_strdup_printf vir_g_strdup_printf
# define g_strdup_vprintf vir_g_strdup_vprintf
#endif

#define g_canonicalize_filename vir_g_canonicalize_filename
#undef g_fsync
#define g_fsync vir_g_fsync
