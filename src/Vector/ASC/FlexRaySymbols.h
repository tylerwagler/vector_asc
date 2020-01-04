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

#include <string>

#include <Vector/ASC/CanSymbols.h>

namespace Vector {
namespace ASC {

/** @copydoc Time */
using FlexRayOldTime = Time;

/** The number of the FlexRay channel. */
using FlexRayOldChannel = char;

// Typ is used to select Event Class

/** Numeric identifier */
using FlexRayOldId = uint16_t;

/** Current number of communication cycle */
using FlexRayOldCycle = uint8_t;

/** Obsolete element not used in the V9 */
using FlexRayOldNm = bool;

/** Sync frame Indicator */
using FlexRayOldSync = bool;

/** HeaderCRC */
using FlexRayOldHeaderCrc = uint16_t;

/** Database name of the frame */
using FlexRayOldSymbolicName = std::string;

/** Payload length */
using FlexRayOldDlc = uint8_t;

/** @copydoc Dx */
using FlexRayOldDx = Dx;

/** See table below */
using FlexRayOldFrameState = uint16_t;

/** FlexRay frame header */
using FlexRayOldHeaderBitMask = uint8_t;

}
}
