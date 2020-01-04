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

/** LIN Symbols */

#pragma once

#include <Vector/ASC/platform.h>

#include <string>

#include <Vector/ASC/CanSymbols.h>

namespace Vector {
namespace ASC {

/** Event’s baudrate [in bits/sec] */
using LinBaudrateType = uint32_t;

/** The number of the LIN channel */
using LinChannel = uint16_t;

/** Checksum byte value */
using LinChecksum = uint8_t;

/** Expected checksum model for checksum value */
enum class LinChecksumModel : uint8_t {
    Unknown = 0,
    Classic = 1,
    Enhanced = 2,
    Error = 3
};

/**
 * CS Info event only: Textual description of checksum model. Possible values:
 *   - "Using enhanced checksum"
 *   - "Using classic checksum"
 */
enum class LinChecksumModelInfo : uint8_t {
    Enhanced = 1,
    Classic = 2,
};

/** @copydoc Dir */
using LinDir = Dir;

/** data length code */
using LinDlc = uint8_t;

/** Number of response bytes; can include the checksum. */
using LinNumberOfResponseBytes = uint8_t;

/**
 * Data byte values or
 * Response byte values; can include the checksum byte.
 */
using LinDx = uint8_t;

/** Textual description */
using LinDescription = std::string;

/**
 * LIN Dominant Signal only:
 *
 * Signal’s state. Possible values:
 *   - "detected"
 *   - "continuing"
 *   - "finished"
 */
enum class LinDomSigState : uint8_t {
    Detected = 1,
    Continuing = 2,
    Finished = 3
};

/**
 * LIN Dominant Signal only:
 * Length of the signal [in us]
 */
using LinDomSigLength = uint32_t;

/** Absolute timestamp indicating end of LIN frame [in seconds] */
using LinEndOfFrame = double;

/**
 * ETF Info event only:
 * Name of event-
 * triggered frame
 */
using LinEtfName = std::string;

/**
 * ETF Info event only:
 * Name of event-
 * triggered frame
 */
using LinEndOfHeader = double;

/** Duration of the entire frame [in bit times] */
using LinFullTime = uint32_t;

/**
 * LIN Receive Error only:
 * Flag indicating if there data byte values
 */
using LinHasDatabytes = bool;

/** Duration of the frame header [in bit times] */
using LinHeaderTime = uint32_t;

/** Event’s baudrate measured in header [in bits/sec as float value] */
using LinHeaderBaudrate = double;

/** Frame identifier or frame symbolic name */
using LinId = std::string;

/**
 * LIN Receive Error only:
 * Flag indicating if the error is a result of an attempt to resolve DLC
 */
using LinIsDlcTimeout = bool;

/**
 * LIN Receive Error only:
 * Specifies the detail level of the event
 */
using LinIsShortError = bool;

/** 16 bit message identifier */
using LinMessageId = uint16_t;

/** Node address */
using LinNad = uint8_t;

/**
 * LIN Receive Error only:
 * byte which caused the protocol violation
 */
using LinOffendingByte = uint8_t;

/** Event’s baudrate measured in response [in bits/sec] */
using LinResponseBaudrate = uint32_t;

/**
 * Flag indicating whether event has been simu-
 * lated by CANoe/CANalyzer
 */
using LinSimulated = bool;

/**
 * Schedule Mode Change event only:
 * Index of schedule table
 */
using LinScheduleTableIndex = uint8_t;

/** FSM Identifier */
using LinSlaveId = uint8_t;

/**
 * LIN Spike Signal only:
 * Length of the signal [in us]
 */
using LinSpikeLength = uint32_t;

/** Absolute timestamp indicating start of event [in seconds] */
using LinStartOfFrame = double;

/** Current state of the FSM */
using LinState = uint8_t;

/**
 * LIN Receive Error only:
 * The lower 4 bits indicate the LIN hardware state at the time the error has occurred,
 * while the upper 4 bits indicate the reason of the error
 *
 * Values for the state:
 *   - 0: Bus idle
 *   - 1: Waiting for SynchBreak
 *   - 2: Waiting for SynchField
 *   - 3: Waiting for frame ID
 *   - 4-12: Waiting for data byte or checksum byte depending on the frame length.
 *        E.g. value 4 for FrameLength=0, value 12 for FrameLength=8
 *   - 14: Consecutive event (i.e. event resulting from further data interpretation,
 *        after already notified error for first offending byte)
 *   - 15: Not expected event (i.e. not WakeupRequest) during sleepmode. Occurs for LIN
 *        hardware in Master mode only
 *
 * Values for the reason:
 *   - 0: Timeout
 *   - 1: Received an unexpected byte violating protocol.
 *        In this case, <offending byte> field contains its value
 *   - 2: Received a byte with framing error (with dominant stop bit).
 *        In this case, <offending byte> field contains its value
 *   - 3: Unexpected Break field
 *   - 4: Unidentified error
 */
using LinStateReason = uint8_t;

/** Early stop bit offset in frame header for UART timestamps [in ns] */
using LinStopBitOffsetInHeader = uint32_t;

/** Early stop bit offset in frame response for UART timestamps [in ns] */
using LinStopBitOffsetInResponse = uint32_t;

/** Supplier Identifier */
using LinSupplierId = uint16_t;

/** Break length [in ns] */
using LinSyncBreak = uint32_t;

/** Break delimiter length [in ns] */
using LinSyncDel = uint32_t;

/** Break length [in us and bit times] */
struct LinSyncBreakTime {
    uint32_t us;
    double bitTimes;
};

/** Break delimiter length [in us and bit times] */
struct LinSyncDelimiterTime {
    uint32_t us;
    double bitTimes;
};

/** Absolute timestamp indicating end of data byte [in seconds] */
using LinT = double;

/** Absolute or relative event’s time [in seconds] */
using LinTime = double;

/**
 * LIN Sync Error only:
 * Time intervals [in us] detected between the falling signal edges of the Sync field
 */
using LinTimeInterval = uint32_t;

/**
 * Wakeup event only:
 * Byte value used by wakeup frame
 */
using LinWakeupByte = uint8_t;

/**
 * Wakeup event only:
 * Code of wakeup length:
 *   - 0 - OK
 *   - 1 - too short
 *   - 2 - too long
 */
using LinWakeupLengthInfo = uint8_t;

/**
 * Short or slow response only:
 * Non-zero, if the response was too slow;
 * otherwise zero.
 */
using LinIsSlowResponse = bool;

/**
 * Short or slow response only:
 * Non-zero, if the response was interrupted
 * by a sync break; otherwise zero.
 */
using LinResponseWasInterruptedByBreak = bool;

/**
 * The width of a wakeup signal in microseconds.
 * Valid for LIN 2.x only.
 */
using LinWidth = uint16_t;

/**
 * Disturbance event only:
 * The type of disturbance that was executed.
 */
enum class LinDisturbanceType : uint8_t {
    /** dominant */
    Dominant = 1,

    /** recessive */
    Recessive = 2,

    /** header */
    Header = 3,

    /** bitstream */
    Bitstream = 4,

    /** variable bitstream */
    VariableBitstream = 5
};

/**
 * A 0-indexed byte index (i.e. 0 is the first byte, 9
 * is the checksum in a dlc 8 frame).
 *
 * If referring to a header, 0 is the sync field and 1 is the PID.
 */
using LinByteIndex = uint8_t;

/**
 * A 0-indexed bit index (i.e. 0 is the first data
 * bit, 8 is the stop bit, 9 is the first bit in interbyte space).
 */
using LinBitIndex = uint8_t;

/**
 * An offset in 1/16th bits into a bit specified with
 * <ByteIndex> and <BitIndex>
 */
using LinBitOffsetInSixteenthBits = uint8_t;

/**
 * Disturbance event only:
 * The length of a dominant or recessive disturbance in units of
 * 1/16th bits.
 */
using LinDisturbanceLengthInSixteenthBits = uint8_t;

/** A valid lin identifier or FF/255, if not applicable. */
using LinIdOrFf = uint8_t;

}
}
