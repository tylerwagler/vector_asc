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

#include <string>
#include "CanSymbols.h"

namespace Vector {
namespace ASC {

/** acknowledge state */
typedef uint8_t MostAckNack;

/** Size of allocation table. On MOST25 channels this value is always 60. */
typedef uint16_t MostAllocTableSize;

/** If Bit0 is set the event transports a channel list for each label. */
typedef uint8_t MostAt150EventModeFlags;

/** Size of MOST50/150 alloction data (number of word values) */
typedef uint16_t MostAt150Size;

/**
 * CRC acknowledge code
 *   - 0x00: No Response
 *   - 0x01: CRC error
 *   - 0x04: OK
 */
typedef uint8_t MostCack;

/** application channel */
typedef uint8_t MostChannel;

/** Number of coding errors */
typedef uint32_t MostCodingErrors;

/** CRC */
typedef uint16_t MostCrc;

/** 2 byte CRC */
typedef uint16_t MostCrc2;

/** 4 byte CRC */
typedef uint32_t MostCrc4;

/* Allocation Table byte */
typedef uint8_t MostDxAt;

/** target address */
typedef uint16_t MostDestAdr;

/** 48 bit target address */
typedef uint64_t MostDestMacAdr;

/** @copydoc Dir */
typedef Dir MostDir;

/** number of lost messages on Packet Data channel */
typedef uint16_t MostDlAsync;

/** number of lost message on Control channel */
typedef uint16_t MostDlCtrl;

/** data loss information */
typedef uint32_t MostDlInfo;

/** absolute time in seconds */
typedef double MostDlTime;

/** data byte */
typedef uint8_t MostDx;

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
typedef uint16_t MostFirstDataLen;

/** Frame Counter */
typedef uint32_t MostFrameCounter;

/**
 * Number of unreserved bytes for synchronous data
 * Max. 116 with SBC=29 for MOST50
 * Max. 372 with SBC=93 for MOST150
 */
typedef uint16_t MostFreeBytes;

/**
 * Number of transmitted user data bytes in fragments. These bytes were counted on bus.
 * @note The number of bytes saved in this event is stored in FirstDataLen.
 */
typedef uint32_t MostFrgDataLen;

/**
 * Announced user data length at start of transmission. In some cases (e.g.
 * sending to an invalid target address, receive buffer full of target device) the
 * transmission is terminated before all data bytes have been sent. Then the counted
 * number of bytes on bus is less than the announced data length (FrgDataLen
 * <FrgDataLenAnnonced>).
 * Due to rare and very specific bit errors (degrade of end termination byte)
 * FrgDataLen can also be greater than FrgDataLenAnnonced.
 */
typedef uint32_t MostFrgDataLenAnnounced;

/** bit field which denotes the valid data fields in fragment events */
typedef uint32_t MostFrgMask;

/** HW mode */
typedef uint8_t MostHwModeType;

/** bitmask of changed bits */
typedef uint8_t MostHwModeMask;

/**
 * Signal state:
 *   - 0x01 - Signal On + Lock
 *   - 0x02 - Signal Off (implies No Lock)
 *   - 0x03 - Signal On + No Lock
 *   - 0x10 - Stable Lock
 *   - 0x20 - Critical Unlock
 */
typedef uint8_t MostLlState;

/** number of data bytes */
typedef uint8_t MostMsg150Len;

/** number of data bytes */
typedef uint8_t MostMsg50Len;

/** new network state */
typedef uint8_t MostNetStateNew;

/** old network state */
typedef uint8_t MostNetStateOld;

/**
 * pre-emptive acknowledge
 *   - 0x00: No Response
 *   - 0x01: Buffer full
 *   - 0x04: OK
 */
typedef uint8_t MostPack;

/** message/packet index */
typedef uint8_t MostPindex;

/** number of data bytes */
typedef uint16_t MostPkt150Len;

/** arbitration byte */
typedef uint8_t MostPktArbitr;

/** number of Ethernet data bytes */
typedef uint16_t MostPktEthLen;

/** number of data bytes */
typedef uint16_t MostPktLen;

/** priority */
typedef uint8_t MostPktPrio;

/**
 * packet state
 *   - 0 for Rx
 *   - 0x40 - TxOk
 */
typedef uint8_t MostPktState;

/** transmission priority */
typedef uint8_t MostPriority;

/**
 * ID of chip
 *   - 1 - OS8104
 */
typedef uint8_t MostRegChip;

/** number of registers */
typedef uint8_t MostRegDataLen;

/** ID of register */
typedef uint8_t MostRegId;

/** address of register */
typedef uint16_t MostRegOffset;

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
typedef uint16_t MostRegValue;

/** reserved unsigned char */
typedef uint8_t MostRsvdUc;

/** reserved unsigned long */
typedef uint32_t MostRsvdUl;

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
typedef uint8_t MostRtype;

/** source address */
typedef uint16_t MostSourceAdr;

/** 48 bit source address */
typedef uint64_t MostSourceMacAdr;

/** message state */
typedef uint8_t MostState;

/** message state */
typedef uint16_t MostState2;

/** statistic value */
typedef uint32_t MostStatVal;

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
typedef uint8_t MostStressMode;

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
typedef uint16_t MostSysValue;

/** Previous value/state */
typedef uint16_t MostSysValueOld;

/** @copydoc Time */
typedef Time MostTime;

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
typedef uint8_t MostTrigHw;

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
typedef uint32_t MostTrigValue;

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
typedef uint16_t MostWx;

}
}
