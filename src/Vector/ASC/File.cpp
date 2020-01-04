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

#include <cstring>

#include <Vector/ASC.h>

namespace Vector {
namespace ASC {

File::~File() {
    delete scanner;
    scanner = nullptr;
}

void File::open(const char * filename, OpenMode openMode) {
    this->openMode = openMode;
    this->endOfFile = false;

    switch (this->openMode) {
    case OpenMode::Read:
        /* open file for reading */
        file.open(filename, std::ios_base::in);

        /* create scanner */
        delete scanner;
        try {
            scanner = new ascFlexLexer(&file);
        } catch (std::bad_alloc & ba) {
            close(); // delete scanner and close file
        }

        break;
    case OpenMode::Write:
        /* open file for writing */
        file.open(filename, std::ios_base::out);
        break;
    }
}

void File::open(const std::string & filename, OpenMode openMode) {
    open(filename.c_str(), openMode);
}

bool File::is_open() const {
    return file.is_open();
}

void File::close() {
    /* delete scanner */
    delete scanner;
    scanner = nullptr;

    /* close file */
    file.close();
}

bool File::eof() {
    return endOfFile;
}

Event * File::read() {
    /* safety check */
    if (scanner == nullptr)
        return nullptr;

    /* scan line */
    int eventType = scanner->yylex();
    std::string line = scanner->YYText();

    /* remove windows line ending */
    if (line.back() == '\r')
        line.pop_back();

    switch (eventType) {
    case Event::EventType::Default:
        endOfFile = true;
        break;

    /* unknown */
    case Event::EventType::Unknown: {
        Unknown * unknown = new Unknown();
        unknown->line = line;
        return unknown;
    }

    /* File */
    case Event::EventType::FileDate: {
        FileDate * fileDate = FileDate::read(*this, line);
        if (fileDate) {
            date = fileDate->date;
            language = fileDate->language;
        }
        return fileDate;
    }
    case Event::EventType::FileBaseTimestamps: {
        FileBaseTimestamps * fileBaseTimestamps = FileBaseTimestamps::read(*this, line);
        if (fileBaseTimestamps) {
            base = fileBaseTimestamps->base;
            timestamps = fileBaseTimestamps->timestamps;
        }
        return fileBaseTimestamps;
    }
    case Event::EventType::FileInternalEventsLogged: {
        FileInternalEventsLogged * fileInternalEventsLogged = FileInternalEventsLogged::read(*this, line);
        if (fileInternalEventsLogged)
            internalEventsLogged = fileInternalEventsLogged->internalEventsLogged;
        return fileInternalEventsLogged;
    }
    case Event::EventType::FileVersion: {
        FileVersion * fileVersion = FileVersion::read(*this, line);
        if (fileVersion)
            version =
                (fileVersion->versionMajor << 24) |
                (fileVersion->versionMinor << 16) |
                (fileVersion->versionPatch);
        return fileVersion;
    }
    case Event::EventType::FileSplitInformation:
        return FileSplitInformation::read(*this, line);
    case Event::EventType::FileComment:
        return FileComment::read(*this, line);

    /* CAN Events */
    case Event::EventType::CanMessage:
        return CanMessage::read(*this, line);
    case Event::EventType::CanExtendedMessage:
        return CanExtendedMessage::read(*this, line);
    case Event::EventType::CanRemoteFrame:
        return CanRemoteFrame::read(*this, line);
    case Event::EventType::CanErrorFrame:
        return CanErrorFrame::read(*this, line);
    case Event::EventType::CanBusStatistics:
        return CanBusStatistics::read(*this, line);
    case Event::EventType::CanError:
        return CanError::read(*this, line);
    case Event::EventType::CanOverloadFrame:
        return CanOverloadFrame::read(*this, line);

    /* CAN FD Events */
    case Event::EventType::CanFdMessage:
        return CanFdMessage::read(*this, line);
    case Event::EventType::CanFdExtendedMessage:
        return CanFdExtendedMessage::read(*this, line);
    case Event::EventType::CanFdErrorFrame:
        return CanFdErrorFrame::read(*this, line);
    // CAN FD Bus Statistics Event
    // CAN FD Overload Frame

    /* Log and Trigger Events */
    case Event::EventType::LogTrigger:
        return LogTrigger::read(*this, line);
    case Event::EventType::LogDirectStart:
        return LogDirectStart::read(*this, line);
    case Event::EventType::LogDirectStop:
        return LogDirectStop::read(*this, line);
    case Event::EventType::BeginTriggerblock: {
        BeginTriggerblock * beginTriggerblock = BeginTriggerblock::read(*this, line);
        if (beginTriggerblock)
            language = beginTriggerblock->language;
        return beginTriggerblock;
    }
    case Event::EventType::EndTriggerblock:
        return EndTriggerblock::read(*this, line);

    /* Environment Variables */
    case Event::EventType::EnvironmentVariables:
        return EnvironmentVariables::read(*this, line);

    /* System Variables */
    case Event::EventType::SystemVariables:
        return SystemVariables::read(*this, line);

    /* Macros Signal Events */
    case Event::EventType::MacroSignal:
        return MacroSignal::read(*this, line);

    /* GPS events */
    case Event::EventType::Gps:
        return Gps::read(*this, line);

    /* Comment events */
    case Event::EventType::Comment:
        return Comment::read(*this, line);

    /* Global market events */
    case Event::EventType::GlobalMarker:
        return GlobalMarker::read(*this, line);

    /* Ethernet Events */
    case Event::EventType::EthernetPacket:
        return EthernetPacket::read(*this, line);
    case Event::EventType::EthernetStatus:
        return EthernetStatus::read(*this, line);
    case Event::EventType::EthernetRxError:
        return EthernetRxError::read(*this, line);

    /* AFDX Events */
    case Event::EventType::AfdxPacket:
        return AfdxPacket::read(*this, line);

    /* FlexRay Events (Old Format) */
    case Event::EventType::FlexRayOldMessage:
        return FlexRayOldMessage::read(*this, line);
    case Event::EventType::FlexRayOldStartCycle:
        return FlexRayOldStartCycle::read(*this, line);

    /* FlexRay Events (New Format) */
    case Event::EventType::FlexRayMessage:
        return FlexRayMessage::read(*this, line);
    case Event::EventType::FlexRayStartCycle:
        return FlexRayStartCycle::read(*this, line);
    case Event::EventType::FlexRayStatus:
        return FlexRayStatus::read(*this, line);
    case Event::EventType::FlexRayError:
        return FlexRayError::read(*this, line);

    /* K-Line Events */
    case Event::EventType::KLineByte:
        return KLineByte::read(*this, line);
    case Event::EventType::KLineMessage:
        return KLineMessage::read(*this, line);

    /* LIN Events */
    case Event::EventType::LinMessage:
        return LinMessage::read(*this, line);

    /* LIN Error Events */
    case Event::EventType::LinTransmissionError:
        return LinTransmissionError::read(*this, line);
    case Event::EventType::LinReceiveError:
        return LinReceiveError::read(*this, line);
    case Event::EventType::LinSyncError:
        return LinSyncError::read(*this, line);
    case Event::EventType::LinChecksumError:
        return LinChecksumError::read(*this, line);
    case Event::EventType::LinSpike:
        return LinSpike::read(*this, line);
    case Event::EventType::LinDominantSignal:
        return LinDominantSignal::read(*this, line);

    /* LIN Info Events */
    case Event::EventType::LinBaudrate:
        return LinBaudrate::read(*this, line);
    case Event::EventType::LinDlcInfo:
        return LinDlcInfo::read(*this, line);
    case Event::EventType::LinChecksumInfo:
        return LinChecksumInfo::read(*this, line);
    case Event::EventType::LinSchedulerModeChange:
        return LinSchedulerModeChange::read(*this, line);
    case Event::EventType::LinSlaveTimeout:
        return LinSlaveTimeout::read(*this, line);
    case Event::EventType::LinEventTriggeredFrameInfo:
        return LinEventTriggeredFrameInfo::read(*this, line);
    case Event::EventType::LinStatisticInfo:
        return LinStatisticInfo::read(*this, line);
    case Event::EventType::LinShortOrSlowResponse:
        return LinShortOrSlowResponse::read(*this, line);
    case Event::EventType::LinDisturbance:
        return LinDisturbance::read(*this, line);

    /* LIN Sleep/Wakeup Events */
    case Event::EventType::LinSleepMode:
        return LinSleepMode::read(*this, line);
    case Event::EventType::LinWakeupFrame:
        return LinWakeupFrame::read(*this, line);
    case Event::EventType::LinUnexpectedWakeup:
        return LinUnexpectedWakeup::read(*this, line);

    /* MOST Events */
    case Event::EventType::Most25ControlMessageNodeMode:
        return Most25ControlMessageNodeMode::read(*this, line);
    case Event::EventType::Most25ControlMessageSpyMode:
        return Most25ControlMessageSpyMode::read(*this, line);
    case Event::EventType::Most25Packet:
        return Most25Packet::read(*this, line);
    case Event::EventType::MostLightLock:
        return MostLightLock::read(*this, line);
    case Event::EventType::MostSpecialRegister:
        return MostSpecialRegister::read(*this, line);
    case Event::EventType::MostCommonRegister:
        return MostCommonRegister::read(*this, line);
    case Event::EventType::MostHwMode:
        return MostHwMode::read(*this, line);
    case Event::EventType::MostNetState:
        return MostNetState::read(*this, line);
    case Event::EventType::MostDataLost:
        return MostDataLost::read(*this, line);
    case Event::EventType::MostTrigger:
        return MostTrigger::read(*this, line);
    case Event::EventType::MostStatistic:
        return MostStatistic::read(*this, line);
    case Event::EventType::MostStatisticExtended:
        return MostStatisticExtended::read(*this, line);
    case Event::EventType::MostTxLight:
        return MostTxLight::read(*this, line);
    case Event::EventType::MostStress:
        return MostStress::read(*this, line);
    case Event::EventType::Most25AllocTable:
        return Most25AllocTable::read(*this, line);
    case Event::EventType::Most150ControlMessage:
        return Most150ControlMessage::read(*this, line);
    case Event::EventType::Most150ControlMessageFragment:
        return Most150ControlMessageFragment::read(*this, line);
    case Event::EventType::Most150Packet:
        return Most150Packet::read(*this, line);
    case Event::EventType::Most150PacketFragment:
        return Most150PacketFragment::read(*this, line);
    case Event::EventType::MostEthernetPacket:
        return MostEthernetPacket::read(*this, line);
    case Event::EventType::MostEthernetPacketFragment:
        return MostEthernetPacketFragment::read(*this, line);
    case Event::EventType::MostSystem:
        return MostSystem::read(*this, line);
    case Event::EventType::Most150AllocTable:
        return Most150AllocTable::read(*this, line);
    case Event::EventType::Most50ControlMessage:
        return Most50ControlMessage::read(*this, line);
    case Event::EventType::Most50Packet:
        return Most50Packet::read(*this, line);
    case Event::EventType::MostEcl:
        return MostEcl::read(*this, line);

    /* TP/Diagnostics Events */
    case Event::EventType::TpSingleFrame:
        return TpSingleFrame::read(*this, line);
    case Event::EventType::TpFirstFrame:
        return TpFirstFrame::read(*this, line);
    case Event::EventType::TpConsecutiveFrame:
        return TpConsecutiveFrame::read(*this, line);
    case Event::EventType::TpFlowControlFrame:
        return TpFlowControlFrame::read(*this, line);
    case Event::EventType::DiagRequest:
        return DiagRequest::read(*this, line);

    /* undocumented events */
    case Event::EventType::StartOfMeasurement: {
        StartOfMeasurement * startOfMeasurement = StartOfMeasurement::read(*this, line);
        if (startOfMeasurement)
            language = startOfMeasurement->language;
        return startOfMeasurement;
    }

    default:
        break;
    }

    return nullptr;
}

void File::write(Event * event) {
    if (event != nullptr)
        event->write(*this, file);
}

}
}
