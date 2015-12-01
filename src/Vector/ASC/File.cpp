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
#include <iostream>

#include "../ASC.h"

namespace Vector {
namespace ASC {

File::File() :
    openMode(OpenMode::Read),
    date(),
    language(Language::En),
    base(Base::Dec),
    timestamps(Timestamps::Absolute),
    internalEventsLogged(true),
    version(0), // version will be set as soon as FileVersion is read
    timestampPrecision(0), // automatically set dependent on file version
    file(),
    scanner(nullptr)
{
}

File::~File()
{
    delete scanner;
    scanner = nullptr;
}

void File::open(const char * filename)
{
    switch(openMode) {
    case OpenMode::Read:
        /* open file for reading */
        file.open(filename, std::ios_base::in);

        /* create scanner */
        delete scanner;
        try {
            scanner = new ascFlexLexer(&file);
        }
        catch(std::bad_alloc & ba)
        {
            std::cerr << "Failed to allocate scanner: " << ba.what() << std::endl;
            exit(EXIT_FAILURE);
        }

        break;
    case OpenMode::Write:
        /* open file for writing */
        file.open(filename, std::ios_base::out);
        break;
    }
}

void File::open(const std::string & filename)
{
    open(filename.c_str());
}

bool File::is_open() const
{
    return file.is_open();
}

void File::close()
{
    /* delete scanner */
    delete scanner;
    scanner = nullptr;

    /* close file */
    file.close();
}

bool File::eof()
{
    return file.eof();
}

Event * File::read()
{
    /* scan line */
    int eventType = scanner->yylex();
    std::string line = scanner->YYText();

    /* remove windows line ending */
    if (line.back() == '\r')
        line.pop_back();

    switch(eventType) {
    /* unknown */
    case Event::EventType::Unknown:
    {
        std::cout << "Unknown: " << line << std::endl;
#if 0
        Unknown * unknown = new Unknown();
        unknown->line = line;
        return unknown;
#endif
    }

    /* File */
    case Event::EventType::FileDate:
    {
        FileDate * fileDate = FileDate::parse(*this, line);
        if (fileDate) {
            date = fileDate->date;
            language = fileDate->language;
        }
        return fileDate;
    }
    case Event::EventType::FileBaseTimestamps:
    {
        FileBaseTimestamps * fileBaseTimestamps = FileBaseTimestamps::parse(*this, line);
        if (fileBaseTimestamps) {
            base = fileBaseTimestamps->base;
            timestamps = fileBaseTimestamps->timestamps;
        }
        return fileBaseTimestamps;
    }
    case Event::EventType::FileInternalEventsLogged:
    {
        FileInternalEventsLogged * fileInternalEventsLogged = FileInternalEventsLogged::parse(*this, line);
        if (fileInternalEventsLogged)
            internalEventsLogged = fileInternalEventsLogged->internalEventsLogged;
        return fileInternalEventsLogged;
    }
    case Event::EventType::FileVersion:
    {
        FileVersion * fileVersion = FileVersion::parse(*this, line);
        if (fileVersion)
            version = (fileVersion->versionMajor << 24) | (fileVersion->versionMinor << 16);
        return fileVersion;
    }
    case Event::EventType::FileSplitInformation:
        return FileSplitInformation::parse(*this, line);
    case Event::EventType::FileComment:
        return FileComment::parse(*this, line);

    /* CAN Events */
    case Event::EventType::CanMessage:
        return CanMessage::parse(*this, line);
    case Event::EventType::CanExtendedMessage:
        return CanExtendedMessage::parse(*this, line);
    case Event::EventType::CanRemoteFrame:
        return CanRemoteFrame::parse(*this, line);
    case Event::EventType::CanErrorFrame:
        return CanErrorFrame::parse(*this, line);
    case Event::EventType::CanBusStatistics:
        return CanBusStatistics::parse(*this, line);
    case Event::EventType::CanError:
        return CanError::parse(*this, line);
    case Event::EventType::CanOverloadFrame:
        return CanOverloadFrame::parse(*this, line);

    /* CAN FD Events */
    case Event::EventType::CanFdMessage:
        return CanFdMessage::parse(*this, line);
    case Event::EventType::CanFdExtendedMessage:
        return CanFdExtendedMessage::parse(*this, line);
    case Event::EventType::CanFdErrorFrame:
        return CanFdErrorFrame::parse(*this, line);
    // CAN FD Bus Statistics Event
    // CAN FD Overload Frame

    /* Log and Trigger Events */
    case Event::EventType::LogTrigger:
        return LogTrigger::parse(*this, line);
    case Event::EventType::LogDirectStart:
        return LogDirectStart::parse(*this, line);
    case Event::EventType::LogDirectStop:
        return LogDirectStop::parse(*this, line);
    case Event::EventType::BeginTriggerblock:
    {
        BeginTriggerblock * beginTriggerblock = BeginTriggerblock::parse(*this, line);
        if (beginTriggerblock)
            language = beginTriggerblock->language;
        return beginTriggerblock;
    }
    case Event::EventType::EndTriggerblock:
        return EndTriggerblock::parse(*this, line);

    /* Environment Variables */
    case Event::EventType::EnvironmentVariables:
        return EnvironmentVariables::parse(*this, line);

    /* System Variables */
    case Event::EventType::SystemVariables:
        return SystemVariables::parse(*this, line);

    /* Macros Signal Events */
    case Event::EventType::MacroSignal:
        return MacroSignal::parse(*this, line);

    /* GPS events */
    case Event::EventType::Gps:
        return Gps::parse(*this, line);

    /* Comment events */
    case Event::EventType::Comment:
        return Comment::parse(*this, line);

    /* Global market events */
    case Event::EventType::GlobalMarker:
        return GlobalMarker::parse(*this, line);

    /* Ethernet Events */
    case Event::EventType::EthernetPacket:
        return EthernetPacket::parse(*this, line);
    case Event::EventType::EthernetStatus:
        return EthernetStatus::parse(*this, line);
    case Event::EventType::EthernetRxError:
        return EthernetRxError::parse(*this, line);

    /* AFDX Events */
    case Event::EventType::AfdxPacket:
        return AfdxPacket::parse(*this, line);

    /* FlexRay Events (Old Format) */
    case Event::EventType::FlexRayOldMessage:
        return FlexRayOldMessage::parse(*this, line);
    case Event::EventType::FlexRayOldStartCycle:
        return FlexRayOldStartCycle::parse(*this, line);

    /* FlexRay Events (New Format) */
    case Event::EventType::FlexRayMessage:
        return FlexRayMessage::parse(*this, line);
    case Event::EventType::FlexRayStartCycle:
        return FlexRayStartCycle::parse(*this, line);
    case Event::EventType::FlexRayStatus:
        return FlexRayStatus::parse(*this, line);
    case Event::EventType::FlexRayError:
        return FlexRayError::parse(*this, line);

    /* K-Line Events */
    case Event::EventType::KLineByte:
        return KLineByte::parse(*this, line);
    case Event::EventType::KLineMessage:
        return KLineMessage::parse(*this, line);

    /* LIN Events */
    case Event::EventType::LinMessage:
        return LinMessage::parse(*this, line);

    /* LIN Error Events */
    case Event::EventType::LinTransmissionError:
        return LinTransmissionError::parse(*this, line);
    case Event::EventType::LinReceiveError:
        return LinReceiveError::parse(*this, line);
    case Event::EventType::LinSyncError:
        return LinSyncError::parse(*this, line);
    case Event::EventType::LinChecksumError:
        return LinChecksumError::parse(*this, line);
    case Event::EventType::LinSpike:
        return LinSpike::parse(*this, line);
    case Event::EventType::LinDominantSignal:
        return LinDominantSignal::parse(*this, line);

    /* LIN Info Events */
    case Event::EventType::LinBaudrate:
        return LinBaudrate::parse(*this, line);
    case Event::EventType::LinDlcInfo:
        return LinDlcInfo::parse(*this, line);
    case Event::EventType::LinChecksumInfo:
        return LinChecksumInfo::parse(*this, line);
    case Event::EventType::LinSchedulerModeChange:
        return LinSchedulerModeChange::parse(*this, line);
    case Event::EventType::LinSlaveTimeout:
        return LinSlaveTimeout::parse(*this, line);
    case Event::EventType::LinEventTriggeredFrameInfo:
        return LinEventTriggeredFrameInfo::parse(*this, line);
    case Event::EventType::LinStatisticInfo:
        return LinStatisticInfo::parse(*this, line);
    case Event::EventType::LinShortOrSlowResponse:
        return LinShortOrSlowResponse::parse(*this, line);
    case Event::EventType::LinDisturbance:
        return LinDisturbance::parse(*this, line);

    /* LIN Sleep/Wakeup Events */
    case Event::EventType::LinSleepMode:
        return LinSleepMode::parse(*this, line);
    case Event::EventType::LinWakeupFrame:
        return LinWakeupFrame::parse(*this, line);
    case Event::EventType::LinUnexpectedWakeup:
        return LinUnexpectedWakeup::parse(*this, line);

    /* MOST Events */
    case Event::EventType::Most25ControlMessageNodeMode:
        return Most25ControlMessageNodeMode::parse(*this, line);
    case Event::EventType::Most25ControlMessageSpyMode:
        return Most25ControlMessageSpyMode::parse(*this, line);
    case Event::EventType::Most25Packet:
        return Most25Packet::parse(*this, line);
    case Event::EventType::MostLightLock:
        return MostLightLock::parse(*this, line);
    case Event::EventType::MostSpecialRegister:
        return MostSpecialRegister::parse(*this, line);
    case Event::EventType::MostCommonRegister:
        return MostCommonRegister::parse(*this, line);
    case Event::EventType::MostHwMode:
        return MostHwMode::parse(*this, line);
    case Event::EventType::MostNetState:
        return MostNetState::parse(*this, line);
    case Event::EventType::MostDataLost:
        return MostDataLost::parse(*this, line);
    case Event::EventType::MostTrigger:
        return MostTrigger::parse(*this, line);
    case Event::EventType::MostStatistic:
        return MostStatistic::parse(*this, line);
    case Event::EventType::MostStatisticExtended:
        return MostStatisticExtended::parse(*this, line);
    case Event::EventType::MostTxLight:
        return MostTxLight::parse(*this, line);
    case Event::EventType::MostStress:
        return MostStress::parse(*this, line);
    case Event::EventType::Most25AllocTable:
        return Most25AllocTable::parse(*this, line);
    case Event::EventType::Most150ControlMessage:
        return Most150ControlMessage::parse(*this, line);
    case Event::EventType::Most150ControlMessageFragment:
        return Most150ControlMessageFragment::parse(*this, line);
    case Event::EventType::Most150Packet:
        return Most150Packet::parse(*this, line);
    case Event::EventType::Most150PacketFragment:
        return Most150PacketFragment::parse(*this, line);
    case Event::EventType::MostEthernetPacket:
        return MostEthernetPacket::parse(*this, line);
    case Event::EventType::MostEthernetPacketFragment:
        return MostEthernetPacketFragment::parse(*this, line);
    case Event::EventType::MostSystem:
        return MostSystem::parse(*this, line);
    case Event::EventType::Most150AllocTable:
        return Most150AllocTable::parse(*this, line);
    case Event::EventType::Most50ControlMessage:
        return Most50ControlMessage::parse(*this, line);
    case Event::EventType::Most50Packet:
        return Most50Packet::parse(*this, line);
    case Event::EventType::MostEcl:
        return MostEcl::parse(*this, line);

    /* TP/Diagnostics Events */
    case Event::EventType::TpSingleFrame:
        return TpSingleFrame::parse(*this, line);
    case Event::EventType::TpFirstFrame:
        return TpFirstFrame::parse(*this, line);
    case Event::EventType::TpConsecutiveFrame:
        return TpConsecutiveFrame::parse(*this, line);
    case Event::EventType::TpFlowControlFrame:
        return TpFlowControlFrame::parse(*this, line);
    case Event::EventType::DiagRequest:
        return DiagRequest::parse(*this, line);

    /* undocumented events */
    case Event::EventType::StartOfMeasurement:
    {
        StartOfMeasurement * startOfMeasurement = StartOfMeasurement::parse(*this, line);
        if (startOfMeasurement)
            language = startOfMeasurement->language;
        return startOfMeasurement;
    }

    case Event::EventType::Default:
    default:
        std::cout << "Default: " << line << std::endl;

    }

    return nullptr;
}

void File::write(Event * event)
{
    if (event != nullptr)
        event->write(*this, file);
}

}
}
