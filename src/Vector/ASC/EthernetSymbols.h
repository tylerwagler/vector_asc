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

/** Ethernet Symbols */

#pragma once

#include <string>
#include "CanSymbols.h"

namespace Vector {
namespace ASC {

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

}
}
