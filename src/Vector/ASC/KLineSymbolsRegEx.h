/*
 * Copyright (C) 2014-2015 Tobias Lorenz.
 * Contact: tobias.lorenz@gmx.net
 *
 * This file is part of Tobias Lorenz's Toolkit.
 *
 * Commercial License Usage
 * Licensees holding valid commercial licenses may use this file in
 * accordance with the commercial license agreement provided with the
 * Software or, alternatively, in accordance with the terms contained in
 * a written agreement between you and Tobias Lorenz.
 *
 * GNU General Public License 3.0 Usage
 * Alternatively, this file may be used under the terms of the GNU
 * General Public License version 3.0 as published by the Free Software
 * Foundation and appearing in the file LICENSE.GPL included in the
 * packaging of this file.  Please review the following information to
 * ensure the GNU General Public License version 3.0 requirements will be
 * met: http://www.gnu.org/copyleft/gpl.html.
 */

/** K-Line Symbols */

#pragma once

#include <Vector/ASC/platform.h>

#include <Vector/ASC/CanSymbolsRegEx.h>

namespace Vector {
namespace ASC {

#define REGEX_KLine_time "([[:digit:].]{3,})"
#define REGEX_KLine_port "((COM|KL)[[:digit:]]{1,3})"
#define REGEX_KLine_direction "(Tx|Rx)"
#define REGEX_KLine_baudrate "([[:digit:]]{1,6})"
#define REGEX_KLine_source "([[:alnum:]]+)"
#define REGEX_KLine_destination "([[:alnum:]]+)"
#define REGEX_KLine_length "([[:digit:]]{1,4})"
#define REGEX_KLine_data "[[:xdigit:]]{1,3}"

}
}
