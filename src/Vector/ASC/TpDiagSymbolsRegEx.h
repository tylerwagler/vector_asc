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

/** TP/Diagnostics Symbols */

#pragma once

#include <Vector/ASC/platform.h>

#include <Vector/ASC/CanSymbolsRegEx.h>

namespace Vector {
namespace ASC {

#define REGEX_TPDiag_CANChannel "([[:digit:]]{1,2})"
#define REGEX_TPDiag_connectionId "([[:xdigit:]]{2})"
#define REGEX_TPDiag_type "(Info|Warn|Error|Atom|Data)"
#define REGEX_TPDiag_source "([[:alnum:]_<>]+)"
#define REGEX_TPDiag_destination "([[:alnum:]_<>]+)"
#define REGEX_TPDiag_length "([[:xdigit:]]{2,4})"
#define REGEX_TPDiag_transportedBytes "((" REGEX_WS "[[:xdigit:]]+)*)"
#define REGEX_TPDiag_SN "([[:xdigit:]]{1,4})"
#define REGEX_TPDiag_FCType "(CTS|WT|OVFLW)"
#define REGEX_TPDiag_BS "([[:xdigit:]]{1,4})"
#define REGEX_TPDiag_STmin "([[:xdigit:]]{1,4})"
#define REGEX_TPDiag_timestamp "([[:digit:].]{3,})"
#define REGEX_TPDiag_ECUQualifier "([[:alnum:]_]+)"
#define REGEX_TPDiag_byteSequence "((" REGEX_WS "[[:xdigit:]]+)*)"

}
}
