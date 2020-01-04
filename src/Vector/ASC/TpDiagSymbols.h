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

/* TP/Diagnostics Symbols */

#pragma once

#include <Vector/ASC/platform.h>

#include <string>

namespace Vector {
namespace ASC {

/** CAN channel */
using TpDiagCanChannel = uint8_t;

/** Identify data transfer */
using TpDiagConnectionId = uint8_t;

/** Event type */
enum class TpDiagType : uint8_t {
    Info = 1,
    Warn = 2,
    Error = 3,
    Atom = 4,
    Data = 5
};

/** Source node */
using TpDiagSource = std::string;

/** Destination node */
using TpDiagDestination = std::string;

/** Number of bytes transferred */
using TpDiagLength = uint16_t;

/** Bytes transported within this CAN message */
using TpDiagTransportedBytes = uint8_t;

/** Sequence number */
using TpDiagSn = uint8_t;

/** Flow Control frame type */
enum class TpDiagFcType : uint8_t {
    /** CTS */
    Cts = 1,

    /** WT */
    Wt = 2,

    /** OVFLW */
    Ovflw = 3,

    /** Illegal Flow Status */
    IllegalFlowStatus = 4
};

/** Block size */
using TpDiagBs = uint8_t;

/** Minimum separation time */
using TpDiagStMin = uint8_t;

/** Standard trace time stamp */
using TpDiagTimestamp = double;

/** Unique identifier of the diagnostics description */
using TpDiagEcuQualifier = std::string;

/** Representation of the bytes sent to the ECU by the tester */
using TpDiagByteSequence = uint8_t;

}
}
