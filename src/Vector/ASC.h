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
#include "ASC/File.h"
#include "ASC/FileDate.h"
#include "ASC/FileBaseTimestamps.h"
#include "ASC/FileInternalEventsLogged.h"
#include "ASC/FileVersion.h"
#include "ASC/FileSplitInformation.h"
#include "ASC/FileComment.h"

/* CAN, Log & Trigger Events */
#include "ASC/CanMessageEvent.h"
#include "ASC/CanExtendedMessageEvent.h"
#include "ASC/CanRemoteFrameEvent.h"
#include "ASC/CanErrorFrame.h"
#include "ASC/CanBusStatisticsEvent.h"
#include "ASC/CanErrorEvent.h"
#include "ASC/CanOverloadFrameEvent.h"
#include "ASC/CanFdMessageEvent.h"
#include "ASC/CanFdExtendedMessageEvent.h"
#include "ASC/CanFdErrorFrame.h"
// CAN FD Bus Statistics Event
// CAN FD Overload Frame
#include "ASC/LogTriggerEvent.h"
#include "ASC/LogDirectStartEvent.h"
#include "ASC/LogDirectStopEvent.h"
#include "ASC/BeginTriggerblockEvent.h"
#include "ASC/EndTriggerblockEvent.h"
#include "ASC/EnvironmentVariablesEvent.h"
#include "ASC/SystemVariablesEvent.h"
#include "ASC/MacroSignalEvent.h"
#include "ASC/GpsEvent.h"
#include "ASC/CommentEvent.h"
#include "ASC/GlobalMarkerEvent.h"

/* Ethernet Events */
#include "ASC/EthernetPacket.h"
#include "ASC/EthernetStatus.h"
#include "ASC/EthernetRxError.h"
#include "ASC/AfdxPacket.h"

/* FlexRay Events */
#include "ASC/FlexRayOldMessageEvent.h"
#include "ASC/FlexRayOldStartCycleEvent.h"
#include "ASC/FlexRayMessageEvent.h"
#include "ASC/FlexRayStartCycleEvent.h"
#include "ASC/FlexRayStatusEvent.h"
#include "ASC/FlexRayErrorEvent.h"

/* K-Line Events */
#include "ASC/KLineByteEvent.h"
#include "ASC/KLineMessageEvent.h"

/* LIN Events */
#include "ASC/LinMessage.h"
#include "ASC/LinTransmissionError.h"
#include "ASC/LinReceiveError.h"
#include "ASC/LinSyncError.h"
#include "ASC/LinChecksumError.h"
#include "ASC/LinSpikeEvent.h"
#include "ASC/LinDominantSignal.h"
#include "ASC/LinBaudrate.h"
#include "ASC/LinDlcInfo.h"
#include "ASC/LinChecksumInfo.h"
#include "ASC/LinSchedulerModeChange.h"
#include "ASC/LinSlaveTimeout.h"
#include "ASC/LinEventTriggeredFrameInfo.h"
#include "ASC/LinStatisticInfo.h"
#include "ASC/LinShortOrSlowResponse.h"
#include "ASC/LinDisturbanceEvent.h"
#include "ASC/LinSleepMode.h"
#include "ASC/LinWakeupFrame.h"
#include "ASC/LinUnexpectedWakeup.h"

/* MOST Events */
#include "ASC/Most25ControlMessageNodeMode.h"
#include "ASC/Most25ControlMessageSpyMode.h"
#include "ASC/Most25Packet.h"
#include "ASC/MostLightLockEvent.h"
#include "ASC/MostSpecialRegisterEvent.h"
#include "ASC/MostCommonRegisterEvent.h"
#include "ASC/MostHwModeEvent.h"
#include "ASC/MostNetStateEvent.h"
#include "ASC/MostDataLostEvent.h"
#include "ASC/MostTriggerEvent.h"
#include "ASC/MostStatisticEvent.h"
#include "ASC/MostStatisticExtendedEvent.h"
#include "ASC/MostTxLight.h"
#include "ASC/MostStressEvent.h"
#include "ASC/Most25AllocTable.h"
#include "ASC/Most150ControlMessage.h"
#include "ASC/Most150ControlMessageFragment.h"
#include "ASC/Most150Packet.h"
#include "ASC/Most150PacketFragment.h"
#include "ASC/MostEthernetPacket.h"
#include "ASC/MostEthernetPacketFragment.h"
#include "ASC/MostSystemEvent.h"
#include "ASC/Most150AllocTable.h"
#include "ASC/Most50ControlMessage.h"
#include "ASC/Most50Packet.h"
#include "ASC/MostEcl.h"

/* TP/Diagnostics Events */
#include "ASC/TpDiagPrefix.h"
#include "ASC/TpDiagSingleFrame.h"
#include "ASC/TpDiagFirstFrame.h"
#include "ASC/TpDiagConsecutiveFrame.h"
#include "ASC/TpDiagFlowControlFrame.h"
#include "ASC/TpDiagRequest.h"
