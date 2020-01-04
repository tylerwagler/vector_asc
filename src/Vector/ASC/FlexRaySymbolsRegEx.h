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

/** FlexRay Symbols */

#pragma once

#include <Vector/ASC/platform.h>

#include <Vector/ASC/CanSymbolsRegEx.h>

namespace Vector {
namespace ASC {

#define REGEX_FlexRayOld_Time "([[:digit:].]{3,})"
#define REGEX_FlexRayOld_Channel "Fr ([12*])"
// REGEX_FlexRay_Typ (V9|StartCycleEvent|ErrorFrame)
#define REGEX_FlexRayOld_ID "([[:xdigit:]]{1,4})"
#define REGEX_FlexRayOld_Cycle "([[:digit:]]{1,2})"
#define REGEX_FlexRayOld_NM "([01])"
#define REGEX_FlexRayOld_Sync "([01])"
#define REGEX_FlexRayOld_HeaderCRC "([[:xdigit:]]{1,4})"
#define REGEX_FlexRayOld_SymbolicName "([[:alnum:]_]+)"
#define REGEX_FlexRayOld_DLC "([[:xdigit:]]{1,3})"
#define REGEX_FlexRayOld_Dx "[[:xdigit:]]{1,3}"
#define REGEX_FlexRayOld_FrameState "([[:xdigit:]]{1,5})"
#define REGEX_FlexRayOld_HeaderBitMask "([[:xdigit:]]{1,3})"
#define REGEX_FlexRay_Time "([[:digit:].]{3,})"
#define REGEX_FlexRay_Dir "(Rx|Tx|TxRq)"

}
}
