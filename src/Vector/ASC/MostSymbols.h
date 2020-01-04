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

/** MOST Symbols */

#pragma once

#include <Vector/ASC/platform.h>

#include <Vector/ASC/CanSymbols.h>

namespace Vector {
namespace ASC {

/** acknowledge state */
using MostAckNack = uint8_t;

/** Size of allocation table. On MOST25 channels this value is always 60. */
using MostAllocTableSize = uint16_t;

/** If Bit0 is set the event transports a channel list for each label. */
using MostAt150EventModeFlags = uint8_t;

/** Size of MOST50/150 alloction data (number of word values) */
using MostAt150Size = uint16_t;

/**
 * CRC acknowledge code
 *   - 0x00: No Response
 *   - 0x01: CRC error
 *   - 0x04: OK
 */
using MostCAck = uint8_t;

/** application channel */
using MostChannel = uint8_t;

/** Number of coding errors */
using MostCodingErrors = uint32_t;

/** CRC */
using MostCrc = uint16_t;

/** 2 byte CRC */
using MostCrc2 = uint16_t;

/** 4 byte CRC */
using MostCrc4 = uint32_t;

/** Allocation Table byte values */
using MostDxAt = uint8_t;

/** target address */
using MostDestAdr = uint16_t;

/** 48 bit target address */
using MostDestMacAdr = uint64_t;

/** @copydoc Dir */
using MostDir = Dir;

/** number of lost messages on Packet Data channel */
using MostDlAsync = uint16_t;

/** number of lost message on Control channel */
using MostDlCtrl = uint16_t;

/** data loss information */
using MostDlInfo = uint32_t;

/** absolute time in seconds */
using MostDlTime = double;

/** data byte */
using MostDx = uint8_t;

enum class MostEclMode : uint8_t {
    /** discrete */
    Discrete = 0,

    /** sequence */
    Sequence = 1
};

enum class MostEclState : uint8_t {
    /** EclMode = 0: line low */
    LineLow = 0,

    /** EclMode = 0: line high */
    LineHigh = 1,

    /** EclMode = 1: sequence stopped */
    SequenceStopped = 0,

    /** EclMode = 1: sequence started */
    SequenceStarted = 1
};

/**
 * Number of bytes stored in
 * the payload field.
 *
 * @note In order to limit the size of this event not all
 * counted bytes (s. FrgDataLen) on bus will be
 * stored in the payload of the logging event.
 */
using MostFirstDataLen = uint8_t;

/** Frame Counter */
using MostFrameCounter = uint32_t;

/**
 * Number of unreserved bytes for synchronous data
 * Max. 116 with SBC=29 for MOST50
 * Max. 372 with SBC=93 for MOST150
 */
using MostFreeBytes = uint16_t;

/**
 * Number of transmitted user data bytes in fragments. These bytes were counted on bus.
 * @note The number of bytes saved in this event is stored in FirstDataLen.
 */
using MostFrgDataLen = uint32_t;

/**
 * Announced user data length at start of transmission. In some cases (e.g.
 * sending to an invalid target address, receive buffer full of target device) the
 * transmission is terminated before all data bytes have been sent. Then the counted
 * number of bytes on bus is less than the announced data length (FrgDataLen
 * <FrgDataLenAnnonced>).
 * Due to rare and very specific bit errors (degrade of end termination byte)
 * FrgDataLen can also be greater than FrgDataLenAnnonced.
 */
using MostFrgDataLenAnnounced = uint32_t;

/** bit field which denotes the valid data fields in fragment events */
using MostFrgMask = uint32_t;

/** HW mode */
using MostHwModeType = uint8_t;

/** bitmask of changed bits */
using MostHwModeMask = uint8_t;

/**
 * Signal state:
 *   - 0x01 - Signal On + Lock
 *   - 0x02 - Signal Off (implies No Lock)
 *   - 0x03 - Signal On + No Lock
 *   - 0x10 - Stable Lock
 *   - 0x20 - Critical Unlock
 */
using MostLlState = uint8_t;

/** number of data bytes */
using MostMsg150Len = uint8_t;

/** number of data bytes */
using MostMsg50Len = uint8_t;

/** new network state */
using MostNetStateNew = uint8_t;

/** old network state */
using MostNetStateOld = uint8_t;

/**
 * pre-emptive acknowledge
 *   - 0x00: No Response
 *   - 0x01: Buffer full
 *   - 0x04: OK
 */
using MostPAck = uint8_t;

/** message/packet index */
using MostPIndex = uint8_t;

/** number of data bytes */
using MostPkt150Len = uint16_t;

/** arbitration byte */
using MostPktArbitr = uint8_t;

/** number of Ethernet data bytes */
using MostPktEthLen = uint16_t;

/** number of data bytes */
using MostPktLen = uint16_t;

/** priority */
using MostPktPrio = uint8_t;

/**
 * packet state
 *   - 0 for Rx
 *   - 0x40 - TxOk
 */
using MostPktState = uint8_t;

/** transmission priority */
using MostPriority = uint8_t;

/**
 * ID of chip
 *   - 1 - OS8104
 */
using MostRegChip = uint8_t;

/** number of registers */
using MostRegDataLen = uint8_t;

/** ID of register */
using MostRegId = uint8_t;

/** address of register */
using MostRegOffset = uint16_t;

/** type of register event */
enum class MostRegSubType : uint8_t {
    /** unspecified (or HW does not support sub types) */
    Unspecified = 0,

