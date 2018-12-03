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

/*
 * The implementation is based on:
 * - CAN_LIN_TRIGGER_ASC_Format.pdf, Version 1.3.0, 2013-04-11
 * - Ethernet_ASC_Format.pdf, Version 1.2.0, 2013-04-23
 * - FlexRay_ASC_Format.pdf, Version 1.4.2, 2009-09-08
 * - KLine_ASC_Format.pdf, Version 1.0, 2011-02-02
 * - LIN_ASC_Format.pdf, Version 1.0.17, 2010-10-27
 * - MOST_ASC_Format.pdf, Version 1.8.7, 2013-03-20
 * - TPDiag_ASC_Format.pdf, Version 1.1, 2009-05-18
 */

#pragma once

/* File */
#include <Vector/ASC/File.h>
#include <Vector/ASC/FileDate.h>
#include <Vector/ASC/FileBaseTimestamps.h>
#include <Vector/ASC/FileInternalEventsLogged.h>
#include <Vector/ASC/FileVersion.h>
#include <Vector/ASC/FileSplitInformation.h>
#include <Vector/ASC/FileComment.h>

/* CAN, Log & Trigger Events */
#include <Vector/ASC/CanMessage.h>
#include <Vector/ASC/CanExtendedMessage.h>
#include <Vector/ASC/CanRemoteFrame.h>
#include <Vector/ASC/CanErrorFrame.h>
#include <Vector/ASC/CanBusStatistics.h>
#include <Vector/ASC/CanError.h>
#include <Vector/ASC/CanOverloadFrame.h>
#include <Vector/ASC/CanFdMessage.h>
#include <Vector/ASC/CanFdExtendedMessage.h>
#include <Vector/ASC/CanFdErrorFrame.h>
// CAN FD Bus Statistics
// CAN FD Overload Frame
#include <Vector/ASC/LogTrigger.h>
#include <Vector/ASC/LogDirectStart.h>
#include <Vector/ASC/LogDirectStop.h>
#include <Vector/ASC/BeginTriggerblock.h>
#include <Vector/ASC/EndTriggerblock.h>
#include <Vector/ASC/EnvironmentVariables.h>
#include <Vector/ASC/SystemVariables.h>
#include <Vector/ASC/MacroSignal.h>
#include <Vector/ASC/Gps.h>
#include <Vector/ASC/Comment.h>
#include <Vector/ASC/GlobalMarker.h>

/* Ethernet Events */
#include <Vector/ASC/EthernetPacket.h>
#include <Vector/ASC/EthernetStatus.h>
#include <Vector/ASC/EthernetRxError.h>
#include <Vector/ASC/AfdxPacket.h>

/* FlexRay Events */
#include <Vector/ASC/FlexRayOldMessage.h>
#include <Vector/ASC/FlexRayOldStartCycle.h>
#include <Vector/ASC/FlexRayMessage.h>
#include <Vector/ASC/FlexRayStartCycle.h>
#include <Vector/ASC/FlexRayStatus.h>
#include <Vector/ASC/FlexRayError.h>

/* K-Line Events */
#include <Vector/ASC/KLineByte.h>
#include <Vector/ASC/KLineMessage.h>

/* LIN Events */
#include <Vector/ASC/LinMessage.h>
#include <Vector/ASC/LinTransmissionError.h>
#include <Vector/ASC/LinReceiveError.h>
#include <Vector/ASC/LinSyncError.h>
#include <Vector/ASC/LinChecksumError.h>
#include <Vector/ASC/LinSpike.h>
#include <Vector/ASC/LinDominantSignal.h>
#include <Vector/ASC/LinBaudrate.h>
#include <Vector/ASC/LinDlcInfo.h>
#include <Vector/ASC/LinChecksumInfo.h>
#include <Vector/ASC/LinSchedulerModeChange.h>
#include <Vector/ASC/LinSlaveTimeout.h>
#include <Vector/ASC/LinEventTriggeredFrameInfo.h>
#include <Vector/ASC/LinStatisticInfo.h>
#include <Vector/ASC/LinShortOrSlowResponse.h>
#include <Vector/ASC/LinDisturbance.h>
#include <Vector/ASC/LinSleepMode.h>
#include <Vector/ASC/LinWakeupFrame.h>
#include <Vector/ASC/LinUnexpectedWakeup.h>

/* MOST Events */
#include <Vector/ASC/Most25ControlMessageNodeMode.h>
#include <Vector/ASC/Most25ControlMessageSpyMode.h>
#include <Vector/ASC/Most25Packet.h>
#include <Vector/ASC/MostLightLock.h>
#include <Vector/ASC/MostSpecialRegister.h>
#include <Vector/ASC/MostCommonRegister.h>
#include <Vector/ASC/MostHwMode.h>
#include <Vector/ASC/MostNetState.h>
#include <Vector/ASC/MostDataLost.h>
#include <Vector/ASC/MostTrigger.h>
#include <Vector/ASC/MostStatistic.h>
#include <Vector/ASC/MostStatisticExtended.h>
#include <Vector/ASC/MostTxLight.h>
#include <Vector/ASC/MostStress.h>
#include <Vector/ASC/Most25AllocTable.h>
#include <Vector/ASC/Most150ControlMessage.h>
#include <Vector/ASC/Most150ControlMessageFragment.h>
#include <Vector/ASC/Most150Packet.h>
#include <Vector/ASC/Most150PacketFragment.h>
#include <Vector/ASC/MostEthernetPacket.h>
#include <Vector/ASC/MostEthernetPacketFragment.h>
#include <Vector/ASC/MostSystem.h>
#include <Vector/ASC/Most150AllocTable.h>
#include <Vector/ASC/Most50ControlMessage.h>
#include <Vector/ASC/Most50Packet.h>
#include <Vector/ASC/MostEcl.h>

/* TP/Diagnostics Events */
#include <Vector/ASC/TpSingleFrame.h>
#include <Vector/ASC/TpFirstFrame.h>
#include <Vector/ASC/TpConsecutiveFrame.h>
#include <Vector/ASC/TpFlowControlFrame.h>
#include <Vector/ASC/DiagRequest.h>

/* undocumented events */
#include <Vector/ASC/StartOfMeasurement.h>
#include <Vector/ASC/Unknown.h>
