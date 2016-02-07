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

#include "platform.h"

#include <string>

namespace Vector {
namespace ASC {

/** absolute or relative time in seconds */
typedef double Time;

/** Number of CAN channel. */
typedef uint8_t Channel;

/** Numeric identifier */
typedef uint32_t IdNum;

/** Symbolic identifier */
typedef std::string IdSym;

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
typedef uint8_t Dlc;

/** Some special message flags that are written at the end of a logging line. */
typedef struct {
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
} MessageFlags;

/** the number of received statistic events */
typedef uint32_t StatNumber;

/** the busload in percent */
typedef double StatPercent;

/** the pre trigger time in ms */
typedef uint32_t PreTrigger;

/** the post trigger time in ms */
typedef uint32_t PostTrigger;

/** the error message of the CAN error event */
typedef std::string Error;

/** data byte */
typedef uint8_t Dx;

/* WeekDay, Month, Date, FullTime, and Year are in struct tm */

/** a number which represents the variable data type */
enum Svtype : uint8_t {
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
typedef uint32_t MessageDuration;

/** Total number of bits of the message including EOF and Interframe Space [in bits] */
typedef uint32_t MessageLength;

/** Bit rate switch flag for CAN FD. Indicate bit rate switch is enabled or disabled. */
typedef bool Brs;

/** Error state indicator flag for CAN FD. Indicate a transceiver is in error active or error passive mode. */
typedef bool Esi;

/** Valid length of the message in bytes. */
typedef uint8_t DataLength;

/** Bit timing information for CAN-FD frames. */
typedef uint32_t BitTimingConfArb;

/** Bit timing information for CAN-FD frames. */
typedef uint32_t BitTimingConfData;

}
}
