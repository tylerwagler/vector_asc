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

#pragma once

#include <string>

namespace Vector {
namespace ASC {

/* CAN, Log & Trigger Symbols */

/** absolute or relative time in seconds */
typedef double Time;

/** Number of CAN channel. */
typedef uint16_t Channel;

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
enum class Svtype : uint32_t {
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

/* Ethernet Symbols */

/** Application Channel */
typedef uint16_t EthChannel;

/**
 * Data of Ethernet packet. Starting with the target Ethernet MAC ID and ending with data or
 * padding bytes (without Ethernet packet CRC). Each data byte has two hex characters.
 */
typedef uint8_t EthData;

/** Length of data in bytes (packet length). */
typedef uint16_t EthDataLen;

/** @copydoc Dir */
typedef Dir EthDir;

/** @copydoc Time */
typedef Time EthTime;

/**
 * Error code for Rx errors
 *   - 1: Data length error
 *   - 2: Invalid CRC
 *   - 4: Invalid Data received
 *   - 8: Colission detected
 */
typedef uint8_t EthErrorCode;

/** Frame checksum */
typedef uint32_t EthFrameChecksum;

/** Measured time [µsec] since last frame on this VL */
typedef uint32_t AfdxBag;

/** @copydoc EthChannel */
typedef EthChannel AfdxChannel;

/**
 * Data of AFDX packet. Starting with the target Ethernet MAC ID and ending with data or
 * padding bytes (without Ethernet packet CRC) and AFDX-SeqNo.
 */
typedef uint8_t AfdxData;

/** @copydoc EthDataLen */
typedef EthDataLen AfdxDataLen;

/** @copydoc EthDir */
typedef EthDir AfdxDir;

/** Underlying ETH-channel */
typedef EthChannel AfdxEthChannel;

/**
 * Flags signaling specific status and errors
 *
 * Status- and error flags using following bits with meaning:
 *   - Bit 0: Frame from line-B
 *   - Bit 1: Packet is redundant
 *   - Bit 2: Frame is a fragment only
 *   - Bit 3: Frame is already reassembled
 *   - Bit 4: Packet is not a valid AFDX frame
 *   - Bit 5: AFDX-SequenceNo is invalid
 *   - Bit 6: Redundancy timeout violated
 *   - Bit 7: Redundancy error encountered
 *   - Bit 8: A / B interface mismatch
 *   - Bit 11: Fragmentation error
 */
typedef uint16_t AfdxFlags;

/** @copydoc EthTime */
typedef EthTime AfdxTime;

/* FlexRay Symbols */

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

/* K-Line Symbols */

/** Time of reception of the bytes, i.e. the end of a byte sequence */
typedef Time KLineTime;

/** COMn for serial port n, or KLn for LINcab n */
typedef std::string KLinePort;

/** Were the bytes sent or received? */
typedef Dir KLineDirection;

/** Rate the data was transferred on */
typedef uint32_t KLineBaudrate;

/** Source address */
typedef std::string KLineSource;

/** Destination address */
typedef std::string KLineDestination;

/** Number of bytes transferred */
typedef uint16_t KLineLength;

/** Bytes transported within this CAN message */
typedef uint8_t KLineData;

/* LIN Symbols */

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
typedef int LinDlc;

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
typedef double LinHeaderTime;

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

/* MOST Symbols */

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
typedef uint16_t MostFrameCounter;

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
typedef uint8_t MostHwMode;

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

/* TP/Diagnostics Symbols */

/** CAN channel */
typedef uint8_t TpDiagCanChannel;

/** Identify data transfer */
typedef uint8_t TpDiagConnectionId;

/** Event type */
enum class TpDiagType : uint8_t {
    Info = 1,
    Warn = 2,
    Error = 3,
    Atom = 4,
    Data = 5
};

/** Source node */
typedef std::string TpDiagSource;

/** Destination node */
typedef std::string TpDiagDestination;

/** Number of bytes transferred */
typedef uint16_t TpDiagLength;

/** Bytes transported within this CAN message */
typedef uint8_t TpDiagTransportedBytes;

/** Sequence number */
typedef uint8_t TpDiagSn;

/** Flow Control frame type */
enum class TpDiagFcType : uint8_t {
    /** CTS */
    Cts = 1,

    /** WT */
    Wt = 2,

    /** OVFLW */
    Ovflw = 3
};

/** Block size */
typedef uint8_t TpDiagBs;

/** Minimum separation time */
typedef uint8_t TpDiagStMin;

/** Standard trace time stamp */
typedef double TpDiagTimestamp;

/** Unique identifier of the diagnostics description */
typedef std::string TpDiagEcuQualifier;

/** Representation of the bytes sent to the ECU by the tester */
typedef uint8_t TpDiagByteSequence;

}
}
