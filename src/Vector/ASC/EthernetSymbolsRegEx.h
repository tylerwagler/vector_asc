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

/** Ethernet Symbols */

#pragma once

#include <Vector/ASC/platform.h>

#include <Vector/ASC/CanSymbolsRegEx.h>

namespace Vector {
namespace ASC {

#define REGEX_Eth_Channel "([[:xdigit:]]{1,3})"
#define REGEX_Eth_Data "([[:xdigit:]]+)"
#define REGEX_Eth_DataLen "([[:xdigit:]]{1,4})"
#define REGEX_Eth_Dir "(Rx|Tx|TxRq)"
#define REGEX_Eth_Time "([[:digit:].]{3,})"
#define REGEX_Eth_ErrorCode "([[:xdigit:]]{1,2})"
#define REGEX_Eth_FrameChecksum "([[:xdigit:]]{8})"
#define REGEX_Afdx_BAG "([[:xdigit:]]+)"
#define REGEX_Afdx_Channel "([[:xdigit:]]{1,3})"
#define REGEX_Afdx_Data "([[:xdigit:]]+)"
#define REGEX_Afdx_DataLen "([[:xdigit:]]{1,4})"
#define REGEX_Afdx_Dir "(Rx|Tx|TxRq)"
#define REGEX_Afdx_EthChannel "([[:xdigit:]]{1,3})"
#define REGEX_Afdx_Flags "([[:xdigit:]]{1,5})"
#define REGEX_Afdx_Time "([[:digit:].]{3,})"

}
}
