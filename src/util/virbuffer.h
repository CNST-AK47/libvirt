/*
 * virbuffer.h: buffers for libvirt
 *
 * Copyright (C) 2005-2008, 2011-2014 Red Hat, Inc.
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

#include <stdarg.h>

#include "internal.h"

/**
 * virBuffer:
 *
 * A buffer structure.
 */
// 声明一个buffer
typedef struct _virBuffer virBuffer;
typedef virBuffer *virBufferPtr;

#define VIR_BUFFER_INITIALIZER \
  {                            \
    NULL, 0                    \
  }

/**
 * VIR_BUFFER_INIT_CHILD:
 * @parentbuf: parent buffer for XML element formatting
 *
 * Initialize a virBuffer structure and set up the indentation level for
 * formatting XML subelements of @parentbuf.
 */

/**
 * @brief 初始化buffer的字结构体
 */
#define VIR_BUFFER_INIT_CHILD(parentbuf) \
  {                                      \
    NULL, (parentbuf)->indent + 2        \
  }
/**
 * @brief vir缓冲结构体
 */
struct _virBuffer
{
  GString *str; //< Gstring 指针
  int indent;
};
/**
 * @brief  获取buf上下文字符串
 * @param  buf     buf对应数据
 * @return const char* 返回目标数据指针
 */
const char *virBufferCurrentContent(virBufferPtr buf);
/**
 * @brief  获取相关数据并重置buf
 * @param  buf              My Param doc
 * @return char* 
 */
char *virBufferContentAndReset(virBufferPtr buf);
/**
 * @brief  释放buf内存，并且将数据所有数据重新设置为1
 * @param  buf              buf数据指针
 */
void virBufferFreeAndReset(virBufferPtr buf);
/**
 * @brief Construct a new g define auto cleanup clear func object
 * 使用G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC 定义析构函数
 */
G_DEFINE_AUTO_CLEANUP_CLEAR_FUNC(virBuffer, virBufferFreeAndReset);
/**
 * @brief  查询buffer使用量
 * @param  buf       
 * @return size_t 存储数据量
 */
size_t virBufferUse(const virBuffer *buf);
/**
 * @brief  将str中数据拷贝len到buf中
 * @param  buf              缓冲数据
 * @param  str              原始字符串
 * @param  len              相对长度
 */
void virBufferAdd(virBufferPtr buf, const char *str, int len);
/**
 * @brief  将目标toadd 添加到目标buf上
 * @param  buf              目标buf
 * @param  toadd            需要额外添加的buf
 */
void virBufferAddBuffer(virBufferPtr buf, virBufferPtr toadd);
/**
 * @brief  增加到字符串上
 * @param  buf              buf
 * @param  c                目标字符串
 */
void virBufferAddChar(virBufferPtr buf, char c);

/**
 * @brief 将buf 按照指定格式进行输出
 * @param buf buf
 * @param format 指定格式
 */
void virBufferAsprintf(virBufferPtr buf, const char *format, ...)
    G_GNUC_PRINTF(2, 3); // 注意这里的统一参数参数检查，检查第二合第一个参数
/**
 * @brief 按照指定格式进行输出
 */
void virBufferVasprintf(virBufferPtr buf, const char *format, va_list ap)
    G_GNUC_PRINTF(2, 0);
/**
 * @brief  将参数添加到buf中，对于xml会进行自动格式化
 * @note 最后一个参数为NULL
 * @param  buf              缓冲buf
 * @param  ...              对应的格式参数
 */
void virBufferStrcat(virBufferPtr buf, ...)
    G_GNUC_NULL_TERMINATED;

/**
 * @brief  将参数添加到buf中
 * @param  buf              My Param doc
 * @param  ap               My Param doc
 */
void virBufferStrcatVArgs(virBufferPtr buf, va_list ap);
/**
 * @brief  使用buf将字符串进行替换
 * @param  buf              
 * @param  escape           替换字符串
 * @param  toescape         被替换字符串
 * @param  format           格式
 * @param  str              原始字符串
 */
void virBufferEscape(virBufferPtr buf, char escape, const char *toescape,
                     const char *format, const char *str);

/**
 * @brief  对string 进行标准字符串的替换，主要是针对特殊的符号进行转意
 * @param  buf              目标缓冲区
 * @param  format           指定格式
 * @param  str              原始字符串
 */
void virBufferEscapeString(virBufferPtr buf, const char *format,
                           const char *str);
/**
 * @brief  正则表达式转义
 * @param  buf              My Param doc
 * @param  format           My Param doc
 * @param  str              My Param doc
 */
void virBufferEscapeSexpr(virBufferPtr buf, const char *format,
                          const char *str);
void virBufferEscapeRegex(virBufferPtr buf,
                          const char *format,
                          const char *str);
void virBufferEscapeSQL(virBufferPtr buf,
                        const char *format,
                        const char *str);
void virBufferEscapeShell(virBufferPtr buf, const char *str);

void virBufferURIEncodeString(virBufferPtr buf, const char *str);

#define virBufferAddLit(buf_, literal_string_) \
  virBufferAdd(buf_, "" literal_string_ "", sizeof(literal_string_) - 1)
/**
 * @brief  调整缩进
 * @param  buf              目标缓冲区
 * @param  indent           需要增加或者减少的缩进字符
 */
void virBufferAdjustIndent(virBufferPtr buf, int indent);
/**
 * @brief  设置锁进
 * @param  indent           My Param doc
 */
void virBufferSetIndent(virBufferPtr, int indent);
/**
 * @brief 获取当前缩紧
 * @param  buf              缓冲区
 * @return size_t           需要缩进大小
 */
size_t virBufferGetIndent(const virBuffer *buf);
/**
 * @brief  获取格式化需要的缩进大小
 * @param  buf              目标字符串
 * @return size_t 
 */
size_t virBufferGetEffectiveIndent(const virBuffer *buf);
/**
 * @brief  去除buf末尾字符串
 * @param  buf              buf
 * @param  trim             目标字符串
 */
void virBufferTrim(virBufferPtr buf, const char *trim);
/**
 * @brief  去除末尾字符数组
 * @param  buf              buf
 * @param  trim             目标字符串
 */
void virBufferTrimChars(virBufferPtr buf, const char *trim);
/**
 * @brief  去除末尾指定长度
 * @param  buf              缓冲区
 * @param  len              指定长度
 */
void virBufferTrimLen(virBufferPtr buf, int len);
/**
 * @brief  将str添加到buf中
 * @param  buf              缓冲区buf
 * @param  str              目标字符串
 */
void virBufferAddStr(virBufferPtr buf, const char *str);