    /** notification on register change (spontaneous) */
    Notify = 1,

    /** request of a register read operation */
    ReadRequest = 2,

    /** request of a register write operation */
    WriteRequest = 3,

    /** result of a register read operation */
    ReadResult = 4,

    /** result of a register write operation */
    WriteResult = 5,

    /** register read operation failed */
    ReadFailed = 6,

    /** register write operation failed */
    WriteFailed = 7
};

/** register value */
using MostRegValue = uint16_t;

/** reserved unsigned char */
using MostRsvdUc = uint8_t;

/** reserved unsigned long */
using MostRsvdUl = uint32_t;

/**
 * message sub type
 *   - 0 - Normal
 *   - 1 - RemoteRead
 *   - 2-- RemoteWrite
 *   - 3 - Alloc
 *   - 4 - Dealloc
 *   - 5 - GetSource
 *   - >5 - not used so far
 */
using MostRType = uint8_t;

/** source address */
using MostSourceAdr = uint16_t;

/** 48 bit source address */
using MostSourceMacAdr = uint64_t;

/** message state */
using MostState = uint8_t;

/** message state */
using MostState2 = uint16_t;

/** statistic value */
using MostStatVal = uint32_t;

/**
 * Stress mode of HW interface:
 *   - 1 - Light
 *   - 2 - Lock
 *   - 3 - Busload Ctrl
 *   - 4 - Busload Async
 *   - 5 - Rx Buffer Ctrl
 *   - 6 - TxLight power
 *   - 7 - Bypass toggling
 *   - 8 - SystemLock flag usage
 *   - 9 - Shutdown flag usage
 *   - 10 - Rx Buffer Async
 */
using MostStressMode = uint8_t;

/** State of Stress mode */
enum class MostStressState : uint8_t {
    /** Stopped */
    Stopped = 0,

    /** Started */
    Started = 1,
};

/** Identification of transported data (enumeration) */
enum class MostSysId : uint8_t {
    /** System Lock (MOST150) */
    SystemLock = 1,

    /** Shutdown flag (MOST150) */
    ShutdownFlag = 2,

    /** Shutdown reason (MOST150) */
    ShutdownReason = 3
};

/** System value/state */
using MostSysValue = uint16_t;

/** Previous value/state */
using MostSysValueOld = uint16_t;

/** @copydoc Time */
using MostTime = Time;

enum class MostTransferType : uint8_t {
    /**
     * Node: MOST transceiver reported the message
     * (either due to a successful reception or as
     * acknowledgment for a transmit request).
     */
    Node = 1,

    /**
     * Spy: Message was reported by the network
     * spy. The Spy sees all messages independently of the
     * destination address.
     * @note this information is not transferred on the bus.
     */
    Spy = 2,
};

/**
 * HW that generated the trigger event
 *   - 0 - unknown
 *   - 1 - Optolyzer
 *   - 2 - reserved
 *   - 3 - reserved
 *   - 4 - VN2600/VN2610
 *   - 5 - OptoLyzer OL3150o
 *   - 6 - VN2640
 *   - 7 - OptoLyzer OL3050e
 *   - 8 - SMSC PCI 50
 *   - 9 - MOCCAcompact50e
 */
using MostTrigHw = uint8_t;

/** trigger mode */
enum class MostTrigMode : uint8_t {
    /** unknown */
    Unknown = 0,

    /** synchronization master */
    SynchronizationMaster = 1,

    /** synchronization slave */
    SynchronizationSlave = 2
};

/** value of IO register */
using MostTrigValue = uint32_t;

/** Light/signal state at output */
enum class MostTxLightState : uint8_t {
    /** TxLight/Signal off */
    Off = 0,

    /** TxLight/Signal enabled */
    Enabled = 1,

    /** TxLight/Signal forced on */
    ForcedOn = 2
};

/** data word */
using MostWx = uint16_t;

}
}
