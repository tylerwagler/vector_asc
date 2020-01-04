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

#include <Vector/ASC/platform.h>

#include <Vector/ASC/CanSymbols.h>

namespace Vector {
namespace ASC {

/** Application Channel */
using EthChannel = uint8_t;

/**
 * Data of Ethernet packet. Starting with the target Ethernet MAC ID and ending with data or
 * padding bytes (without Ethernet packet CRC). Each data byte has two hex characters.
 */
using EthData = uint8_t;

/** Length of data in bytes (packet length). */
using EthDataLen = uint16_t;

/** @copydoc Dir */
using EthDir = Dir;

/** @copydoc Time */
using EthTime = Time;

/**
 * Error code for Rx errors
 *   - 1: Data length error
 *   - 2: Invalid CRC
 *   - 4: Invalid Data received
 *   - 8: Colission detected
 */
using EthErrorCode = uint8_t;

/** Frame checksum */
using EthFrameChecksum = uint32_t;

/** Measured time [µsec] since last frame on this VL */
using AfdxBag = uint32_t;

/** @copydoc EthChannel */
using AfdxChannel = EthChannel;

/**
 * Data of AFDX packet. Starting with the target Ethernet MAC ID and ending with data or
 * padding bytes (without Ethernet packet CRC) and AFDX-SeqNo.
 */
using AfdxData = uint8_t;

/** @copydoc EthDataLen */
using AfdxDataLen = EthDataLen;

/** @copydoc EthDir */
using AfdxDir = EthDir;

/** Underlying ETH-channel */
using AfdxEthChannel = EthChannel;

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
using AfdxFlags = uint16_t;

/** @copydoc EthTime */
using AfdxTime = EthTime;

}
}
