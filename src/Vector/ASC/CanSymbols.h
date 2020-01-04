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

/** CAN, Log & Trigger Symbols */

#pragma once

#include <Vector/ASC/platform.h>

#include <string>

namespace Vector {
namespace ASC {

/** absolute or relative time in seconds */
using Time = double;

/** Number of CAN channel. */
using Channel = uint8_t;

/** Numeric identifier */
using IdNum = uint32_t;

/** Symbolic identifier */
using IdSym = std::string;

/** Direction of transmission */
enum class Dir {
    /** Receive */
    Rx = 0,

    /** Transmit */
    Tx = 1,

    /** Transmit Request */
    TxRq = 2
};

/**
 * data length code
 *
 * @note In case DLC is greater 8, there are max. 8 data bytes written/read in.
 */
using Dlc = uint8_t;

/** Some special message flags that are written at the end of a logging line. */
struct MessageFlags {
    /**
     * Transmission Error (NERR signal).
     * Indicates whether a line has failed during a two-wire operation.
     * Especially available on Single-Wire mode.
     */
    bool te;

    /**
     * Wake-Up.
     * Indicates whether a message transmitted with overvoltage
     * with the purpose of waking up the CAN controller.
     */
    bool wu;
};

/** the number of received statistic events */
using StatNumber = uint32_t;

/** the busload in percent */
using StatPercent = double;

/** the pre trigger time in ms */
using PreTrigger = uint32_t;

/** the post trigger time in ms */
using PostTrigger = uint32_t;

/** the error message of the CAN error event */
enum class Error {
    /** unknown */
    Unknown = 0,

    /** chip status busoff */
    ChipStatusBusoff,

    /** chip status error passive */
    ChipStatusErrorPassive,

    /** chip status error active */
    ChipStatusErrorActive,

    /** rx queue overrun */
    RxQueueOverrun,

    /** chip status warning level */
    ChipStatusWarningLevel,

    /** hardware interface disconnected */
    HardwareInterfaceDisconnected
};

/** data byte */
using Dx = uint8_t;

/* WeekDay, Month, Date, FullTime, and Year are in struct tm */

/** a number which represents the variable data type */
enum class Svtype : uint8_t {
    /** Float */
    Float = 1,

    /** Int */
    Int = 2,

    /** String */
    String = 3,

    /** Float array */
    FloatArray = 4,

    /** Int array */
    IntArray = 5
};

/**
 * Message Duration [in nanoseconds]. Not including 3 Interframe
 * Space bit times and by Rx-message also not including 1 End-Of-Frame bit time
 */
using MessageDuration = uint32_t;

/** Total number of bits of the message including EOF and Interframe Space [in bits] */
using MessageLength = uint32_t;

/** Bit rate switch flag for CAN FD. Indicate bit rate switch is enabled or disabled. */
using Brs = bool;

/** Error state indicator flag for CAN FD. Indicate a transceiver is in error active or error passive mode. */
using Esi = bool;

/** Valid length of the message in bytes. */
using DataLength = uint8_t;

/** Bit timing information for CAN-FD frames. */
using BitTimingConfArb = uint32_t;

/** Bit timing information for CAN-FD frames. */
using BitTimingConfData = uint32_t;

}
}
