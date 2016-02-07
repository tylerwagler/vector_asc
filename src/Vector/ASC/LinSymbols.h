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

#include "platform.h"

#include <string>

#include "CanSymbols.h"

#include "vector_asc_export.h"

namespace Vector {
namespace ASC {

/** Event’s baudrate [in bits/sec] */
typedef uint32_t LinBaudrateType;

/** The number of the LIN channel */
typedef uint16_t LinChannel;

/** Checksum byte value */
typedef uint8_t LinChecksum;

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
typedef Dir LinDir;

/** data length code */
typedef uint8_t LinDlc;

/** Number of response bytes; can include the checksum. */
typedef uint8_t LinNumberOfResponseBytes;

/**
 * Data byte values or
 * Response byte values; can include the checksum byte.
 */
typedef uint8_t LinDx;

/** Textual description */
typedef std::string LinDescription;

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
typedef uint32_t LinDomSigLength;

/** Absolute timestamp indicating end of LIN frame [in seconds] */
typedef double LinEndOfFrame;

/**
 * ETF Info event only:
 * Name of event-
 * triggered frame
 */
typedef std::string LinEtfName;

/**
 * ETF Info event only:
 * Name of event-
 * triggered frame
 */
typedef double LinEndOfHeader;

/** Duration of the entire frame [in bit times] */
typedef uint32_t LinFullTime;

/**
 * LIN Receive Error only:
 * Flag indicating if there data byte values
 */
typedef bool LinHasDatabytes;

/** Duration of the frame header [in bit times] */
typedef uint32_t LinHeaderTime;

/** Event’s baudrate measured in header [in bits/sec as float value] */
typedef double LinHeaderBaudrate;

/** Frame identifier or frame symbolic name */
typedef std::string LinId;

/**
 * LIN Receive Error only:
 * Flag indicating if the error is a result of an attempt to resolve DLC
 */
typedef bool LinIsDlcTimeout;

/**
 * LIN Receive Error only:
 * Specifies the detail level of the event
 */
typedef bool LinIsShortError;

/** 16 bit message identifier */
typedef uint16_t LinMessageId;

/** Node address */
typedef uint8_t LinNad;

/**
 * LIN Receive Error only:
 * byte which caused the protocol violation
 */
typedef uint8_t LinOffendingByte;

/** Event’s baudrate measured in response [in bits/sec] */
typedef uint32_t LinResponseBaudrate;

/**
 * Flag indicating whether event has been simu-
 * lated by CANoe/CANalyzer
 */
typedef bool LinSimulated;

/**
 * Schedule Mode Change event only:
 * Index of schedule table
 */
typedef uint8_t LinScheduleTableIndex;

/** FSM Identifier */
typedef uint8_t LinSlaveId;

/**
 * LIN Spike Signal only:
 * Length of the signal [in us]
 */
typedef uint32_t LinSpikeLength;

/** Absolute timestamp indicating start of event [in seconds] */
typedef double LinStartOfFrame;

/** Current state of the FSM */
typedef uint8_t LinState;

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
typedef uint8_t LinStateReason;

/** Early stop bit offset in frame header for UART timestamps [in ns] */
typedef uint32_t LinStopBitOffsetInHeader;

/** Early stop bit offset in frame response for UART timestamps [in ns] */
typedef uint32_t LinStopBitOffsetInResponse;

/** Supplier Identifier */
typedef uint16_t LinSupplierId;

/** Break length [in ns] */
typedef uint32_t LinSyncBreak;

/** Break delimiter length [in ns] */
typedef uint32_t LinSyncDel;

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
typedef double LinT;

/** Absolute or relative event’s time [in seconds] */
typedef double LinTime;

/**
 * LIN Sync Error only:
 * Time intervals [in us] detected between the falling signal edges of the Sync field
 */
typedef uint32_t LinTimeInterval;

/**
 * Wakeup event only:
 * Byte value used by wakeup frame
 */
typedef uint8_t LinWakeupByte;

/**
 * Wakeup event only:
 * Code of wakeup length:
 *   - 0 - OK
 *   - 1 - too short
 *   - 2 - too long
 */
typedef uint8_t LinWakeupLengthInfo;

/**
 * Short or slow response only:
 * Non-zero, if the response was too slow;
 * otherwise zero.
 */
typedef bool LinIsSlowResponse;

/**
 * Short or slow response only:
 * Non-zero, if the response was interrupted
 * by a sync break; otherwise zero.
 */
typedef bool LinResponseWasInterruptedByBreak;

/**
 * The width of a wakeup signal in microseconds.
 * Valid for LIN 2.x only.
 */
typedef uint16_t LinWidth;

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
typedef uint8_t LinByteIndex;

/**
 * A 0-indexed bit index (i.e. 0 is the first data
 * bit, 8 is the stop bit, 9 is the first bit in interbyte space).
 */
typedef uint8_t LinBitIndex;

/**
 * An offset in 1/16th bits into a bit specified with
 * <ByteIndex> and <BitIndex>
 */
typedef uint8_t LinBitOffsetInSixteenthBits;

/**
 * Disturbance event only:
 * The length of a dominant or recessive disturbance in units of
 * 1/16th bits.
 */
typedef uint8_t LinDisturbanceLengthInSixteenthBits;

/** A valid lin identifier or FF/255, if not applicable. */
typedef uint8_t LinIdOrFf;

}
}
