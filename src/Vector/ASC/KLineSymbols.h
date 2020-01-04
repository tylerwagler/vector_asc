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

#include <string>

#include <Vector/ASC/CanSymbols.h>

namespace Vector {
namespace ASC {

/** Time of reception of the bytes, i.e. the end of a byte sequence */
using KLineTime = Time;

/** COMn for serial port n, or KLn for LINcab n */
using KLinePort = std::string;

/** Were the bytes sent or received? */
using KLineDirection = Dir;

/** Rate the data was transferred on */
using KLineBaudrate = uint32_t;

/** Source address */
using KLineSource = std::string;

/** Destination address */
using KLineDestination = std::string;

/** Number of bytes transferred */
using KLineLength = uint16_t;

/** Bytes transported within this CAN message */
using KLineData = uint8_t;

}
}
