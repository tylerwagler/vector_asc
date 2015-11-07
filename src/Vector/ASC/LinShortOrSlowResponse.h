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

/** LIN Short or slow response */
/* <Time> <Channel> <ID> <DLC> ShortOrSlowResponse: NumRespBytes = <NumberOfResponseBytes>
 * <D0>...<D8> SlowResponse = <IsSlowResponse> InterruptedByBreak = <ResponseWasInterruptedBy-
 * Break> SOF = <start of frame> BR = <baudrate> break = <SyncBreak> <SyncDel> (subId = <NAD>
 * <MessageId> <SupplierId>) EOH = <end of header> EOB = <T0> ... <T8> HBR = <header baudrate>
 * HSO = <stop bit offset in header> CSM = <checksum model> */
class LinShortOrSlowResponse : public Event
{
public:
    LinShortOrSlowResponse();
    virtual ~LinShortOrSlowResponse();

    /** Time */
    float time;

    /** Channel */
    std::string channel;

    /** ID */
    uint8_t id;

    /** DLC */
    uint8_t dlc;

    /** NumberOfResponseBytes */
    uint8_t numberOfResponseBytes;

    /** Data */
    uint8_t data[9];

    /** IsSlowResponse */
    bool isSlowResponse;

    /** ResponseWasInterruptedByBreak */
    bool responseWasInterruptedByBreak;

    /** start of frame (SOF) */
    float startOfFrame;

    /** baudrate (BR) */
    uint16_t baudrate;

    /** SyncBreak */
    uint32_t syncBreak;

    /** SyncDel */
    uint32_t syncDel;

    /** subId (NAD) */
    uint8_t subId;

    /** MessageId */
    uint8_t messageId;

    /** SupplierId */
    uint8_t supplierId;

    /** end of header (EOH) */
    float endOfHeader;

    /** end of byte (EOB) */
    float endOfByte[8];

    /** header baudrate (HBR) */
    float headerBaudrate;

    /** stop bit offset in header (HSO) */
    uint16_t stopBitOffsetInHeader;

    /** checksum model (CSM) */
    std::string checksumModel;

    /**
     * Parse function
     *
     * @param line Line as input
     * @return NULL if not parsed, otherwise valid object
     */
    static LinShortOrSlowResponse * parse(File & file, std::string & line);

    /**
     * Writes event to output stream.
     *
     * @param stream output stream
     */
    virtual void write(File & file, std::ostream & stream);
};

}
}
