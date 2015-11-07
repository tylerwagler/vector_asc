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

#include "Event.h"

namespace Vector {
namespace ASC {

/** LIN Receive Error */
/* <Time> <Channel> (<ID> <DLC>) RcvError: <description> (char = <offending byte>) (slave = <slave
 * id>, state = <state>) */
/* <Time> <Channel> (<ID> <DLC>) RcvError: <description> (char = <offending byte>) (slave = <slave
 * id>, state = <state>) StateReason = <StateReason> ShortError = <IsShortError> DlcTimeout = <Is-
 * DLCTimeout> HasDatabytes = <HasDatabytes> (<D0>...<D7>) SOF = <start of frame> BR =
 * <baudrate> break = <SyncBreak> <SyncDel> (subId = <NAD> <MessageId> <SupplierId>) (EOH =
 * <end of header>) (EOB = <T0> ... <T7>) */
/* <Time> <Channel> (<ID> <DLC>) RcvError: <description> (char = <offending byte>) (slave = <slave
 * id>, state = <state>) StateReason = <StateReason> ShortError = <IsShortError> DlcTimeout = <Is-
 * DLCTimeout> HasDatabytes = <HasDatabytes> (<D0>...<D7>) SOF = <start of frame> BR =
 * <baudrate> break = <SyncBreak> <SyncDel> (subId = <NAD> <MessageId> <SupplierId>) (EOH =
 * <end of header>) (EOB = <T0> ... <T7>) (RBR = <response baudrate>) */
/* <Time> <Channel> (<ID> <DLC>) RcvError: <description> (char = <offending byte>) (slave = <slave
 * id>, state = <state>) StateReason = <StateReason> ShortError = <IsShortError> DlcTimeout = <Is-
 * DLCTimeout> HasDatabytes = <HasDatabytes> (<D0>...<D7>) SOF = <start of frame> BR =
 * <baudrate> break = <SyncBreak> <SyncDel> (subId = <NAD> <MessageId> <SupplierId>) (EOH =
 * <end of header>) (EOB = <T0> ... <T7>) RBR = <response baudrate> HBR = <header baudrate> HSO =
 * <stop bit offset in header> RSO = <stop bit offset in response> */
/* <Time> <Channel> (<ID> <DLC>) RcvError: <description> (char = <offending byte>) (slave = <slave
 * id>, state = <state>) StateReason = <StateReason> ShortError = <IsShortError> DlcTimeout = <Is-
 * DLCTimeout> HasDatabytes = <HasDatabytes> (<D0>...<D7>) SOF = <start of frame> BR =
 * <baudrate> break = <SyncBreak> <SyncDel> (subId = <NAD> <MessageId> <SupplierId>) (EOH =
 * <end of header>) (EOB = <T0> ... <T7>) RBR = <response baudrate> HBR = <header baudrate> HSO =
 * <stop bit offset in header> RSO = <stop bit offset in response> CSM = <checksum model> */
class LinReceiveError : public Event
{
public:
    LinReceiveError();
    virtual ~LinReceiveError();

    /** Time */
    float time;

    /** Channel */
    std::string channel;

    /** ID */
    uint16_t id;

    /** DLC */
    uint8_t dlc;

    /** description */
    std::string description;

    /** offending byte */
    uint16_t offendingByte;

    /** slave id */
    uint8_t slaveId;

    /** state */
    uint8_t state;

    /** header time */
    uint8_t headerTime;

    /** full time */
    uint8_t fullTime;


    /** StateReason */
    uint8_t stateReason;

    /** IsShortError */
    bool isShortError;

    /** IsDLCTimeout */
    bool isDlcTimeout;

    /** HasDatabytes */
    bool hasDataBytes;

    /** Data */
    uint8_t data[8];

    /** start of frame (SOF) */
    float startOfFrame;

    /** baudrate (BR) */
    uint16_t baudrate;

    /** SyncBreak */
    uint32_t syncBreak;

    /** SyncDel */
    uint32_t syncDel;

    /** subId (NAD) */
    uint16_t subId;

    /** MessageId */
    uint16_t messageId;

    /** SupplierId */
    uint16_t supplierId;

    /** end of header (EOH) */
    float endOfHeader;

    /** T (EOB) */
    float endOfByte[8];


    /** response baudrate (RBR) */
    float responseBaudrate;


    /** header baudrate (HBR) */
    float headerBaudrate;

    /** stop bit offset in header (HSO) */
    uint16_t stopBitOffsetInHeader;

    /** stop bit offset in response (RSO) */
    uint16_t stopBitOffsetInResponse;


    /** checksum model (CSM) */
    std::string checksumModel;

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static LinReceiveError * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
