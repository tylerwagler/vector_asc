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

#include <string>
#include "CanSymbols.h"

namespace Vector {
namespace ASC {

/** @copydoc Time */
typedef Time FlexRayOldTime;

/** The number of the FlexRay channel. */
typedef char FlexRayOldChannel;

// Typ is used to select Event Class

/** Numeric identifier */
typedef uint16_t FlexRayOldId;

/** Current number of communication cycle */
typedef uint8_t FlexRayOldCycle;

/** Obsolete element not used in the V9 */
typedef bool FlexRayOldNm;

/** Sync frame Indicator */
typedef bool FlexRayOldSync;

/** HeaderCRC */
typedef uint16_t FlexRayOldHeaderCrc;

/** Database name of the frame */
typedef std::string FlexRayOldSymbolicName;

/** Payload length */
typedef uint8_t FlexRayOldDlc;

/** @copydoc Dx */
typedef Dx FlexRayOldDx;

/** See table below */
typedef uint16_t FlexRayOldFrameState;

/** FlexRay frame header */
typedef uint8_t FlexRayOldHeaderBitMask;

}
}
