#define BOOST_TEST_MODULE Events
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <fstream>
#include <iterator>
#include <string>

#include "Vector/ASC.h"

#define SUCCEEDED(code) ((int)(code) >= 0)
#define WARNED(code) ((int)(code) & 0x40000000)
#define FAILED(code) ((int)(code) < 0)

static bool isEqual(double a, double b)
{
    return ((a-b) < 0.000001) && ((b-a) < 0.000001);
}

/* File */
BOOST_AUTO_TEST_CASE(FileDate)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileDate.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileDate * fileDate;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileDate);
    fileDate = static_cast<Vector::ASC::FileDate *>(event);
    BOOST_CHECK(fileDate->date.tm_wday == 3);
    BOOST_CHECK(fileDate->date.tm_mon == 5);
    BOOST_CHECK(fileDate->date.tm_mday == 11);
    BOOST_CHECK(fileDate->date.tm_hour == 11);
    BOOST_CHECK(fileDate->date.tm_min == 37);
    BOOST_CHECK(fileDate->date.tm_sec == 33);
    BOOST_CHECK(fileDate->date.tm_year == (2008 - 1900));
    BOOST_CHECK(fileDate->language == Vector::ASC::File::Language::En);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileDate);
    fileDate = static_cast<Vector::ASC::FileDate *>(event);
    BOOST_CHECK(fileDate->date.tm_wday == 2);
    BOOST_CHECK(fileDate->date.tm_mon == 2);
    BOOST_CHECK(fileDate->date.tm_mday == 13);
    BOOST_CHECK(fileDate->date.tm_hour == 11);
    BOOST_CHECK(fileDate->date.tm_min == 58);
    BOOST_CHECK(fileDate->date.tm_sec == 02);
    BOOST_CHECK(fileDate->date.tm_year == (2007 - 1900));
    BOOST_CHECK(fileDate->language == Vector::ASC::File::Language::De);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(FileBaseTimestamps)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileBaseTimestamps.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileBaseTimestamps * fileBaseTimestamps;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);
    fileBaseTimestamps = static_cast<Vector::ASC::FileBaseTimestamps *>(event);
    BOOST_CHECK(fileBaseTimestamps->base == Vector::ASC::File::Base::Hex);
    BOOST_CHECK(fileBaseTimestamps->timestamps == Vector::ASC::File::Timestamps::Relative);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(FileInternalEventsLogged)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileInternalEventsLogged.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileInternalEventsLogged * fileInternalEventsLogged;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileInternalEventsLogged);
    fileInternalEventsLogged = static_cast<Vector::ASC::FileInternalEventsLogged *>(event);
    BOOST_CHECK(fileInternalEventsLogged->internalEventsLogged == true);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileInternalEventsLogged);
    fileInternalEventsLogged = static_cast<Vector::ASC::FileInternalEventsLogged *>(event);
    BOOST_CHECK(fileInternalEventsLogged->internalEventsLogged == false);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(FileVersion)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileVersion.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileVersion * fileVersion;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);
    fileVersion = static_cast<Vector::ASC::FileVersion *>(event);
    BOOST_CHECK(fileVersion->versionMajor == 7);
    BOOST_CHECK(fileVersion->versionMinor == 1);
    BOOST_CHECK(fileVersion->versionPatch == 0);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(FileSplitInformation)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileSplitInformation.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileSplitInformation * fileSplitInformation;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileSplitInformation);
    fileSplitInformation = static_cast<Vector::ASC::FileSplitInformation *>(event);
    BOOST_CHECK(fileSplitInformation->time == 60.0000);
    BOOST_CHECK(fileSplitInformation->fileName == "Inc_L1.asc");
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(FileComment)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FileComment.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FileComment * fileComment;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileComment);
    fileComment = static_cast<Vector::ASC::FileComment *>(event);
    BOOST_CHECK(fileComment->comment == " comment");
    delete event;

    file.close();
}

/* CAN Events */
BOOST_AUTO_TEST_CASE(CanMessageEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanMessageEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanMessageEvent * canMessageEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileVersion);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanMessageEvent);
    canMessageEvent = static_cast<Vector::ASC::CanMessageEvent *>(event);
    BOOST_CHECK(isEqual(canMessageEvent->time, 0.003040));
    BOOST_CHECK(canMessageEvent->channel == 1);
    BOOST_CHECK(canMessageEvent->id == 0x123);
    BOOST_CHECK(canMessageEvent->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(canMessageEvent->dlc == 2);
    BOOST_CHECK(canMessageEvent->data[0] == 0);
    BOOST_CHECK(canMessageEvent->data[1] == 0);
    BOOST_CHECK(canMessageEvent->messageDuration == 768000);
    BOOST_CHECK(canMessageEvent->messageLength == 67);
    BOOST_CHECK(canMessageEvent->messageId == 291);
    BOOST_CHECK(canMessageEvent->messageFlags.te == false);
    BOOST_CHECK(canMessageEvent->messageFlags.wu == false);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(CanExtendedMessageEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanExtendedMessageEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanExtendedMessageEvent * canExtendedMessageEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanExtendedMessageEvent);
    canExtendedMessageEvent = static_cast<Vector::ASC::CanExtendedMessageEvent *>(event);
    BOOST_CHECK(isEqual(canExtendedMessageEvent->time, 4.876870));
    BOOST_CHECK(canExtendedMessageEvent->channel == 1);
    BOOST_CHECK(canExtendedMessageEvent->id == 0x54C5638);
    BOOST_CHECK(canExtendedMessageEvent->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(canExtendedMessageEvent->dlc == 8);
    BOOST_CHECK(canExtendedMessageEvent->data[0] == 0);
    BOOST_CHECK(canExtendedMessageEvent->data[1] == 0);
    BOOST_CHECK(canExtendedMessageEvent->data[2] == 0);
    BOOST_CHECK(canExtendedMessageEvent->data[3] == 0);
    BOOST_CHECK(canExtendedMessageEvent->data[4] == 0);
    BOOST_CHECK(canExtendedMessageEvent->data[5] == 0);
    BOOST_CHECK(canExtendedMessageEvent->data[6] == 0);
    BOOST_CHECK(canExtendedMessageEvent->data[7] == 0);
    BOOST_CHECK(canExtendedMessageEvent->messageDuration == 1704000);
    BOOST_CHECK(canExtendedMessageEvent->messageLength == 145);
    BOOST_CHECK(canExtendedMessageEvent->messageId == 0x88888888);
    BOOST_CHECK(canExtendedMessageEvent->messageFlags.te == false);
    BOOST_CHECK(canExtendedMessageEvent->messageFlags.wu == false);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(CanRemoteFrameEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanRemoteFrameEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanRemoteFrameEvent * canRemoteFrameEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanRemoteFrameEvent);
    canRemoteFrameEvent = static_cast<Vector::ASC::CanRemoteFrameEvent *>(event);
    BOOST_CHECK(isEqual(canRemoteFrameEvent->time, 2.5010));
    BOOST_CHECK(canRemoteFrameEvent->channel == 1);
    BOOST_CHECK(canRemoteFrameEvent->id == 0x200);
    BOOST_CHECK(canRemoteFrameEvent->dir == Vector::ASC::Dir::Tx);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(CanErrorFrame)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanErrorFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanErrorFrame * canErrorFrame;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanErrorFrame);
    canErrorFrame = static_cast<Vector::ASC::CanErrorFrame *>(event);
    BOOST_CHECK(isEqual(canErrorFrame->time, 1.592186));
    BOOST_CHECK(canErrorFrame->channel == 1);
    BOOST_CHECK(canErrorFrame->code == 0xA2);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanErrorFrame);
    canErrorFrame = static_cast<Vector::ASC::CanErrorFrame *>(event);
    BOOST_CHECK(isEqual(canErrorFrame->time, 1.592186));
    BOOST_CHECK(canErrorFrame->channel == 2);
    BOOST_CHECK(canErrorFrame->flags == 0xe);
    BOOST_CHECK(canErrorFrame->codeExt == 0x20a2);
    BOOST_CHECK(canErrorFrame->code == 0x82);
    BOOST_CHECK(canErrorFrame->id == 0);
    BOOST_CHECK(canErrorFrame->dlc == 0);
    BOOST_CHECK(canErrorFrame->position == 5);
    BOOST_CHECK(canErrorFrame->length == 11300);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(CanBusStatisticsEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanBusStatisticsEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanBusStatisticsEvent * canBusStatisticsEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanBusStatisticsEvent);
    canBusStatisticsEvent = static_cast<Vector::ASC::CanBusStatisticsEvent *>(event);
    BOOST_CHECK(isEqual(canBusStatisticsEvent->time, 1.0100));
    BOOST_CHECK(canBusStatisticsEvent->channel == 1);
    BOOST_CHECK(canBusStatisticsEvent->dataFrames == 1000);
    BOOST_CHECK(canBusStatisticsEvent->remoteFrames == 15);
    BOOST_CHECK(canBusStatisticsEvent->extendedDataFrames == 0);
    BOOST_CHECK(canBusStatisticsEvent->extendedRemoteFrames == 0);
    BOOST_CHECK(canBusStatisticsEvent->errorFrames == 0);
    BOOST_CHECK(canBusStatisticsEvent->overloadFrames == 0);
    BOOST_CHECK(isEqual(canBusStatisticsEvent->busload, 0.0));
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(CanErrorEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanErrorEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanErrorEvent * canErrorEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanErrorEvent);
    canErrorEvent = static_cast<Vector::ASC::CanErrorEvent *>(event);
    BOOST_CHECK(isEqual(canErrorEvent->time, 0.0006));
    BOOST_CHECK(canErrorEvent->channel == 2);
    BOOST_CHECK(canErrorEvent->error == "chip status error active");
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(CanOverloadFrameEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanOverloadFrameEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanOverloadFrameEvent * canOverloadFrameEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanOverloadFrameEvent);
    canOverloadFrameEvent = static_cast<Vector::ASC::CanOverloadFrameEvent *>(event);
    BOOST_CHECK(isEqual(canOverloadFrameEvent->time, 2.5158));
    BOOST_CHECK(canOverloadFrameEvent->channel == 1);
    delete event;

    file.close();
}

/* CAN FD Events */
BOOST_AUTO_TEST_CASE(CanFdMessageEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanFdMessageEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanFdMessageEvent * canFdMessageEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanFdMessageEvent);
    canFdMessageEvent = static_cast<Vector::ASC::CanFdMessageEvent *>(event);
    BOOST_CHECK(isEqual(canFdMessageEvent->time, 8.151536));
    BOOST_CHECK(canFdMessageEvent->channel == 2);
    BOOST_CHECK(canFdMessageEvent->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(canFdMessageEvent->id == 0xc9);
    BOOST_CHECK(canFdMessageEvent->symbolicName == "ABSdata_FD_64Byte");
    BOOST_CHECK(canFdMessageEvent->brs == false);
    BOOST_CHECK(canFdMessageEvent->esi == false);
    BOOST_CHECK(canFdMessageEvent->dlc == 9);
    BOOST_CHECK(canFdMessageEvent->dataLength == 12);
    BOOST_CHECK(canFdMessageEvent->data[0] == 0x29);
    BOOST_CHECK(canFdMessageEvent->data[1] == 0x00);
    BOOST_CHECK(canFdMessageEvent->data[2] == 0x00);
    BOOST_CHECK(canFdMessageEvent->data[3] == 0x00);
    BOOST_CHECK(canFdMessageEvent->data[4] == 0x0b);
    BOOST_CHECK(canFdMessageEvent->data[5] == 0x2a);
    BOOST_CHECK(canFdMessageEvent->data[6] == 0x00);
    BOOST_CHECK(canFdMessageEvent->data[7] == 0x00);
    BOOST_CHECK(canFdMessageEvent->data[8] == 0x00);
    BOOST_CHECK(canFdMessageEvent->data[9] == 0x00);
    BOOST_CHECK(canFdMessageEvent->data[10] == 0x00);
    BOOST_CHECK(canFdMessageEvent->data[11] == 0x00);
    BOOST_CHECK(canFdMessageEvent->messageDuration == 164000);
    BOOST_CHECK(canFdMessageEvent->messageLength == 167);
    BOOST_CHECK(canFdMessageEvent->flags == 121200);
    BOOST_CHECK(canFdMessageEvent->crc == 0x7ca0);
    BOOST_CHECK(canFdMessageEvent->bitTimingConfArb == 0x500a2041);
    BOOST_CHECK(canFdMessageEvent->bitTimingConfData == 0x460a4841);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(CanFdExtendedMessageEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanFdExtendedMessageEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanFdExtendedMessageEvent * canFdExtendedMessageEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanFdExtendedMessageEvent);
    canFdExtendedMessageEvent = static_cast<Vector::ASC::CanFdExtendedMessageEvent *>(event);
    BOOST_CHECK(isEqual(canFdExtendedMessageEvent->time, 0.248166));
    BOOST_CHECK(canFdExtendedMessageEvent->channel == 2);
    BOOST_CHECK(canFdExtendedMessageEvent->dir == Vector::ASC::Dir::Rx);
    BOOST_CHECK(canFdExtendedMessageEvent->id == 0x1fffffff);
    BOOST_CHECK(canFdExtendedMessageEvent->symbolicName == "");
    BOOST_CHECK(canFdExtendedMessageEvent->brs == false);
    BOOST_CHECK(canFdExtendedMessageEvent->esi == false);
    BOOST_CHECK(canFdExtendedMessageEvent->dlc == 0xf);
    BOOST_CHECK(canFdExtendedMessageEvent->dataLength == 64);
    for (int i = 0; i < 64; ++i)
        BOOST_CHECK(canFdExtendedMessageEvent->data[i] == i+1);
    BOOST_CHECK(canFdExtendedMessageEvent->messageDuration == 1238000);
    BOOST_CHECK(canFdExtendedMessageEvent->messageLength == 111);
    BOOST_CHECK(canFdExtendedMessageEvent->flags == 101000);
    BOOST_CHECK(canFdExtendedMessageEvent->crc == 0x46518);
    BOOST_CHECK(canFdExtendedMessageEvent->bitTimingConfArb == 0x46500250);
    BOOST_CHECK(canFdExtendedMessageEvent->bitTimingConfData == 0x46280250);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(CanFdErrorFrame)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CanFdErrorFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CanFdErrorFrame * canFdErrorFrame;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CanFdErrorFrame);
    canFdErrorFrame = static_cast<Vector::ASC::CanFdErrorFrame *>(event);
    BOOST_CHECK(isEqual(canFdErrorFrame->time, 3.923364));
    BOOST_CHECK(canFdErrorFrame->channel == 2);
    BOOST_CHECK(canFdErrorFrame->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(canFdErrorFrame->errorText == "Not Acknowledge error, dominant error flag");
    BOOST_CHECK(canFdErrorFrame->flags1 == 0xfffe);
    BOOST_CHECK(canFdErrorFrame->code == 0xc7);
    BOOST_CHECK(canFdErrorFrame->codeExt == 0x31ca);
    BOOST_CHECK(canFdErrorFrame->phase == Vector::ASC::CanFdErrorFrame::Phase::Data);
    BOOST_CHECK(canFdErrorFrame->position == 45);
    BOOST_CHECK(canFdErrorFrame->id == 0xff);
    BOOST_CHECK(canFdErrorFrame->brs == true);
    BOOST_CHECK(canFdErrorFrame->esi == false);
    BOOST_CHECK(canFdErrorFrame->dlc == 0xf);
    BOOST_CHECK(canFdErrorFrame->dataLength == 64);
    for (int i = 0; i < 64; ++i)
        BOOST_CHECK(canFdErrorFrame->data[i] == 0xaa);
    BOOST_CHECK(canFdErrorFrame->messageDuration == 336484);
    BOOST_CHECK(canFdErrorFrame->flags2 == 3);
    BOOST_CHECK(canFdErrorFrame->crc == 0);
    BOOST_CHECK(canFdErrorFrame->bitTimingConfArb == 0x51103250);
    BOOST_CHECK(canFdErrorFrame->bitTimingConfData == 0x460a0250);
    delete event;

    file.close();
}

// @todo CanFdBusStatisticsEvent
// @todo CanFdOverloadFrame

/* Log and Trigger Events */
BOOST_AUTO_TEST_CASE(LogTriggerEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LogTriggerEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LogTriggerEvent * logTriggerEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LogTriggerEvent);
    logTriggerEvent = static_cast<Vector::ASC::LogTriggerEvent *>(event);
    BOOST_CHECK(logTriggerEvent->time == 2.0000);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(LogDirectStartEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LogDirectStartEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LogDirectStartEvent * logDirectStartEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LogDirectStartEvent);
    logDirectStartEvent = static_cast<Vector::ASC::LogDirectStartEvent *>(event);
    BOOST_CHECK(isEqual(logDirectStartEvent->time, 2.1100));
    BOOST_CHECK(logDirectStartEvent->preTrigger == 2000);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(LogDirectStopEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LogDirectStopEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LogDirectStopEvent * logDirectStopEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LogDirectStopEvent);
    logDirectStopEvent = static_cast<Vector::ASC::LogDirectStopEvent *>(event);
    BOOST_CHECK(isEqual(logDirectStopEvent->time, 2.1100));
    BOOST_CHECK(logDirectStopEvent->postTrigger == 1000);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(BeginTriggerblockEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/BeginTriggerblockEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::BeginTriggerblockEvent * beginTriggerblockEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::BeginTriggerblockEvent);
    beginTriggerblockEvent = static_cast<Vector::ASC::BeginTriggerblockEvent *>(event);
    BOOST_CHECK(beginTriggerblockEvent->date.tm_wday == 1);
    BOOST_CHECK(beginTriggerblockEvent->date.tm_mon == 2);
    BOOST_CHECK(beginTriggerblockEvent->date.tm_mday == 7);
    BOOST_CHECK(beginTriggerblockEvent->date.tm_hour == 1+12);
    BOOST_CHECK(beginTriggerblockEvent->date.tm_min == 21);
    BOOST_CHECK(beginTriggerblockEvent->date.tm_sec == 51);
    BOOST_CHECK(beginTriggerblockEvent->date.tm_year == (2005 - 1900));
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(EndTriggerblockEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EndTriggerblockEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::EndTriggerblockEvent * endTriggerblockEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EndTriggerblockEvent);
    endTriggerblockEvent = static_cast<Vector::ASC::EndTriggerblockEvent *>(event);
    delete event;

    file.close();
}

/* Environment Variables */
BOOST_AUTO_TEST_CASE(EnvironmentVariablesEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EnvironmentVariablesEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::EnvironmentVariablesEvent * environmentVariablesEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EnvironmentVariablesEvent);
    environmentVariablesEvent = static_cast<Vector::ASC::EnvironmentVariablesEvent *>(event);
    BOOST_CHECK(isEqual(environmentVariablesEvent->time, 2.130000));
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EnvironmentVariablesEvent);
    environmentVariablesEvent = static_cast<Vector::ASC::EnvironmentVariablesEvent *>(event);
    BOOST_CHECK(isEqual(environmentVariablesEvent->time, 2.567000));
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EnvironmentVariablesEvent);
    environmentVariablesEvent = static_cast<Vector::ASC::EnvironmentVariablesEvent *>(event);
    BOOST_CHECK(isEqual(environmentVariablesEvent->time, 3.830000));
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EnvironmentVariablesEvent);
    environmentVariablesEvent = static_cast<Vector::ASC::EnvironmentVariablesEvent *>(event);
    BOOST_CHECK(isEqual(environmentVariablesEvent->time, 2.250000));
    delete event;

    file.close();
}

/* System Variables */
BOOST_AUTO_TEST_CASE(SystemVariablesEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/SystemVariablesEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::SystemVariablesEvent * systemVariablesEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::SystemVariablesEvent);
    systemVariablesEvent = static_cast<Vector::ASC::SystemVariablesEvent *>(event);
    BOOST_CHECK(isEqual(systemVariablesEvent->time, 1.200000));
    BOOST_CHECK(systemVariablesEvent->svtype == Vector::ASC::Svtype::Int);
    BOOST_CHECK(systemVariablesEvent->path == "::NS1::IntVar");
    BOOST_CHECK(systemVariablesEvent->value == "4");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::SystemVariablesEvent);
    systemVariablesEvent = static_cast<Vector::ASC::SystemVariablesEvent *>(event);
    BOOST_CHECK(isEqual(systemVariablesEvent->time, 1.370000));
    BOOST_CHECK(systemVariablesEvent->svtype == Vector::ASC::Svtype::Float);
    BOOST_CHECK(systemVariablesEvent->path == "::NS1::FloatVar");
    BOOST_CHECK(systemVariablesEvent->value == "4.1");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::SystemVariablesEvent);
    systemVariablesEvent = static_cast<Vector::ASC::SystemVariablesEvent *>(event);
    BOOST_CHECK(isEqual(systemVariablesEvent->time, 1.580000));
    BOOST_CHECK(systemVariablesEvent->svtype == Vector::ASC::Svtype::String);
    BOOST_CHECK(systemVariablesEvent->path == "::NS1::StringVar");
    BOOST_CHECK(systemVariablesEvent->value == "\"Value: 4\"");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::SystemVariablesEvent);
    systemVariablesEvent = static_cast<Vector::ASC::SystemVariablesEvent *>(event);
    BOOST_CHECK(isEqual(systemVariablesEvent->time, 1.690000));
    BOOST_CHECK(systemVariablesEvent->svtype == Vector::ASC::Svtype::IntArray);
    BOOST_CHECK(systemVariablesEvent->path == "::NS1::IntArray");
    BOOST_CHECK(systemVariablesEvent->value == "A3 4 5 2");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::SystemVariablesEvent);
    systemVariablesEvent = static_cast<Vector::ASC::SystemVariablesEvent *>(event);
    BOOST_CHECK(isEqual(systemVariablesEvent->time, 2.000000));
    BOOST_CHECK(systemVariablesEvent->svtype == Vector::ASC::Svtype::FloatArray);
    BOOST_CHECK(systemVariablesEvent->path == "::NS1::FloatArray");
    BOOST_CHECK(systemVariablesEvent->value == "D3 4.1 2.9 6");
    delete event;

    file.close();
}

/* Macros Signal Event */
BOOST_AUTO_TEST_CASE(MacroSignalEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MacroSignalEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MacroSignalEvent * macroSignalEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MacroSignalEvent);
    macroSignalEvent = static_cast<Vector::ASC::MacroSignalEvent *>(event);
    BOOST_CHECK(isEqual(macroSignalEvent->time, 2.350000));
    BOOST_CHECK(macroSignalEvent->bussystem == Vector::ASC::MacroSignalEvent::Bussystem::Can);
    BOOST_CHECK(macroSignalEvent->channel == 1);
    BOOST_CHECK(macroSignalEvent->node == "Node");
    BOOST_CHECK(macroSignalEvent->message == "aCANMessage");
    BOOST_CHECK(macroSignalEvent->signal == "aBitSignal");
    BOOST_CHECK(macroSignalEvent->value == "1");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MacroSignalEvent);
    macroSignalEvent = static_cast<Vector::ASC::MacroSignalEvent *>(event);
    BOOST_CHECK(isEqual(macroSignalEvent->time, 2.350000));
    BOOST_CHECK(macroSignalEvent->bussystem == Vector::ASC::MacroSignalEvent::Bussystem::Can);
    BOOST_CHECK(macroSignalEvent->channel == 1);
    BOOST_CHECK(macroSignalEvent->node == "Node");
    BOOST_CHECK(macroSignalEvent->message == "aCANMessage");
    BOOST_CHECK(macroSignalEvent->signal == "aBitSignal");
    BOOST_CHECK(macroSignalEvent->value == "Eins");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MacroSignalEvent);
    macroSignalEvent = static_cast<Vector::ASC::MacroSignalEvent *>(event);
    BOOST_CHECK(isEqual(macroSignalEvent->time, 5.000000));
    BOOST_CHECK(macroSignalEvent->bussystem == Vector::ASC::MacroSignalEvent::Bussystem::Lin);
    BOOST_CHECK(macroSignalEvent->channel == 1);
    BOOST_CHECK(macroSignalEvent->node == "L_Slave");
    BOOST_CHECK(macroSignalEvent->message == "aLINMessage");
    BOOST_CHECK(macroSignalEvent->signal == "aLINBitSignal");
    BOOST_CHECK(macroSignalEvent->value == "0");
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MacroSignalEvent);
    macroSignalEvent = static_cast<Vector::ASC::MacroSignalEvent *>(event);
    BOOST_CHECK(isEqual(macroSignalEvent->time, 1.110000));
    BOOST_CHECK(macroSignalEvent->bussystem == Vector::ASC::MacroSignalEvent::Bussystem::FlexRay);
    BOOST_CHECK(macroSignalEvent->channel == 1);
    BOOST_CHECK(macroSignalEvent->node == "FR_ECU");
    BOOST_CHECK(macroSignalEvent->message == "aFlexRayMessage");
    BOOST_CHECK(macroSignalEvent->signal == "aFRSignal");
    BOOST_CHECK(macroSignalEvent->value == "3");
    delete event;

    file.close();
}

/* GPS events */
BOOST_AUTO_TEST_CASE(GpsEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/GpsEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::GpsEvent * gpsEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::GpsEvent);
    gpsEvent = static_cast<Vector::ASC::GpsEvent *>(event);
    BOOST_CHECK(isEqual(gpsEvent->time, 2.097603));
    BOOST_CHECK(gpsEvent->channel == 1);
    BOOST_CHECK(isEqual(gpsEvent->latitude, 48.825100));
    BOOST_CHECK(isEqual(gpsEvent->longitude, 9.091267));
    BOOST_CHECK(isEqual(gpsEvent->altitude, 325.399994));
    BOOST_CHECK(isEqual(gpsEvent->speed, 29.686400));
    BOOST_CHECK(isEqual(gpsEvent->course, 87.099998));
    delete event;

    file.close();
}

/* Comment events */
BOOST_AUTO_TEST_CASE(CommentEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/CommentEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::CommentEvent * commentEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::CommentEvent);
    commentEvent = static_cast<Vector::ASC::CommentEvent *>(event);
    BOOST_CHECK(isEqual(commentEvent->time, 1.593770));
    BOOST_CHECK(commentEvent->type == 105);
    BOOST_CHECK(commentEvent->commentText == "testComment");
    delete event;

    file.close();
}

/* Global market events */
BOOST_AUTO_TEST_CASE(GlobalMarkerEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/GlobalMarkerEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::GlobalMarkerEvent * globalMarkerEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::GlobalMarkerEvent);
    globalMarkerEvent = static_cast<Vector::ASC::GlobalMarkerEvent *>(event);
    BOOST_CHECK(isEqual(globalMarkerEvent->time, 2.200804));
    BOOST_CHECK(globalMarkerEvent->type == 0);
    BOOST_CHECK(globalMarkerEvent->backgroundColor == 16777215);
    BOOST_CHECK(globalMarkerEvent->foregroundColor == 0);
    BOOST_CHECK(globalMarkerEvent->relocatable == true);
    BOOST_CHECK(globalMarkerEvent->groupName == "Marker Group");
    BOOST_CHECK(globalMarkerEvent->markerName == "[1]");
    BOOST_CHECK(globalMarkerEvent->description == "description");
    delete event;

    file.close();
}

/* Ethernet Events */
BOOST_AUTO_TEST_CASE(EthernetPacket)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EthernetPacket.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::EthernetPacket * ethernetPacket;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EthernetPacket);
    ethernetPacket = static_cast<Vector::ASC::EthernetPacket *>(event);
    BOOST_CHECK(isEqual(ethernetPacket->time, 0.000000));
    BOOST_CHECK(ethernetPacket->channel == 2);
    BOOST_CHECK(ethernetPacket->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(ethernetPacket->dataLen == 0x3c);
    BOOST_CHECK(ethernetPacket->data[0x00] == 0xFF);
    BOOST_CHECK(ethernetPacket->data[0x01] == 0xFF);
    BOOST_CHECK(ethernetPacket->data[0x02] == 0xFF);
    BOOST_CHECK(ethernetPacket->data[0x03] == 0xFF);
    BOOST_CHECK(ethernetPacket->data[0x04] == 0xFF);
    BOOST_CHECK(ethernetPacket->data[0x05] == 0xFF);
    BOOST_CHECK(ethernetPacket->data[0x06] == 0x40);
    BOOST_CHECK(ethernetPacket->data[0x07] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x08] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x09] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x0a] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x0b] == 0x04);
    BOOST_CHECK(ethernetPacket->data[0x0c] == 0x08);
    BOOST_CHECK(ethernetPacket->data[0x0d] == 0x06);
    BOOST_CHECK(ethernetPacket->data[0x0e] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x0f] == 0x01);
    BOOST_CHECK(ethernetPacket->data[0x10] == 0x08);
    BOOST_CHECK(ethernetPacket->data[0x11] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x12] == 0x06);
    BOOST_CHECK(ethernetPacket->data[0x13] == 0x04);
    BOOST_CHECK(ethernetPacket->data[0x14] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x15] == 0x01);
    BOOST_CHECK(ethernetPacket->data[0x16] == 0x40);
    BOOST_CHECK(ethernetPacket->data[0x17] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x18] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x19] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x1a] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x1b] == 0x04);
    BOOST_CHECK(ethernetPacket->data[0x1c] == 0xC0);
    BOOST_CHECK(ethernetPacket->data[0x1d] == 0xA8);
    BOOST_CHECK(ethernetPacket->data[0x1e] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x1f] == 0x01);
    BOOST_CHECK(ethernetPacket->data[0x20] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x21] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x22] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x23] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x24] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x25] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x26] == 0xC0);
    BOOST_CHECK(ethernetPacket->data[0x27] == 0xA8);
    BOOST_CHECK(ethernetPacket->data[0x28] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x29] == 0x01);
    BOOST_CHECK(ethernetPacket->data[0x2a] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x2b] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x2c] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x2d] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x2e] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x2f] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x30] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x31] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x32] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x33] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x34] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x35] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x36] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x37] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x38] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x39] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x3a] == 0x00);
    BOOST_CHECK(ethernetPacket->data[0x3b] == 0x00);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(EthernetStatus)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EthernetStatus.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::EthernetStatus * ethernetStatus;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EthernetStatus);
    ethernetStatus = static_cast<Vector::ASC::EthernetStatus *>(event);
    BOOST_CHECK(isEqual(ethernetStatus->time, 0.002404));
    BOOST_CHECK(ethernetStatus->channel == 1);
    BOOST_CHECK(ethernetStatus->link == "Link_up");
    BOOST_CHECK(ethernetStatus->linkSpeed == "100Mbit/s");
    BOOST_CHECK(ethernetStatus->physical == "IEEE802.3");
    BOOST_CHECK(ethernetStatus->duplex == "Full");
    BOOST_CHECK(ethernetStatus->mdi == "Crossover");
    BOOST_CHECK(ethernetStatus->connector == "RJ45");
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(EthernetRxError)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/EthernetRxError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::EthernetRxError * ethernetRxError;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::EthernetRxError);
    ethernetRxError = static_cast<Vector::ASC::EthernetRxError *>(event);
    BOOST_CHECK(isEqual(ethernetRxError->time, 1.465409));
    BOOST_CHECK(ethernetRxError->channel == 2);
    BOOST_CHECK(ethernetRxError->errorCode == 0x02);
    BOOST_CHECK(ethernetRxError->frameChecksum == 0x00001234);
    BOOST_CHECK(ethernetRxError->dataLen == 0x3c);
    BOOST_CHECK(ethernetRxError->data[0x00] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x01] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x02] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x03] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x04] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x05] == 0x01);
    BOOST_CHECK(ethernetRxError->data[0x06] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x07] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x08] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x09] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x0a] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x0b] == 0x02);
    BOOST_CHECK(ethernetRxError->data[0x0c] == 0xFF);
    BOOST_CHECK(ethernetRxError->data[0x0d] == 0x01);
    BOOST_CHECK(ethernetRxError->data[0x0e] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x0f] == 0x01);
    BOOST_CHECK(ethernetRxError->data[0x10] == 0x02);
    BOOST_CHECK(ethernetRxError->data[0x11] == 0x03);
    BOOST_CHECK(ethernetRxError->data[0x12] == 0x04);
    BOOST_CHECK(ethernetRxError->data[0x13] == 0x05);
    BOOST_CHECK(ethernetRxError->data[0x14] == 0x06);
    BOOST_CHECK(ethernetRxError->data[0x15] == 0x07);
    BOOST_CHECK(ethernetRxError->data[0x16] == 0x08);
    BOOST_CHECK(ethernetRxError->data[0x17] == 0x09);
    BOOST_CHECK(ethernetRxError->data[0x18] == 0x0A);
    BOOST_CHECK(ethernetRxError->data[0x19] == 0x0B);
    BOOST_CHECK(ethernetRxError->data[0x1a] == 0x0C);
    BOOST_CHECK(ethernetRxError->data[0x1b] == 0x0D);
    BOOST_CHECK(ethernetRxError->data[0x1c] == 0x0E);
    BOOST_CHECK(ethernetRxError->data[0x1d] == 0x0F);
    BOOST_CHECK(ethernetRxError->data[0x1e] == 0x10);
    BOOST_CHECK(ethernetRxError->data[0x1f] == 0x11);
    BOOST_CHECK(ethernetRxError->data[0x20] == 0x12);
    BOOST_CHECK(ethernetRxError->data[0x21] == 0x13);
    BOOST_CHECK(ethernetRxError->data[0x22] == 0x14);
    BOOST_CHECK(ethernetRxError->data[0x23] == 0x15);
    BOOST_CHECK(ethernetRxError->data[0x24] == 0x16);
    BOOST_CHECK(ethernetRxError->data[0x25] == 0x17);
    BOOST_CHECK(ethernetRxError->data[0x26] == 0x18);
    BOOST_CHECK(ethernetRxError->data[0x27] == 0x19);
    BOOST_CHECK(ethernetRxError->data[0x28] == 0x1A);
    BOOST_CHECK(ethernetRxError->data[0x29] == 0x1B);
    BOOST_CHECK(ethernetRxError->data[0x2a] == 0x1C);
    BOOST_CHECK(ethernetRxError->data[0x2b] == 0x1D);
    BOOST_CHECK(ethernetRxError->data[0x2c] == 0x1E);
    BOOST_CHECK(ethernetRxError->data[0x2d] == 0x1F);
    BOOST_CHECK(ethernetRxError->data[0x2e] == 0x20);
    BOOST_CHECK(ethernetRxError->data[0x2f] == 0x21);
    BOOST_CHECK(ethernetRxError->data[0x30] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x31] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x32] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x33] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x34] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x35] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x36] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x37] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x38] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x39] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x3a] == 0x00);
    BOOST_CHECK(ethernetRxError->data[0x3b] == 0x00);
    delete event;

    file.close();
}

/* AFDX Events */
BOOST_AUTO_TEST_CASE(AfdxPacket)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/AfdxPacket.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::AfdxPacket * afdxPacket;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::AfdxPacket);
    afdxPacket = static_cast<Vector::ASC::AfdxPacket *>(event);
    BOOST_CHECK(isEqual(afdxPacket->time, 0.000000));
    BOOST_CHECK(afdxPacket->channel == 1);
    BOOST_CHECK(afdxPacket->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(afdxPacket->ethChannel == 1);
    BOOST_CHECK(afdxPacket->flags == 0x64);
    BOOST_CHECK(afdxPacket->bag == 0);
    BOOST_CHECK(afdxPacket->dataLen == 0x3c);
    BOOST_CHECK(afdxPacket->data[0x00] == 0xFF);
    BOOST_CHECK(afdxPacket->data[0x01] == 0xFF);
    BOOST_CHECK(afdxPacket->data[0x02] == 0xFF);
    BOOST_CHECK(afdxPacket->data[0x03] == 0xFF);
    BOOST_CHECK(afdxPacket->data[0x04] == 0xFF);
    BOOST_CHECK(afdxPacket->data[0x05] == 0xFF);
    BOOST_CHECK(afdxPacket->data[0x06] == 0x40);
    BOOST_CHECK(afdxPacket->data[0x07] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x08] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x09] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x0a] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x0b] == 0x04);
    BOOST_CHECK(afdxPacket->data[0x0c] == 0x08);
    BOOST_CHECK(afdxPacket->data[0x0d] == 0x06);
    BOOST_CHECK(afdxPacket->data[0x0e] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x0f] == 0x01);
    BOOST_CHECK(afdxPacket->data[0x10] == 0x08);
    BOOST_CHECK(afdxPacket->data[0x11] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x12] == 0x06);
    BOOST_CHECK(afdxPacket->data[0x13] == 0x04);
    BOOST_CHECK(afdxPacket->data[0x14] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x15] == 0x01);
    BOOST_CHECK(afdxPacket->data[0x16] == 0x40);
    BOOST_CHECK(afdxPacket->data[0x17] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x18] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x19] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x1a] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x1b] == 0x04);
    BOOST_CHECK(afdxPacket->data[0x1c] == 0xC0);
    BOOST_CHECK(afdxPacket->data[0x1d] == 0xA8);
    BOOST_CHECK(afdxPacket->data[0x1e] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x1f] == 0x01);
    BOOST_CHECK(afdxPacket->data[0x20] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x21] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x22] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x23] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x24] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x25] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x26] == 0xC0);
    BOOST_CHECK(afdxPacket->data[0x27] == 0xA8);
    BOOST_CHECK(afdxPacket->data[0x28] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x29] == 0x01);
    BOOST_CHECK(afdxPacket->data[0x2a] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x2b] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x2c] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x2d] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x2e] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x2f] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x30] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x31] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x32] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x33] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x34] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x35] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x36] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x37] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x38] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x39] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x3a] == 0x00);
    BOOST_CHECK(afdxPacket->data[0x3b] == 0x00);
    delete event;

    file.close();
}

/* FlexRay Events (Old Format) */
BOOST_AUTO_TEST_CASE(FlexRayOldMessageEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayOldMessageEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayOldMessageEvent * flexRayOldMessageEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayOldMessageEvent);
    flexRayOldMessageEvent = static_cast<Vector::ASC::FlexRayOldMessageEvent *>(event);
    BOOST_CHECK(isEqual(flexRayOldMessageEvent->time, 0.0420));
    BOOST_CHECK(flexRayOldMessageEvent->channel == '1');
    BOOST_CHECK(flexRayOldMessageEvent->id == 4);
    BOOST_CHECK(flexRayOldMessageEvent->cycle == 25);
    BOOST_CHECK(flexRayOldMessageEvent->nm == false);
    BOOST_CHECK(flexRayOldMessageEvent->sync == true);
    BOOST_CHECK(flexRayOldMessageEvent->headerCrc == 151);
    BOOST_CHECK(flexRayOldMessageEvent->symbolicName == "Ident_04_Rnd_0");
    BOOST_CHECK(flexRayOldMessageEvent->dlc == 4);
    BOOST_CHECK(flexRayOldMessageEvent->data[0] == 21);
    BOOST_CHECK(flexRayOldMessageEvent->data[1] == 87);
    BOOST_CHECK(flexRayOldMessageEvent->data[2] == 22);
    BOOST_CHECK(flexRayOldMessageEvent->data[3] == 148);
    BOOST_CHECK(flexRayOldMessageEvent->frameState == 0x00d0);
    BOOST_CHECK(flexRayOldMessageEvent->headerBitMask == 0x9a);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayOldMessageEvent);
    flexRayOldMessageEvent = static_cast<Vector::ASC::FlexRayOldMessageEvent *>(event);
    BOOST_CHECK(isEqual(flexRayOldMessageEvent->time, 0.0426));
    BOOST_CHECK(flexRayOldMessageEvent->channel == '2');
    BOOST_CHECK(flexRayOldMessageEvent->id == 13);
    BOOST_CHECK(flexRayOldMessageEvent->cycle == 25);
    BOOST_CHECK(flexRayOldMessageEvent->nm == false);
    BOOST_CHECK(flexRayOldMessageEvent->sync == false);
    BOOST_CHECK(flexRayOldMessageEvent->headerCrc == 620);
    BOOST_CHECK(flexRayOldMessageEvent->symbolicName == "x");
    BOOST_CHECK(flexRayOldMessageEvent->dlc == 4);
    BOOST_CHECK(flexRayOldMessageEvent->data[0] == 2);
    BOOST_CHECK(flexRayOldMessageEvent->data[1] == 89);
    BOOST_CHECK(flexRayOldMessageEvent->data[2] == 0);
    BOOST_CHECK(flexRayOldMessageEvent->data[3] == 13);
    BOOST_CHECK(flexRayOldMessageEvent->frameState == 0x0180);
    BOOST_CHECK(flexRayOldMessageEvent->headerBitMask == 0x88);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(FlexRayOldStartCycleEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayOldStartCycleEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayOldStartCycleEvent * flexRayOldStartCycleEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayOldStartCycleEvent);
    flexRayOldStartCycleEvent = static_cast<Vector::ASC::FlexRayOldStartCycleEvent *>(event);
    BOOST_CHECK(isEqual(flexRayOldStartCycleEvent->time, 0.0417));
    BOOST_CHECK(flexRayOldStartCycleEvent->channel == '*');
    BOOST_CHECK(flexRayOldStartCycleEvent->dlc == 2);
    BOOST_CHECK(flexRayOldStartCycleEvent->data[0] == 0);
    BOOST_CHECK(flexRayOldStartCycleEvent->data[1] == 0);
    delete event;

    file.close();
}

/* FlexRay Events (New Format) */
BOOST_AUTO_TEST_CASE(FlexRayMessageEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayMessageEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayMessageEvent * flexRayMessageEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayMessageEvent);
    flexRayMessageEvent = static_cast<Vector::ASC::FlexRayMessageEvent *>(event);
    BOOST_CHECK(isEqual(flexRayMessageEvent->time, 0.039255));
    BOOST_CHECK(flexRayMessageEvent->flexRayEventType == Vector::ASC::FlexRayMessageEvent::FlexRayEventType::RMSG);
    BOOST_CHECK(flexRayMessageEvent->clusterNr == 0);
    BOOST_CHECK(flexRayMessageEvent->clientId == 0);
    BOOST_CHECK(flexRayMessageEvent->channelNr == 1);
    BOOST_CHECK(flexRayMessageEvent->channelMask == 1);
    BOOST_CHECK(flexRayMessageEvent->slotId == 4);
    BOOST_CHECK(flexRayMessageEvent->cycleNo == 7);
    BOOST_CHECK(flexRayMessageEvent->direction == "Rx");
    BOOST_CHECK(flexRayMessageEvent->appParam == 0);
    BOOST_CHECK(flexRayMessageEvent->flags == 14);
    BOOST_CHECK(flexRayMessageEvent->ccType == 5);
    BOOST_CHECK(flexRayMessageEvent->ccData == 32);
    BOOST_CHECK(flexRayMessageEvent->headerCrc == 151);
    BOOST_CHECK(flexRayMessageEvent->name == "Message_2");
    BOOST_CHECK(flexRayMessageEvent->payloadLength == 4);
    BOOST_CHECK(flexRayMessageEvent->bufferLength == 4);
    BOOST_CHECK(flexRayMessageEvent->data[0] == 27);
    BOOST_CHECK(flexRayMessageEvent->data[1] == 24);
    BOOST_CHECK(flexRayMessageEvent->data[2] == 29);
    BOOST_CHECK(flexRayMessageEvent->data[3] == 241);
    BOOST_CHECK(flexRayMessageEvent->frameCrc == 0);
    BOOST_CHECK(flexRayMessageEvent->spyFlag == 0);
    BOOST_CHECK(flexRayMessageEvent->frameLengthNs == 0);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayMessageEvent);
    flexRayMessageEvent = static_cast<Vector::ASC::FlexRayMessageEvent *>(event);
    BOOST_CHECK(isEqual(flexRayMessageEvent->time, 0.047906));
    BOOST_CHECK(flexRayMessageEvent->flexRayEventType == Vector::ASC::FlexRayMessageEvent::FlexRayEventType::PDU);
    BOOST_CHECK(flexRayMessageEvent->clusterNr == 0);
    BOOST_CHECK(flexRayMessageEvent->clientId == 2);
    BOOST_CHECK(flexRayMessageEvent->channelNr == 1);
    BOOST_CHECK(flexRayMessageEvent->channelMask == 1);
    BOOST_CHECK(flexRayMessageEvent->slotId == 3);
    BOOST_CHECK(flexRayMessageEvent->cycleNo == 7);
    BOOST_CHECK(flexRayMessageEvent->direction == "Tx");
    BOOST_CHECK(flexRayMessageEvent->appParam == 0);
    BOOST_CHECK(flexRayMessageEvent->flags == 2313218);
    BOOST_CHECK(flexRayMessageEvent->ccType == 5);
    BOOST_CHECK(flexRayMessageEvent->ccData == 32);
    BOOST_CHECK(flexRayMessageEvent->headerCrc == 559);
    BOOST_CHECK(flexRayMessageEvent->name == "PDU_DEMO_1");
    BOOST_CHECK(flexRayMessageEvent->payloadLength == 1);
    BOOST_CHECK(flexRayMessageEvent->bufferLength == 1);
    BOOST_CHECK(flexRayMessageEvent->data[0] == 0);
    BOOST_CHECK(flexRayMessageEvent->frameCrc == 0);
    BOOST_CHECK(flexRayMessageEvent->spyFlag == 0);
    BOOST_CHECK(flexRayMessageEvent->frameLengthNs == 0);
    BOOST_CHECK(flexRayMessageEvent->pduOffset == 40);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayMessageEvent);
    flexRayMessageEvent = static_cast<Vector::ASC::FlexRayMessageEvent *>(event);
    BOOST_CHECK(isEqual(flexRayMessageEvent->time, 0.047906));
    BOOST_CHECK(flexRayMessageEvent->flexRayEventType == Vector::ASC::FlexRayMessageEvent::FlexRayEventType::RMSG);
    BOOST_CHECK(flexRayMessageEvent->clusterNr == 0);
    BOOST_CHECK(flexRayMessageEvent->clientId == 2);
    BOOST_CHECK(flexRayMessageEvent->channelNr == 1);
    BOOST_CHECK(flexRayMessageEvent->channelMask == 1);
    BOOST_CHECK(flexRayMessageEvent->slotId == 3);
    BOOST_CHECK(flexRayMessageEvent->cycleNo == 7);
    BOOST_CHECK(flexRayMessageEvent->direction == "Tx");
    BOOST_CHECK(flexRayMessageEvent->appParam == 0);
    BOOST_CHECK(flexRayMessageEvent->flags == 2640898);
    BOOST_CHECK(flexRayMessageEvent->ccType == 5);
    BOOST_CHECK(flexRayMessageEvent->ccData == 32);
    BOOST_CHECK(flexRayMessageEvent->headerCrc == 559);
    BOOST_CHECK(flexRayMessageEvent->name == "FlexRay_Frame_[3|0|1]");
    BOOST_CHECK(flexRayMessageEvent->payloadLength == 42);
    BOOST_CHECK(flexRayMessageEvent->bufferLength == 42);
    BOOST_CHECK(flexRayMessageEvent->data[ 0] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[ 1] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[ 2] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[ 3] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[ 4] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[ 5] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[ 6] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[ 7] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[ 8] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[ 9] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[10] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[11] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[12] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[13] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[14] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[15] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[16] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[17] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[18] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[19] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[20] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[21] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[22] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[23] == 128);
    BOOST_CHECK(flexRayMessageEvent->data[24] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[25] == 128);
    BOOST_CHECK(flexRayMessageEvent->data[26] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[27] == 128);
    BOOST_CHECK(flexRayMessageEvent->data[28] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[29] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[30] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[31] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[32] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[33] == 128);
    BOOST_CHECK(flexRayMessageEvent->data[34] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[35] == 128);
    BOOST_CHECK(flexRayMessageEvent->data[36] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[37] == 128);
    BOOST_CHECK(flexRayMessageEvent->data[38] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[39] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[40] == 0);
    BOOST_CHECK(flexRayMessageEvent->data[41] == 56);
    BOOST_CHECK(flexRayMessageEvent->frameCrc == 0);
    BOOST_CHECK(flexRayMessageEvent->spyFlag == 0);
    BOOST_CHECK(flexRayMessageEvent->frameLengthNs == 0);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(FlexRayStartCycleEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayStartCycleEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayStartCycleEvent * flexRayStartCycleEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayStartCycleEvent);
    flexRayStartCycleEvent = static_cast<Vector::ASC::FlexRayStartCycleEvent *>(event);
    BOOST_CHECK(isEqual(flexRayStartCycleEvent->time, 0.044115));
    BOOST_CHECK(flexRayStartCycleEvent->clusterNr == 0);
    BOOST_CHECK(flexRayStartCycleEvent->clientId == 0);
    BOOST_CHECK(flexRayStartCycleEvent->channelNr == 1);
    BOOST_CHECK(flexRayStartCycleEvent->channelMask == 3);
    BOOST_CHECK(flexRayStartCycleEvent->cycleNo == 8);
    BOOST_CHECK(flexRayStartCycleEvent->direction == "Rx");
    BOOST_CHECK(flexRayStartCycleEvent->ccType == 5);
    BOOST_CHECK(flexRayStartCycleEvent->ccData[0] == 0);
    BOOST_CHECK(flexRayStartCycleEvent->ccData[1] == 4);
    BOOST_CHECK(flexRayStartCycleEvent->ccData[2] == 0);
    BOOST_CHECK(flexRayStartCycleEvent->ccData[3] == 0);
    BOOST_CHECK(flexRayStartCycleEvent->ccData[4] == 0);
    BOOST_CHECK(flexRayStartCycleEvent->nmVectL == 0);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(FlexRayStatusEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayStatusEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayStatusEvent * flexRayStatusEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayStatusEvent);
    flexRayStatusEvent = static_cast<Vector::ASC::FlexRayStatusEvent *>(event);
    BOOST_CHECK(isEqual(flexRayStatusEvent->time, 0.003022));
    BOOST_CHECK(flexRayStatusEvent->clusterNr == 0);
    BOOST_CHECK(flexRayStatusEvent->clientId == 0);
    BOOST_CHECK(flexRayStatusEvent->channelNr == 1);
    BOOST_CHECK(flexRayStatusEvent->channelMask == 3);
    BOOST_CHECK(flexRayStatusEvent->cycleNo == 255);
    BOOST_CHECK(flexRayStatusEvent->ccType == 5);
    BOOST_CHECK(flexRayStatusEvent->syncState == 2);
    BOOST_CHECK(flexRayStatusEvent->ccData[0] == 15);
    BOOST_CHECK(flexRayStatusEvent->ccData[1] == 0);
    BOOST_CHECK(flexRayStatusEvent->symbol == 0);
    BOOST_CHECK(flexRayStatusEvent->wakeUpState == 0);
    BOOST_CHECK(flexRayStatusEvent->spyFlag == 0);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(FlexRayErrorEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/FlexRayErrorEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::FlexRayErrorEvent * flexRayErrorEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FlexRayErrorEvent);
    flexRayErrorEvent = static_cast<Vector::ASC::FlexRayErrorEvent *>(event);
    BOOST_CHECK(isEqual(flexRayErrorEvent->time, 7.344250));
    BOOST_CHECK(flexRayErrorEvent->clusterNr == 0);
    BOOST_CHECK(flexRayErrorEvent->clientId == 0);
    BOOST_CHECK(flexRayErrorEvent->channelNr == 1);
    BOOST_CHECK(flexRayErrorEvent->channelMask == 2);
    BOOST_CHECK(flexRayErrorEvent->ccType == 5);
    BOOST_CHECK(flexRayErrorEvent->ccData[0] == 5);
    BOOST_CHECK(flexRayErrorEvent->ccData[1] == 65536);
    BOOST_CHECK(flexRayErrorEvent->ccData[2] == 0);
    BOOST_CHECK(flexRayErrorEvent->ccData[3] == 0);
    delete event;

    file.close();
}

/* K-Line Events */
BOOST_AUTO_TEST_CASE(KLineByteEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/KLineByteEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::KLineByteEvent * kLineByteEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::KLineByteEvent);
    kLineByteEvent = static_cast<Vector::ASC::KLineByteEvent *>(event);
    BOOST_CHECK(isEqual(kLineByteEvent->time, 12.315000));
    BOOST_CHECK(kLineByteEvent->port == "COM2");
    BOOST_CHECK(kLineByteEvent->direction == Vector::ASC::Dir::Rx);
    BOOST_CHECK(kLineByteEvent->baudrate == 10400);
    BOOST_CHECK(kLineByteEvent->length == 7);
    BOOST_CHECK(kLineByteEvent->data[0] == 0x83);
    BOOST_CHECK(kLineByteEvent->data[1] == 0x11);
    BOOST_CHECK(kLineByteEvent->data[2] == 0x61);
    BOOST_CHECK(kLineByteEvent->data[3] == 0x7F);
    BOOST_CHECK(kLineByteEvent->data[4] == 0x1A);
    BOOST_CHECK(kLineByteEvent->data[5] == 0x78);
    BOOST_CHECK(kLineByteEvent->data[6] == 0x06);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(KLineMessageEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/KLineMessageEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::KLineMessageEvent * kLineMessageEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::KLineMessageEvent);
    kLineMessageEvent = static_cast<Vector::ASC::KLineMessageEvent *>(event);
    BOOST_CHECK(isEqual(kLineMessageEvent->time, 12.315000));
    BOOST_CHECK(kLineMessageEvent->port == "COM2");
    BOOST_CHECK(kLineMessageEvent->direction == Vector::ASC::Dir::Rx);
    BOOST_CHECK(kLineMessageEvent->baudrate == 10400);
    BOOST_CHECK(kLineMessageEvent->source == "61");
    BOOST_CHECK(kLineMessageEvent->destination == "11");
    BOOST_CHECK(kLineMessageEvent->length == 7);
    BOOST_CHECK(kLineMessageEvent->data[0] == 0x83);
    BOOST_CHECK(kLineMessageEvent->data[1] == 0x11);
    BOOST_CHECK(kLineMessageEvent->data[2] == 0x61);
    BOOST_CHECK(kLineMessageEvent->data[3] == 0x7F);
    BOOST_CHECK(kLineMessageEvent->data[4] == 0x1A);
    BOOST_CHECK(kLineMessageEvent->data[5] == 0x78);
    BOOST_CHECK(kLineMessageEvent->data[6] == 0x06);
    delete event;

    file.close();
}

/* LIN Events */
BOOST_AUTO_TEST_CASE(LinMessage)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinMessage * linMessage;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinMessage);
    linMessage = static_cast<Vector::ASC::LinMessage *>(event);
    BOOST_CHECK(isEqual(linMessage->time, 0.073973));
    BOOST_CHECK(linMessage->channel == 1);
    BOOST_CHECK(linMessage->id == "2d");
    BOOST_CHECK(linMessage->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(linMessage->dlc == 8);
    BOOST_CHECK(linMessage->data[0] == 0x00);
    BOOST_CHECK(linMessage->data[1] == 0xf0);
    BOOST_CHECK(linMessage->data[2] == 0xf0);
    BOOST_CHECK(linMessage->data[3] == 0xff);
    BOOST_CHECK(linMessage->data[4] == 0xff);
    BOOST_CHECK(linMessage->data[5] == 0xff);
    BOOST_CHECK(linMessage->data[6] == 0xff);
    BOOST_CHECK(linMessage->data[7] == 0xff);
    BOOST_CHECK(linMessage->checksum = 70);
    BOOST_CHECK(linMessage->headerTime == 40);
    BOOST_CHECK(linMessage->fullTime == 130);
    BOOST_CHECK(isEqual(linMessage->startOfFrame, 0.067195));
    BOOST_CHECK(linMessage->baudrate == 19230);
    BOOST_CHECK(linMessage->syncBreak == 937125);
    BOOST_CHECK(linMessage->syncDel == 114062);
    BOOST_CHECK(isEqual(linMessage->endOfHeader, 0.069266));
    BOOST_CHECK(isEqual(linMessage->endOfByte[0], 0.069789));
    BOOST_CHECK(isEqual(linMessage->endOfByte[1], 0.070312));
    BOOST_CHECK(isEqual(linMessage->endOfByte[2], 0.070835));
    BOOST_CHECK(isEqual(linMessage->endOfByte[3], 0.071358));
    BOOST_CHECK(isEqual(linMessage->endOfByte[4], 0.071881));
    BOOST_CHECK(isEqual(linMessage->endOfByte[5], 0.072404));
    BOOST_CHECK(isEqual(linMessage->endOfByte[6], 0.072927));
    BOOST_CHECK(isEqual(linMessage->endOfByte[7], 0.073450));
    BOOST_CHECK(linMessage->simulated == true);
    BOOST_CHECK(isEqual(linMessage->endOfFrame, 0.073973));
    BOOST_CHECK(linMessage->responseBaudrate == 19231);
    BOOST_CHECK(isEqual(linMessage->headerBaudrate, 19230.769231));
    BOOST_CHECK(linMessage->stopBitOffsetInHeader == 26000);
    BOOST_CHECK(linMessage->stopBitOffsetInResponse == 26000);
    BOOST_CHECK(linMessage->checksumModel == Vector::ASC::LinChecksumModel::Enhanced);
    delete event;

    file.close();
}

/* LIN Error Events */
BOOST_AUTO_TEST_CASE(LinTransmissionError)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinTransmissionError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinTransmissionError * linTransmissionError;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinTransmissionError);
    linTransmissionError = static_cast<Vector::ASC::LinTransmissionError *>(event);
    BOOST_CHECK(isEqual(linTransmissionError->time, 0.424674));
    BOOST_CHECK(linTransmissionError->channel == 1);
    BOOST_CHECK(linTransmissionError->id == "33");
    BOOST_CHECK(linTransmissionError->headerTime == 40);
    BOOST_CHECK(linTransmissionError->fullTime == 166);
    BOOST_CHECK(isEqual(linTransmissionError->startOfFrame, 0.416054));
    BOOST_CHECK(linTransmissionError->baudrate == 19230);
    BOOST_CHECK(linTransmissionError->syncBreak == 937187);
    BOOST_CHECK(linTransmissionError->syncDel == 113250);
    BOOST_CHECK(isEqual(linTransmissionError->endOfHeader, 0.418122));
    BOOST_CHECK(isEqual(linTransmissionError->headerBaudrate, 19230.769231));
    BOOST_CHECK(linTransmissionError->stopBitOffsetInHeader == 26000);
    BOOST_CHECK(linTransmissionError->checksumModel == Vector::ASC::LinChecksumModel::Enhanced);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(LinReceiveError)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinReceiveError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinReceiveError * linReceiveError;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinReceiveError);
    linReceiveError = static_cast<Vector::ASC::LinReceiveError *>(event);
    BOOST_CHECK(isEqual(linReceiveError->time, 0.554673));
    BOOST_CHECK(linReceiveError->channel == 1);
    BOOST_CHECK(linReceiveError->id == "33");
    BOOST_CHECK(linReceiveError->dlc == 8);
    BOOST_CHECK(linReceiveError->description == "timeout while waiting for checksum field");
    BOOST_CHECK(linReceiveError->stateReason == 0x0c);
    BOOST_CHECK(linReceiveError->isShortError == false);
    BOOST_CHECK(linReceiveError->isDlcTimeout == false);
    BOOST_CHECK(linReceiveError->hasDataBytes == true);
    BOOST_CHECK(linReceiveError->data[0] == 0x05);
    BOOST_CHECK(linReceiveError->data[1] == 0x00);
    BOOST_CHECK(linReceiveError->data[2] == 0x00);
    BOOST_CHECK(linReceiveError->data[3] == 0x00);
    BOOST_CHECK(linReceiveError->data[4] == 0x00);
    BOOST_CHECK(linReceiveError->data[5] == 0xff);
    BOOST_CHECK(linReceiveError->data[6] == 0xff);
    BOOST_CHECK(linReceiveError->data[7] == 0xff);
    BOOST_CHECK(isEqual(linReceiveError->startOfFrame, 0.546052));
    BOOST_CHECK(linReceiveError->baudrate == 19230);
    BOOST_CHECK(linReceiveError->syncBreak == 937187);
    BOOST_CHECK(linReceiveError->syncDel == 112437);
    BOOST_CHECK(isEqual(linReceiveError->endOfHeader, 0.548121));
    BOOST_CHECK(isEqual(linReceiveError->endOfByte[0], 0.548644));
    BOOST_CHECK(isEqual(linReceiveError->endOfByte[1], 0.549167));
    BOOST_CHECK(isEqual(linReceiveError->endOfByte[2], 0.549690));
    BOOST_CHECK(isEqual(linReceiveError->endOfByte[3], 0.550213));
    BOOST_CHECK(isEqual(linReceiveError->endOfByte[4], 0.550736));
    BOOST_CHECK(isEqual(linReceiveError->endOfByte[5], 0.551259));
    BOOST_CHECK(isEqual(linReceiveError->endOfByte[6], 0.551782));
    BOOST_CHECK(isEqual(linReceiveError->endOfByte[7], 0.552305));
    BOOST_CHECK(linReceiveError->responseBaudrate == 19231);
    BOOST_CHECK(linReceiveError->stopBitOffsetInResponse == 26000);
    BOOST_CHECK(isEqual(linReceiveError->headerBaudrate, 19230.769231));
    BOOST_CHECK(linReceiveError->stopBitOffsetInHeader == 26000);
    BOOST_CHECK(linReceiveError->checksumModel == Vector::ASC::LinChecksumModel::Enhanced);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(LinSyncError)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSyncError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinSyncError * linSyncError;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinSyncError);
    linSyncError = static_cast<Vector::ASC::LinSyncError *>(event);
    BOOST_CHECK(isEqual(linSyncError->time, 2.022336));
    BOOST_CHECK(linSyncError->channel == 2);
    BOOST_CHECK(linSyncError->timeInterval[0] == 208);
    BOOST_CHECK(linSyncError->timeInterval[1] == 0);
    BOOST_CHECK(linSyncError->timeInterval[2] == 0);
    BOOST_CHECK(linSyncError->timeInterval[3] == 0);
    BOOST_CHECK(isEqual(linSyncError->startOfFrame, 2.021077));
    BOOST_CHECK(linSyncError->baudrate == 19230);
    BOOST_CHECK(linSyncError->syncBreak == 937125);
    BOOST_CHECK(linSyncError->syncDel == 113312);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(LinChecksumError)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinChecksumError.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinChecksumError * linChecksumError;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinChecksumError);
    linChecksumError = static_cast<Vector::ASC::LinChecksumError *>(event);
    BOOST_CHECK(isEqual(linChecksumError->time, 0.462829));
    BOOST_CHECK(linChecksumError->channel == 1);
    BOOST_CHECK(linChecksumError->id == "33");
    BOOST_CHECK(linChecksumError->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(linChecksumError->dlc == 8);
    BOOST_CHECK(linChecksumError->data[0] == 0x05);
    BOOST_CHECK(linChecksumError->data[1] == 0x00);
    BOOST_CHECK(linChecksumError->data[2] == 0x00);
    BOOST_CHECK(linChecksumError->data[3] == 0x00);
    BOOST_CHECK(linChecksumError->data[4] == 0x00);
    BOOST_CHECK(linChecksumError->data[5] == 0xff);
    BOOST_CHECK(linChecksumError->data[6] == 0xff);
    BOOST_CHECK(linChecksumError->data[7] == 0xff);
    BOOST_CHECK(linChecksumError->checksum == 0x86);
    BOOST_CHECK(linChecksumError->headerTime == 40);
    BOOST_CHECK(linChecksumError->fullTime == 130);
    BOOST_CHECK(isEqual(linChecksumError->startOfFrame, 0.456050));
    BOOST_CHECK(linChecksumError->baudrate == 19230);
    BOOST_CHECK(linChecksumError->syncBreak == 937187);
    BOOST_CHECK(linChecksumError->syncDel == 114875);
    BOOST_CHECK(isEqual(linChecksumError->endOfHeader, 0.458122));
    BOOST_CHECK(isEqual(linChecksumError->endOfByte[0], 0.458645));
    BOOST_CHECK(isEqual(linChecksumError->endOfByte[1], 0.459168));
    BOOST_CHECK(isEqual(linChecksumError->endOfByte[2], 0.459691));
    BOOST_CHECK(isEqual(linChecksumError->endOfByte[3], 0.460214));
    BOOST_CHECK(isEqual(linChecksumError->endOfByte[4], 0.460737));
    BOOST_CHECK(isEqual(linChecksumError->endOfByte[5], 0.461260));
    BOOST_CHECK(isEqual(linChecksumError->endOfByte[6], 0.461783));
    BOOST_CHECK(isEqual(linChecksumError->endOfByte[7], 0.462306));
    BOOST_CHECK(linChecksumError->simulated == true);
    BOOST_CHECK(isEqual(linChecksumError->endOfFrame, 0.462829));
    BOOST_CHECK(linChecksumError->responseBaudrate == 19231);
    BOOST_CHECK(isEqual(linChecksumError->headerBaudrate, 19230.769231));
    BOOST_CHECK(linChecksumError->stopBitOffsetInHeader == 26000);
    BOOST_CHECK(linChecksumError->stopBitOffsetInResponse == 26000);
    BOOST_CHECK(linChecksumError->checksumModel == Vector::ASC::LinChecksumModel::Enhanced);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(LinSpikeEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSpikeEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinSpikeEvent * linSpikeEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinSpikeEvent);
    linSpikeEvent = static_cast<Vector::ASC::LinSpikeEvent *>(event);
    BOOST_CHECK(isEqual(linSpikeEvent->time, 5.990958));
    BOOST_CHECK(linSpikeEvent->channel == 2);
    BOOST_CHECK(linSpikeEvent->dir == Vector::ASC::Dir::Rx);
    BOOST_CHECK(linSpikeEvent->spikeLength == 56);
    BOOST_CHECK(isEqual(linSpikeEvent->startOfFrame, 5.990902));
    BOOST_CHECK(linSpikeEvent->baudrate == 9615);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(LinDominantSignal)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinDominantSignal.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinDominantSignal * linDominantSignal;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinDominantSignal);
    linDominantSignal = static_cast<Vector::ASC::LinDominantSignal *>(event);
    BOOST_CHECK(isEqual(linDominantSignal->time, 8.976802));
    BOOST_CHECK(linDominantSignal->channel == 1);
    BOOST_CHECK(linDominantSignal->domSigState == Vector::ASC::LinDomSigState::Detected);
    BOOST_CHECK(linDominantSignal->domSigLength == 5003);
    BOOST_CHECK(isEqual(linDominantSignal->startOfFrame, 8.971798));
    BOOST_CHECK(linDominantSignal->baudrate == 9615);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinDominantSignal);
    linDominantSignal = static_cast<Vector::ASC::LinDominantSignal *>(event);
    BOOST_CHECK(isEqual(linDominantSignal->time, 8.977000));
    BOOST_CHECK(linDominantSignal->channel == 1);
    BOOST_CHECK(linDominantSignal->domSigState == Vector::ASC::LinDomSigState::Finished);
    BOOST_CHECK(linDominantSignal->domSigLength == 5201);
    BOOST_CHECK(isEqual(linDominantSignal->startOfFrame, 8.971798));
    BOOST_CHECK(linDominantSignal->baudrate == 9615);
    delete event;

    file.close();
}

/* LIN Info Events */
BOOST_AUTO_TEST_CASE(LinBaudrate)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinBaudrate.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinBaudrate * linBaudrate;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinBaudrate);
    linBaudrate = static_cast<Vector::ASC::LinBaudrate *>(event);
    BOOST_CHECK(isEqual(linBaudrate->time, 0.0188));
    BOOST_CHECK(linBaudrate->channel == 1);
    BOOST_CHECK(linBaudrate->baudrate == 9615);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(LinDlcInfo)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinDlcInfo.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinDlcInfo * linDlcInfo;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinDlcInfo);
    linDlcInfo = static_cast<Vector::ASC::LinDlcInfo *>(event);
    BOOST_CHECK(isEqual(linDlcInfo->time, 12.6375));
    BOOST_CHECK(linDlcInfo->channel == 1);
    BOOST_CHECK(linDlcInfo->id == "20");
    BOOST_CHECK(linDlcInfo->dlc == 4);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(LinChecksumInfo)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinChecksumInfo.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinChecksumInfo * linChecksumInfo;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinChecksumInfo);
    linChecksumInfo = static_cast<Vector::ASC::LinChecksumInfo *>(event);
    BOOST_CHECK(isEqual(linChecksumInfo->time, 0.0201));
    BOOST_CHECK(linChecksumInfo->channel == 1);
    BOOST_CHECK(linChecksumInfo->id == "22");
    BOOST_CHECK(linChecksumInfo->checksumModelInfo == Vector::ASC::LinChecksumModelInfo::Classic);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(LinSchedulerModeChange)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSchedulerModeChange.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinSchedulerModeChange * linSchedulerModeChange;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinSchedulerModeChange);
    linSchedulerModeChange = static_cast<Vector::ASC::LinSchedulerModeChange *>(event);
    BOOST_CHECK(isEqual(linSchedulerModeChange->time, 0.1000));
    BOOST_CHECK(linSchedulerModeChange->channel == 1);
    BOOST_CHECK(linSchedulerModeChange->priorSchedulerMode == 2);
    BOOST_CHECK(linSchedulerModeChange->nextSchedulerMode == 0);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(LinSlaveTimeout)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSlaveTimeout.asc");
    BOOST_REQUIRE(file.is_open());


    Vector::ASC::Event * event;
    Vector::ASC::LinSlaveTimeout * linSlaveTimeout;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinSlaveTimeout);
    linSlaveTimeout = static_cast<Vector::ASC::LinSlaveTimeout *>(event);
    BOOST_CHECK(isEqual(linSlaveTimeout->time, 1.0012));
    BOOST_CHECK(linSlaveTimeout->channel == 1);
    BOOST_CHECK(linSlaveTimeout->slaveId == 0);
    BOOST_CHECK(linSlaveTimeout->currentState == 0);
    BOOST_CHECK(linSlaveTimeout->followingState == 1);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(LinEventTriggeredFrameInfo)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinEventTriggeredFrameInfo.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinEventTriggeredFrameInfo * linEventTriggeredFrameInfo;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinEventTriggeredFrameInfo);
    linEventTriggeredFrameInfo = static_cast<Vector::ASC::LinEventTriggeredFrameInfo *>(event);
    BOOST_CHECK(isEqual(linEventTriggeredFrameInfo->time, 1.909165));
    BOOST_CHECK(linEventTriggeredFrameInfo->channel == 1);
    BOOST_CHECK(linEventTriggeredFrameInfo->id == "3a");
    BOOST_CHECK(linEventTriggeredFrameInfo->etfName == "ETF_MotorStates");
    BOOST_CHECK(linEventTriggeredFrameInfo->description == "No response");
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(LinStatisticInfo)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinStatisticInfo.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinStatisticInfo * linStatisticInfo;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinStatisticInfo);
    linStatisticInfo = static_cast<Vector::ASC::LinStatisticInfo *>(event);
    BOOST_CHECK(isEqual(linStatisticInfo->time, 1.999580));
    BOOST_CHECK(linStatisticInfo->channel == 1);
    BOOST_CHECK(linStatisticInfo->channelNum == 1);
    BOOST_CHECK(isEqual(linStatisticInfo->busLoad, 0.903601));
    BOOST_CHECK(linStatisticInfo->burstsTotal == 0);
    BOOST_CHECK(linStatisticInfo->burstsOverrun == 0);
    BOOST_CHECK(linStatisticInfo->framesSent == 0);
    BOOST_CHECK(linStatisticInfo->framesReceived == 73);
    BOOST_CHECK(linStatisticInfo->framesUnanswered == 0);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(LinShortOrSlowResponse)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinShortOrSlowResponse.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinShortOrSlowResponse * linShortOrSlowResponse;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinShortOrSlowResponse);
    linShortOrSlowResponse = static_cast<Vector::ASC::LinShortOrSlowResponse *>(event);
    BOOST_CHECK(isEqual(linShortOrSlowResponse->time, 1.298765));
    BOOST_CHECK(linShortOrSlowResponse->channel == 1);
    BOOST_CHECK(linShortOrSlowResponse->id == "1");
    BOOST_CHECK(linShortOrSlowResponse->dlc == 8);
    BOOST_CHECK(linShortOrSlowResponse->numberOfResponseBytes == 9);
    BOOST_CHECK(linShortOrSlowResponse->data[0] == 0x11);
    BOOST_CHECK(linShortOrSlowResponse->data[1] == 0x12);
    BOOST_CHECK(linShortOrSlowResponse->data[2] == 0x13);
    BOOST_CHECK(linShortOrSlowResponse->data[3] == 0x14);
    BOOST_CHECK(linShortOrSlowResponse->data[4] == 0x15);
    BOOST_CHECK(linShortOrSlowResponse->data[5] == 0x16);
    BOOST_CHECK(linShortOrSlowResponse->data[6] == 0x17);
    BOOST_CHECK(linShortOrSlowResponse->data[7] == 0x18);
    BOOST_CHECK(linShortOrSlowResponse->data[8] == 0x99);
    BOOST_CHECK(linShortOrSlowResponse->isSlowResponse == true);
    BOOST_CHECK(linShortOrSlowResponse->responseWasInterruptedByBreak == false);
    BOOST_CHECK(isEqual(linShortOrSlowResponse->startOfFrame, 1.279516));
    BOOST_CHECK(linShortOrSlowResponse->baudrate == 19230);
    BOOST_CHECK(linShortOrSlowResponse->syncBreak == 937250);
    BOOST_CHECK(linShortOrSlowResponse->syncDel == 102625);
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfHeader, 1.281570));
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfByte[0], 1.283679));
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfByte[1], 1.285759));
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfByte[2], 1.287839));
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfByte[3], 1.289927));
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfByte[4], 1.292007));
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfByte[5], 1.294087));
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfByte[6], 1.296167));
    BOOST_CHECK(isEqual(linShortOrSlowResponse->endOfByte[7], 1.298244));
    BOOST_CHECK(isEqual(linShortOrSlowResponse->headerBaudrate, 19230.769231));
    BOOST_CHECK(linShortOrSlowResponse->stopBitOffsetInHeader == 26000);
    BOOST_CHECK(linShortOrSlowResponse->checksumModel == Vector::ASC::LinChecksumModel::Unknown);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(LinDisturbanceEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinDisturbanceEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinDisturbanceEvent * linDisturbanceEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinDisturbanceEvent);
    linDisturbanceEvent = static_cast<Vector::ASC::LinDisturbanceEvent *>(event);
    BOOST_CHECK(isEqual(linDisturbanceEvent->time, 1.323661));
    BOOST_CHECK(linDisturbanceEvent->channel == 1);
    BOOST_CHECK(linDisturbanceEvent->disturbanceType == Vector::ASC::LinDisturbanceType::Dominant);
    BOOST_CHECK(linDisturbanceEvent->byteIndex == 1);
    BOOST_CHECK(linDisturbanceEvent->bitIndex == 6);
    BOOST_CHECK(linDisturbanceEvent->bitOffset == 0);
    BOOST_CHECK(linDisturbanceEvent->length == 16);
    BOOST_CHECK(linDisturbanceEvent->header == 0x2D);
    BOOST_CHECK(linDisturbanceEvent->disturbingHeader == 0xFF);
    delete event;

    file.close();
}

/* LIN Sleep/Wakeup Events */
BOOST_AUTO_TEST_CASE(LinSleepMode)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinSleepMode.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinSleepMode * linSleepMode;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinSleepMode);
    linSleepMode = static_cast<Vector::ASC::LinSleepMode *>(event);
    BOOST_CHECK(isEqual(linSleepMode->time, 0.7772));
    BOOST_CHECK(linSleepMode->channel == 1);
    BOOST_CHECK(linSleepMode->simulated == false);
    BOOST_CHECK(linSleepMode->description == "entering sleep mode due to sleep mode frame");
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(LinWakeupFrame)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinWakeupFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinWakeupFrame * linWakeupFrame;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinWakeupFrame);
    linWakeupFrame = static_cast<Vector::ASC::LinWakeupFrame *>(event);
    BOOST_CHECK(isEqual(linWakeupFrame->time, 2.318672));
    BOOST_CHECK(linWakeupFrame->channel == 1);
    BOOST_CHECK(linWakeupFrame->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(linWakeupFrame->wakeupByte == 0);
    BOOST_CHECK(isEqual(linWakeupFrame->startOfFrame, 2.317671));
    BOOST_CHECK(linWakeupFrame->baudrate == 19230);
    BOOST_CHECK(linWakeupFrame->wakeupLengthInfo == 0);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(LinUnexpectedWakeup)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/LinUnexpectedWakeup.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::LinUnexpectedWakeup * linUnexpectedWakeup;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::LinUnexpectedWakeup);
    linUnexpectedWakeup = static_cast<Vector::ASC::LinUnexpectedWakeup *>(event);
    BOOST_CHECK(isEqual(linUnexpectedWakeup->time, 0.892363));
    BOOST_CHECK(linUnexpectedWakeup->channel == 1);
    BOOST_CHECK(linUnexpectedWakeup->width == 260);
    BOOST_CHECK(isEqual(linUnexpectedWakeup->startOfFrame, 0.891843));
    BOOST_CHECK(linUnexpectedWakeup->baudrate == 19230);
    delete event;

    file.close();
}

/* MOST Events */
BOOST_AUTO_TEST_CASE(Most25ControlMessageNodeMode)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most25ControlMessageNodeMode.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most25ControlMessageNodeMode * most25ControlMessageNodeMode;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most25ControlMessageNodeMode);
    most25ControlMessageNodeMode = static_cast<Vector::ASC::Most25ControlMessageNodeMode *>(event);
    BOOST_CHECK(isEqual(most25ControlMessageNodeMode->time, 0.111757));
    BOOST_CHECK(most25ControlMessageNodeMode->channel == 1);
    BOOST_CHECK(most25ControlMessageNodeMode->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(most25ControlMessageNodeMode->sourceAdr == 0x0100);
    BOOST_CHECK(most25ControlMessageNodeMode->destAdr == 0x0401);
    BOOST_CHECK(most25ControlMessageNodeMode->rType == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[0] == 0x01);
    BOOST_CHECK(most25ControlMessageNodeMode->data[1] == 0x01);
    BOOST_CHECK(most25ControlMessageNodeMode->data[2] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[3] == 0x01);
    BOOST_CHECK(most25ControlMessageNodeMode->data[4] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[5] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[6] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[7] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[8] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[9] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[10] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[11] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[12] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[13] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[14] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[15] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->data[16] == 0x00);
    BOOST_CHECK(most25ControlMessageNodeMode->state2 == 0x1250);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(Most25ControlMessageSpyMode)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most25ControlMessageSpyMode.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most25ControlMessageSpyMode * most25ControlMessageSpyMode;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::FileBaseTimestamps);

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most25ControlMessageSpyMode);
    most25ControlMessageSpyMode = static_cast<Vector::ASC::Most25ControlMessageSpyMode *>(event);
    BOOST_CHECK(isEqual(most25ControlMessageSpyMode->time, 0.113526));
    BOOST_CHECK(most25ControlMessageSpyMode->channel == 1);
    BOOST_CHECK(most25ControlMessageSpyMode->sourceAdr == 0xFFFF);
    BOOST_CHECK(most25ControlMessageSpyMode->destAdr == 0x0100);
    BOOST_CHECK(most25ControlMessageSpyMode->rType == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->data[0] == 0x01);
    BOOST_CHECK(most25ControlMessageSpyMode->data[1] == 0x01);
    BOOST_CHECK(most25ControlMessageSpyMode->data[2] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->data[3] == 0x0C);
    BOOST_CHECK(most25ControlMessageSpyMode->data[4] == 0x04);
    BOOST_CHECK(most25ControlMessageSpyMode->data[5] == 0x31);
    BOOST_CHECK(most25ControlMessageSpyMode->data[6] == 0x01);
    BOOST_CHECK(most25ControlMessageSpyMode->data[7] == 0x52);
    BOOST_CHECK(most25ControlMessageSpyMode->data[8] == 0x01);
    BOOST_CHECK(most25ControlMessageSpyMode->data[9] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->data[10] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->data[11] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->data[12] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->data[13] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->data[14] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->data[15] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->data[16] == 0x00);
    BOOST_CHECK(most25ControlMessageSpyMode->state == 0x01);
    BOOST_CHECK(most25ControlMessageSpyMode->ackNack == 0x12);
    BOOST_CHECK(most25ControlMessageSpyMode->crc == 0xAA33);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(Most25Packet)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most25Packet.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most25Packet * most25Packet;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most25Packet);
    most25Packet = static_cast<Vector::ASC::Most25Packet *>(event);
    BOOST_CHECK(isEqual(most25Packet->time, 4.445080));
    BOOST_CHECK(most25Packet->channel == 1);
    BOOST_CHECK(most25Packet->dir == Vector::ASC::Dir::Rx);
    BOOST_CHECK(most25Packet->sourceAdr == 0x0101);
    BOOST_CHECK(most25Packet->destAdr == 0x0100);
    BOOST_CHECK(most25Packet->pktState == 0x00);
    BOOST_CHECK(most25Packet->transferType == Vector::ASC::MostTransferType::Node);
    BOOST_CHECK(most25Packet->pktPrio == 0);
    BOOST_CHECK(most25Packet->pktArbitr == 0x03);
    BOOST_CHECK(most25Packet->crc2 == 0x0000);
    BOOST_CHECK(most25Packet->pktLen == 0x00A);
    BOOST_CHECK(most25Packet->data[0] == 0x52);
    BOOST_CHECK(most25Packet->data[1] == 0x01);
    BOOST_CHECK(most25Packet->data[2] == 0xE0);
    BOOST_CHECK(most25Packet->data[3] == 0x3C);
    BOOST_CHECK(most25Packet->data[4] == 0x90);
    BOOST_CHECK(most25Packet->data[5] == 0x01);
    BOOST_CHECK(most25Packet->data[6] == 0xFD);
    BOOST_CHECK(most25Packet->data[7] == 0x00);
    BOOST_CHECK(most25Packet->data[8] == 0x00);
    BOOST_CHECK(most25Packet->data[9] == 0x00);
    BOOST_CHECK(most25Packet->data[10] == 0x00);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(MostLightLockEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostLightLockEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostLightLockEvent * mostLightLockEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostLightLockEvent);
    mostLightLockEvent = static_cast<Vector::ASC::MostLightLockEvent *>(event);
    BOOST_CHECK(isEqual(mostLightLockEvent->time, 0.008638));
    BOOST_CHECK(mostLightLockEvent->channel == 1);
    BOOST_CHECK(mostLightLockEvent->llState == 1);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(MostSpecialRegisterEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostSpecialRegisterEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostSpecialRegisterEvent * mostSpecialRegisterEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostSpecialRegisterEvent);
    mostSpecialRegisterEvent = static_cast<Vector::ASC::MostSpecialRegisterEvent *>(event);
    BOOST_CHECK(isEqual(mostSpecialRegisterEvent->time, 1.4713));
    BOOST_CHECK(mostSpecialRegisterEvent->channel == 1);
    BOOST_CHECK(mostSpecialRegisterEvent->regSubType == Vector::ASC::MostRegSubType::Notify);
    BOOST_CHECK(mostSpecialRegisterEvent->regId == 0x8A);
    BOOST_CHECK(mostSpecialRegisterEvent->regValue == 0x0172);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(MostCommonRegisterEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostCommonRegisterEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostCommonRegisterEvent * mostCommonRegisterEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostCommonRegisterEvent);
    mostCommonRegisterEvent = static_cast<Vector::ASC::MostCommonRegisterEvent *>(event);
    BOOST_CHECK(isEqual(mostCommonRegisterEvent->time, 9.0500));
    BOOST_CHECK(mostCommonRegisterEvent->channel == 1);
    BOOST_CHECK(mostCommonRegisterEvent->regSubType == Vector::ASC::MostRegSubType::Unspecified);
    BOOST_CHECK(mostCommonRegisterEvent->regChip == 0x01);
    BOOST_CHECK(mostCommonRegisterEvent->regOffset == 0x0000);
    BOOST_CHECK(mostCommonRegisterEvent->regDataLen == 0x10);
    BOOST_CHECK(mostCommonRegisterEvent->data[0] == 0x00);
    BOOST_CHECK(mostCommonRegisterEvent->data[1] == 0x01);
    BOOST_CHECK(mostCommonRegisterEvent->data[2] == 0x02);
    BOOST_CHECK(mostCommonRegisterEvent->data[3] == 0x03);
    BOOST_CHECK(mostCommonRegisterEvent->data[4] == 0x04);
    BOOST_CHECK(mostCommonRegisterEvent->data[5] == 0x05);
    BOOST_CHECK(mostCommonRegisterEvent->data[6] == 0x06);
    BOOST_CHECK(mostCommonRegisterEvent->data[7] == 0x07);
    BOOST_CHECK(mostCommonRegisterEvent->data[8] == 0x08);
    BOOST_CHECK(mostCommonRegisterEvent->data[9] == 0x09);
    BOOST_CHECK(mostCommonRegisterEvent->data[10] == 0x0A);
    BOOST_CHECK(mostCommonRegisterEvent->data[11] == 0x0B);
    BOOST_CHECK(mostCommonRegisterEvent->data[12] == 0x0C);
    BOOST_CHECK(mostCommonRegisterEvent->data[13] == 0x0D);
    BOOST_CHECK(mostCommonRegisterEvent->data[14] == 0x0E);
    BOOST_CHECK(mostCommonRegisterEvent->data[15] == 0x0F);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(MostHwModeEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostHwModeEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostHwModeEvent * mostHwModeEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostHwModeEvent);
    mostHwModeEvent = static_cast<Vector::ASC::MostHwModeEvent *>(event);
    BOOST_CHECK(isEqual(mostHwModeEvent->time, 3.5600));
    BOOST_CHECK(mostHwModeEvent->channel == 1);
    BOOST_CHECK(mostHwModeEvent->hwMode == 0x01);
    BOOST_CHECK(mostHwModeEvent->hwModeMask == 0x01);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(MostNetStateEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostNetStateEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostNetStateEvent * mostNetStateEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostNetStateEvent);
    mostNetStateEvent = static_cast<Vector::ASC::MostNetStateEvent *>(event);
    BOOST_CHECK(isEqual(mostNetStateEvent->time, 1.0279));
    BOOST_CHECK(mostNetStateEvent->channel == 1);
    BOOST_CHECK(mostNetStateEvent->netStateOld == 2);
    BOOST_CHECK(mostNetStateEvent->netStateNew == 3);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(MostDataLostEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostDataLostEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostDataLostEvent * mostDataLostEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostDataLostEvent);
    mostDataLostEvent = static_cast<Vector::ASC::MostDataLostEvent *>(event);
    BOOST_CHECK(isEqual(mostDataLostEvent->time, 1.3037));
    BOOST_CHECK(mostDataLostEvent->channel == 1);
    BOOST_CHECK(mostDataLostEvent->dlInfo == 0x00000005);
    BOOST_CHECK(mostDataLostEvent->dlCtrl == 0x003F);
    BOOST_CHECK(mostDataLostEvent->dlAsync == 0x000D);
    BOOST_CHECK(isEqual(mostDataLostEvent->dlTime[0], 101.30369));
    BOOST_CHECK(isEqual(mostDataLostEvent->dlTime[1], 2223.52592));
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(MostTriggerEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostTriggerEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostTriggerEvent * mostTriggerEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostTriggerEvent);
    mostTriggerEvent = static_cast<Vector::ASC::MostTriggerEvent *>(event);
    BOOST_CHECK(isEqual(mostTriggerEvent->time, 1.3037));
    BOOST_CHECK(mostTriggerEvent->channel == 1);
    BOOST_CHECK(mostTriggerEvent->trigMode == Vector::ASC::MostTrigMode::SynchronizationSlave);
    BOOST_CHECK(mostTriggerEvent->trigHw == 4);
    BOOST_CHECK(mostTriggerEvent->trigValue[0] == 0x00000001);
    BOOST_CHECK(mostTriggerEvent->trigValue[1] == 0x00000000);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(MostStatisticEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostStatisticEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostStatisticEvent * mostStatisticEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostStatisticEvent);
    mostStatisticEvent = static_cast<Vector::ASC::MostStatisticEvent *>(event);
    BOOST_CHECK(isEqual(mostStatisticEvent->time, 2.0300));
    BOOST_CHECK(mostStatisticEvent->channel == 1);
    BOOST_CHECK(mostStatisticEvent->fr == 0);
    BOOST_CHECK(mostStatisticEvent->lt == 4);
    BOOST_CHECK(mostStatisticEvent->bl == 0);
    BOOST_CHECK(mostStatisticEvent->pk == 0);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(MostStatisticExtendedEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostStatisticExtendedEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostStatisticExtendedEvent * mostStatisticExtendedEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostStatisticExtendedEvent);
    mostStatisticExtendedEvent = static_cast<Vector::ASC::MostStatisticExtendedEvent *>(event);
    BOOST_CHECK(isEqual(mostStatisticExtendedEvent->time, 2.024742));
    BOOST_CHECK(mostStatisticExtendedEvent->channel == 2);
    BOOST_CHECK(mostStatisticExtendedEvent->codingErrors == 0x000006);
    BOOST_CHECK(mostStatisticExtendedEvent->frameCounter == 0x00A395);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(MostTxLight)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostTxLight.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostTxLight * mostTxLight;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostTxLight);
    mostTxLight = static_cast<Vector::ASC::MostTxLight *>(event);
    BOOST_CHECK(isEqual(mostTxLight->time, 0.008638));
    BOOST_CHECK(mostTxLight->channel == 1);
    BOOST_CHECK(mostTxLight->txLightState == Vector::ASC::MostTxLightState::Enabled);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(MostStressEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostStressEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostStressEvent * mostStressEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostStressEvent);
    mostStressEvent = static_cast<Vector::ASC::MostStressEvent *>(event);
    BOOST_CHECK(isEqual(mostStressEvent->time, 1.793083));
    BOOST_CHECK(mostStressEvent->channel == 1);
    BOOST_CHECK(mostStressEvent->stressMode == 2);
    BOOST_CHECK(mostStressEvent->stressState == Vector::ASC::MostStressState::Started);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(Most25AllocTable)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most25AllocTable.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most25AllocTable * most25AllocTable;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most25AllocTable);
    most25AllocTable = static_cast<Vector::ASC::Most25AllocTable *>(event);
    BOOST_CHECK(isEqual(most25AllocTable->time, 0.032775));
    BOOST_CHECK(most25AllocTable->channel == 2);
    BOOST_CHECK(most25AllocTable->allocTableSize == 0x003C);
    BOOST_CHECK(most25AllocTable->data[0x00] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x01] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x02] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x03] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x04] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x05] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x06] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x07] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x08] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x09] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x0a] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x0b] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x0c] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x0d] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x0e] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x0f] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x10] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x11] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x12] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x13] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x14] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x15] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x16] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x17] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x18] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x19] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x1a] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x1b] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x1c] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x1d] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x1e] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x1f] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x20] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x21] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x22] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x23] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x24] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x25] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x26] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x27] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x28] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x29] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x2a] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x2b] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x2c] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x2d] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x2e] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x2f] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x30] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x31] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x32] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x33] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x34] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x35] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x36] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x37] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x38] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x39] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x3a] == 0x70);
    BOOST_CHECK(most25AllocTable->data[0x3b] == 0x70);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(Most150ControlMessage)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150ControlMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most150ControlMessage * most150ControlMessage;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150ControlMessage);
    most150ControlMessage = static_cast<Vector::ASC::Most150ControlMessage *>(event);
    BOOST_CHECK(isEqual(most150ControlMessage->time, 5.7088));
    BOOST_CHECK(most150ControlMessage->channel == 1);
    BOOST_CHECK(most150ControlMessage->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(most150ControlMessage->sourceAdr == 0x0172);
    BOOST_CHECK(most150ControlMessage->destAdr == 0x03C8);
    BOOST_CHECK(most150ControlMessage->state == 0x02);
    BOOST_CHECK(most150ControlMessage->ackNack == 0x11);
    BOOST_CHECK(most150ControlMessage->transferType == Vector::ASC::MostTransferType::Node);
    BOOST_CHECK(most150ControlMessage->pack == 0x22);
    BOOST_CHECK(most150ControlMessage->priority == 0x01);
    BOOST_CHECK(most150ControlMessage->pIndex == 0x33);
    BOOST_CHECK(most150ControlMessage->crc2 == 0xAABB);
    BOOST_CHECK(most150ControlMessage->cAck == 0x44);
    BOOST_CHECK(most150ControlMessage->rsvdUl == 0x00);
    BOOST_CHECK(most150ControlMessage->msg150Len == 0x08);
    BOOST_CHECK(most150ControlMessage->data[0] == 0x11);
    BOOST_CHECK(most150ControlMessage->data[1] == 0x22);
    BOOST_CHECK(most150ControlMessage->data[2] == 0x33);
    BOOST_CHECK(most150ControlMessage->data[3] == 0x34);
    BOOST_CHECK(most150ControlMessage->data[4] == 0x00);
    BOOST_CHECK(most150ControlMessage->data[5] == 0x02);
    BOOST_CHECK(most150ControlMessage->data[6] == 0x11);
    BOOST_CHECK(most150ControlMessage->data[7] == 0x22);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(Most150ControlMessageFragment)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150ControlMessageFragment.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most150ControlMessageFragment * most150ControlMessageFragment;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150ControlMessageFragment);
    most150ControlMessageFragment = static_cast<Vector::ASC::Most150ControlMessageFragment *>(event);
    BOOST_CHECK(isEqual(most150ControlMessageFragment->time, 5.7088));
    BOOST_CHECK(most150ControlMessageFragment->channel == 1);
    BOOST_CHECK(most150ControlMessageFragment->frgMask == 0x01020304);
    BOOST_CHECK(most150ControlMessageFragment->sourceAdr == 0x0172);
    BOOST_CHECK(most150ControlMessageFragment->destAdr == 0x03C8);
    BOOST_CHECK(most150ControlMessageFragment->ackNack == 0x11);
    BOOST_CHECK(most150ControlMessageFragment->pAck == 0x22);
    BOOST_CHECK(most150ControlMessageFragment->priority == 0x01);
    BOOST_CHECK(most150ControlMessageFragment->pIndex == 0x33);
    BOOST_CHECK(most150ControlMessageFragment->crc2 == 0xAABB);
    BOOST_CHECK(most150ControlMessageFragment->cAck == 0x44);
    BOOST_CHECK(most150ControlMessageFragment->rsvdUl == 0x00);
    BOOST_CHECK(most150ControlMessageFragment->frgDataLen == 0x0006);
    BOOST_CHECK(most150ControlMessageFragment->frgDataLenAnnounced == 0x0210);
    BOOST_CHECK(most150ControlMessageFragment->firstDataLen == 0x06);
    BOOST_CHECK(most150ControlMessageFragment->data[0] == 0x01);
    BOOST_CHECK(most150ControlMessageFragment->data[1] == 0x02);
    BOOST_CHECK(most150ControlMessageFragment->data[2] == 0x03);
    BOOST_CHECK(most150ControlMessageFragment->data[3] == 0x04);
    BOOST_CHECK(most150ControlMessageFragment->data[4] == 0x05);
    BOOST_CHECK(most150ControlMessageFragment->data[5] == 0x06);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(Most150Packet)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150Packet.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most150Packet * most150Packet;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150Packet);
    most150Packet = static_cast<Vector::ASC::Most150Packet *>(event);
    BOOST_CHECK(isEqual(most150Packet->time, 5.7088));
    BOOST_CHECK(most150Packet->channel == 1);
    BOOST_CHECK(most150Packet->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(most150Packet->sourceAdr == 0x0172);
    BOOST_CHECK(most150Packet->destAdr == 0x03C8);
    BOOST_CHECK(most150Packet->state == 0x02);
    BOOST_CHECK(most150Packet->ackNack == 0x11);
    BOOST_CHECK(most150Packet->transferType == Vector::ASC::MostTransferType::Node);
    BOOST_CHECK(most150Packet->pAck == 0x00);
    BOOST_CHECK(most150Packet->rsvdUc == 0x00);
    BOOST_CHECK(most150Packet->pIndex == 0x33);
    BOOST_CHECK(most150Packet->crc2 == 0xAABB);
    BOOST_CHECK(most150Packet->cAck == 0x44);
    BOOST_CHECK(most150Packet->rsvdUl == 0x00);
    BOOST_CHECK(most150Packet->pkt150Len == 0x08);
    BOOST_CHECK(most150Packet->data[0] == 0x11);
    BOOST_CHECK(most150Packet->data[1] == 0x22);
    BOOST_CHECK(most150Packet->data[2] == 0x33);
    BOOST_CHECK(most150Packet->data[3] == 0x34);
    BOOST_CHECK(most150Packet->data[4] == 0x00);
    BOOST_CHECK(most150Packet->data[5] == 0x02);
    BOOST_CHECK(most150Packet->data[6] == 0x11);
    BOOST_CHECK(most150Packet->data[7] == 0x22);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(Most150PacketFragment)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150PacketFragment.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most150PacketFragment * most150PacketFragment;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150PacketFragment);
    most150PacketFragment = static_cast<Vector::ASC::Most150PacketFragment *>(event);
    BOOST_CHECK(isEqual(most150PacketFragment->time, 5.7088));
    BOOST_CHECK(most150PacketFragment->channel == 1);
    BOOST_CHECK(most150PacketFragment->frgMask == 0x01020304);
    BOOST_CHECK(most150PacketFragment->sourceAdr == 0x0172);
    BOOST_CHECK(most150PacketFragment->destAdr == 0x03C8);
    BOOST_CHECK(most150PacketFragment->ackNack == 0x11);
    BOOST_CHECK(most150PacketFragment->pAck == 0x22);
    BOOST_CHECK(most150PacketFragment->rsvdUc == 0x01);
    BOOST_CHECK(most150PacketFragment->pIndex == 0x33);
    BOOST_CHECK(most150PacketFragment->crc2 == 0xAABB);
    BOOST_CHECK(most150PacketFragment->cAck == 0x44);
    BOOST_CHECK(most150PacketFragment->rsvdUl == 0x00);
    BOOST_CHECK(most150PacketFragment->frgDataLen == 0x0006);
    BOOST_CHECK(most150PacketFragment->frgDataLenAnnounced == 0x0210);
    BOOST_CHECK(most150PacketFragment->firstDataLen == 0x06);
    BOOST_CHECK(most150PacketFragment->data[0] == 0x01);
    BOOST_CHECK(most150PacketFragment->data[1] == 0x02);
    BOOST_CHECK(most150PacketFragment->data[2] == 0x03);
    BOOST_CHECK(most150PacketFragment->data[3] == 0x04);
    BOOST_CHECK(most150PacketFragment->data[4] == 0x05);
    BOOST_CHECK(most150PacketFragment->data[5] == 0x06);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(MostEthernetPacket)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostEthernetPacket.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostEthernetPacket * mostEthernetPacket;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostEthernetPacket);
    mostEthernetPacket = static_cast<Vector::ASC::MostEthernetPacket *>(event);
    BOOST_CHECK(isEqual(mostEthernetPacket->time, 5.7088));
    BOOST_CHECK(mostEthernetPacket->channel == 1);
    BOOST_CHECK(mostEthernetPacket->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(mostEthernetPacket->sourceMacAdr == 0x010203040506);
    BOOST_CHECK(mostEthernetPacket->destMacAdr == 0x112233445566);
    BOOST_CHECK(mostEthernetPacket->state == 0x02);
    BOOST_CHECK(mostEthernetPacket->ackNack == 0x11);
    BOOST_CHECK(mostEthernetPacket->transferType == Vector::ASC::MostTransferType::Node);
    BOOST_CHECK(mostEthernetPacket->pAck == 0x22);
    BOOST_CHECK(mostEthernetPacket->crc4 == 0xAABBCCDD);
    BOOST_CHECK(mostEthernetPacket->cAck == 0x44);
    BOOST_CHECK(mostEthernetPacket->rsvdUl == 0x00);
    BOOST_CHECK(mostEthernetPacket->pktEthLen == 0x08);
    BOOST_CHECK(mostEthernetPacket->data[0] == 0x11);
    BOOST_CHECK(mostEthernetPacket->data[1] == 0x22);
    BOOST_CHECK(mostEthernetPacket->data[2] == 0x33);
    BOOST_CHECK(mostEthernetPacket->data[3] == 0x34);
    BOOST_CHECK(mostEthernetPacket->data[4] == 0x00);
    BOOST_CHECK(mostEthernetPacket->data[5] == 0x02);
    BOOST_CHECK(mostEthernetPacket->data[6] == 0x11);
    BOOST_CHECK(mostEthernetPacket->data[7] == 0x22);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(MostEthernetPacketFragment)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostEthernetPacketFragment.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostEthernetPacketFragment * mostEthernetPacketFragment;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostEthernetPacketFragment);
    mostEthernetPacketFragment = static_cast<Vector::ASC::MostEthernetPacketFragment *>(event);
    BOOST_CHECK(isEqual(mostEthernetPacketFragment->time, 5.7088));
    BOOST_CHECK(mostEthernetPacketFragment->channel == 1);
    BOOST_CHECK(mostEthernetPacketFragment->frgMask == 0x01020304);
    BOOST_CHECK(mostEthernetPacketFragment->sourceMacAdr == 0x010203040506);
    BOOST_CHECK(mostEthernetPacketFragment->destMacAdr == 0x112233445566);
    BOOST_CHECK(mostEthernetPacketFragment->ackNack == 0x11);
    BOOST_CHECK(mostEthernetPacketFragment->pAck == 0x01);
    BOOST_CHECK(mostEthernetPacketFragment->crc4 == 0xAABBCCDD);
    BOOST_CHECK(mostEthernetPacketFragment->cAck == 0x44);
    BOOST_CHECK(mostEthernetPacketFragment->rsvdUl == 0x00);
    BOOST_CHECK(mostEthernetPacketFragment->frgDataLen == 0x0006);
    BOOST_CHECK(mostEthernetPacketFragment->frgDataLenAnnounced == 0x0210);
    BOOST_CHECK(mostEthernetPacketFragment->firstDataLen == 0x06);
    BOOST_CHECK(mostEthernetPacketFragment->data[0] == 0x01);
    BOOST_CHECK(mostEthernetPacketFragment->data[1] == 0x02);
    BOOST_CHECK(mostEthernetPacketFragment->data[2] == 0x03);
    BOOST_CHECK(mostEthernetPacketFragment->data[3] == 0x04);
    BOOST_CHECK(mostEthernetPacketFragment->data[4] == 0x05);
    BOOST_CHECK(mostEthernetPacketFragment->data[5] == 0x06);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(MostSystemEvent)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostSystemEvent.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostSystemEvent * mostSystemEvent;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostSystemEvent);
    mostSystemEvent = static_cast<Vector::ASC::MostSystemEvent *>(event);
    BOOST_CHECK(isEqual(mostSystemEvent->time, 1.0279));
    BOOST_CHECK(mostSystemEvent->channel == 1);
    BOOST_CHECK(mostSystemEvent->sysId == Vector::ASC::MostSysId::SystemLock);
    BOOST_CHECK(mostSystemEvent->sysValue == 0x0001);
    BOOST_CHECK(mostSystemEvent->sysValueOld == 0x0000);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(Most150AllocTable)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most150AllocTable.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most150AllocTable * most150AllocTable;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150AllocTable);
    most150AllocTable = static_cast<Vector::ASC::Most150AllocTable *>(event);
    BOOST_CHECK(isEqual(most150AllocTable->time, 44.814398));
    BOOST_CHECK(most150AllocTable->channel == 1);
    BOOST_CHECK(most150AllocTable->at150EventModeFlags == 0x00);
    BOOST_CHECK(most150AllocTable->freeBytes == 0x002E);
    BOOST_CHECK(most150AllocTable->at150Size == 0x0004);
    BOOST_CHECK(most150AllocTable->w[0] == 0x010B);
    BOOST_CHECK(most150AllocTable->w[1] == 0x0004);
    BOOST_CHECK(most150AllocTable->w[2] == 0x4151);
    BOOST_CHECK(most150AllocTable->w[3] == 0x0046);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most150AllocTable);
    most150AllocTable = static_cast<Vector::ASC::Most150AllocTable *>(event);
    BOOST_CHECK(isEqual(most150AllocTable->time, 50.126855));
    BOOST_CHECK(most150AllocTable->channel == 1);
    BOOST_CHECK(most150AllocTable->at150EventModeFlags == 0x00);
    BOOST_CHECK(most150AllocTable->freeBytes == 0x0074);
    BOOST_CHECK(most150AllocTable->at150Size == 0x0004);
    BOOST_CHECK(most150AllocTable->w[0] == 0x010B);
    BOOST_CHECK(most150AllocTable->w[1] == 0x0004);
    BOOST_CHECK(most150AllocTable->w[2] == 0x8151);
    BOOST_CHECK(most150AllocTable->w[3] == 0x0046);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(Most50ControlMessage)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most50ControlMessage.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most50ControlMessage * most50ControlMessage;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most50ControlMessage);
    most50ControlMessage = static_cast<Vector::ASC::Most50ControlMessage *>(event);
    BOOST_CHECK(isEqual(most50ControlMessage->time, 0.200000));
    BOOST_CHECK(most50ControlMessage->channel == 1);
    BOOST_CHECK(most50ControlMessage->dir == Vector::ASC::Dir::Rx);
    BOOST_CHECK(most50ControlMessage->sourceAdr == 0xEF00);
    BOOST_CHECK(most50ControlMessage->destAdr == 0x0101);
    BOOST_CHECK(most50ControlMessage->state == 0x01);
    BOOST_CHECK(most50ControlMessage->ackNack == 0x00);
    BOOST_CHECK(most50ControlMessage->transferType == Vector::ASC::MostTransferType::Spy);
    BOOST_CHECK(most50ControlMessage->rsvdUc1 == 0x00);
    BOOST_CHECK(most50ControlMessage->priority == 0x00);
    BOOST_CHECK(most50ControlMessage->rsvdUc2 == 0x00);
    BOOST_CHECK(most50ControlMessage->crc2 == 0x5678);
    BOOST_CHECK(most50ControlMessage->rsvdUc3 == 0x00);
    BOOST_CHECK(most50ControlMessage->rsvdUl == 0x00);
    BOOST_CHECK(most50ControlMessage->msg50Len == 0x09);
    BOOST_CHECK(most50ControlMessage->data[0] == 0x11);
    BOOST_CHECK(most50ControlMessage->data[1] == 0x01);
    BOOST_CHECK(most50ControlMessage->data[2] == 0x22);
    BOOST_CHECK(most50ControlMessage->data[3] == 0x23);
    BOOST_CHECK(most50ControlMessage->data[4] == 0x04);
    BOOST_CHECK(most50ControlMessage->data[5] == 0x11);
    BOOST_CHECK(most50ControlMessage->data[6] == 0x22);
    BOOST_CHECK(most50ControlMessage->data[7] == 0x33);
    BOOST_CHECK(most50ControlMessage->data[8] == 0x44);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(Most50Packet)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/Most50Packet.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::Most50Packet * most50Packet;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::Most50Packet);
    most50Packet = static_cast<Vector::ASC::Most50Packet *>(event);
    BOOST_CHECK(isEqual(most50Packet->time, 5.7088));
    BOOST_CHECK(most50Packet->channel == 1);
    BOOST_CHECK(most50Packet->dir == Vector::ASC::Dir::Tx);
    BOOST_CHECK(most50Packet->sourceAdr == 0x0172);
    BOOST_CHECK(most50Packet->destAdr == 0x03C8);
    BOOST_CHECK(most50Packet->state == 0x02);
    BOOST_CHECK(most50Packet->ackNack == 0x11);
    BOOST_CHECK(most50Packet->transferType == Vector::ASC::MostTransferType::Node);
    BOOST_CHECK(most50Packet->rsvdUc1 == 0x00);
    BOOST_CHECK(most50Packet->rsvdUc2 == 0x00);
    BOOST_CHECK(most50Packet->rsvdUc3 == 0x00);
    BOOST_CHECK(most50Packet->crc2 == 0xAABB);
    BOOST_CHECK(most50Packet->rsvdUc4 == 0x00);
    BOOST_CHECK(most50Packet->rsvdUl == 0x00);
    BOOST_CHECK(most50Packet->pktLen == 0x08);
    BOOST_CHECK(most50Packet->data[0] == 0x11);
    BOOST_CHECK(most50Packet->data[1] == 0x22);
    BOOST_CHECK(most50Packet->data[2] == 0x33);
    BOOST_CHECK(most50Packet->data[3] == 0x34);
    BOOST_CHECK(most50Packet->data[4] == 0x00);
    BOOST_CHECK(most50Packet->data[5] == 0x02);
    BOOST_CHECK(most50Packet->data[6] == 0x11);
    BOOST_CHECK(most50Packet->data[7] == 0x22);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(MostEcl)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/MostEcl.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::MostEcl * mostEcl;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::MostEcl);
    mostEcl = static_cast<Vector::ASC::MostEcl *>(event);
    BOOST_CHECK(isEqual(mostEcl->time, 0.009068));
    BOOST_CHECK(mostEcl->eclMode == Vector::ASC::MostEclMode::Discrete);
    BOOST_CHECK(mostEcl->eclState == Vector::ASC::MostEclState::LineHigh);
    delete event;

    file.close();
}

/* TP/Diagnostics Events */
BOOST_AUTO_TEST_CASE(TpDiagPrefix)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/TpDiagPrefix.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::TpDiagPrefix * tpDiagPrefix;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::TpDiagPrefix);
    tpDiagPrefix = static_cast<Vector::ASC::TpDiagPrefix *>(event);
    BOOST_CHECK(tpDiagPrefix->canChannel == 1);
    BOOST_CHECK(tpDiagPrefix->connectionId == 0x07);
    BOOST_CHECK(tpDiagPrefix->type == Vector::ASC::TpDiagType::Atom);
    BOOST_CHECK(tpDiagPrefix->source == "Any_ECU_example");
    BOOST_CHECK(tpDiagPrefix->destination == "<tester>");
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(TpDiagSingleFrame)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/TpDiagSingleFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::TpDiagSingleFrame * tpDiagSingleFrame;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::TpDiagSingleFrame);
    tpDiagSingleFrame = static_cast<Vector::ASC::TpDiagSingleFrame *>(event);
    BOOST_CHECK(tpDiagSingleFrame->length == 0x02);
    BOOST_CHECK(tpDiagSingleFrame->transportedBytes[0] == 0x1A);
    BOOST_CHECK(tpDiagSingleFrame->transportedBytes[1] == 0x90);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(TpDiagFirstFrame)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/TpDiagFirstFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::TpDiagFirstFrame * tpDiagFirstFrame;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::TpDiagFirstFrame);
    tpDiagFirstFrame = static_cast<Vector::ASC::TpDiagFirstFrame *>(event);
    BOOST_CHECK(tpDiagFirstFrame->length == 0x000C);
    BOOST_CHECK(tpDiagFirstFrame->transportedBytes[0] == 0x5A);
    BOOST_CHECK(tpDiagFirstFrame->transportedBytes[1] == 0x90);
    BOOST_CHECK(tpDiagFirstFrame->transportedBytes[2] == 0x98);
    BOOST_CHECK(tpDiagFirstFrame->transportedBytes[3] == 0x76);
    BOOST_CHECK(tpDiagFirstFrame->transportedBytes[4] == 0x54);
    BOOST_CHECK(tpDiagFirstFrame->transportedBytes[5] == 0x32);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(TpDiagConsecutiveFrame)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/TpDiagConsecutiveFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::TpDiagConsecutiveFrame * tpDiagConsecutiveFrame;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::TpDiagConsecutiveFrame);
    tpDiagConsecutiveFrame = static_cast<Vector::ASC::TpDiagConsecutiveFrame *>(event);
    BOOST_CHECK(tpDiagConsecutiveFrame->sn == 1);
    BOOST_CHECK(tpDiagConsecutiveFrame->transportedBytes[0] == 0x10);
    BOOST_CHECK(tpDiagConsecutiveFrame->transportedBytes[1] == 0x00);
    BOOST_CHECK(tpDiagConsecutiveFrame->transportedBytes[2] == 0x99);
    BOOST_CHECK(tpDiagConsecutiveFrame->transportedBytes[3] == 0x99);
    BOOST_CHECK(tpDiagConsecutiveFrame->transportedBytes[4] == 0x00);
    BOOST_CHECK(tpDiagConsecutiveFrame->transportedBytes[5] == 0x01);
    BOOST_CHECK(tpDiagConsecutiveFrame->transportedBytes[6] == 0x00);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(TpDiagFlowControlFrame)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/TpDiagFlowControlFrame.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::TpDiagFlowControlFrame * tpDiagFlowControlFrame;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::TpDiagFlowControlFrame);
    tpDiagFlowControlFrame = static_cast<Vector::ASC::TpDiagFlowControlFrame *>(event);
    BOOST_CHECK(tpDiagFlowControlFrame->fcType == Vector::ASC::TpDiagFcType::Cts);
    BOOST_CHECK(tpDiagFlowControlFrame->bs == 0x00);
    BOOST_CHECK(tpDiagFlowControlFrame->stMin == 0x14);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(TpDiagRequest)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/TpDiagRequest.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::TpDiagRequest * tpDiagRequest;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::TpDiagRequest);
    tpDiagRequest = static_cast<Vector::ASC::TpDiagRequest *>(event);
    BOOST_CHECK(isEqual(tpDiagRequest->time, 1.765500));
    BOOST_CHECK(tpDiagRequest->ecuQualifier == "Any_ECU_example");
    BOOST_CHECK(tpDiagRequest->byteSequence[0] == 0x1A);
    BOOST_CHECK(tpDiagRequest->byteSequence[1] == 0x90);
    delete event;

    file.close();
}

BOOST_AUTO_TEST_CASE(StartOfMeasurement)
{
    Vector::ASC::File file;
    file.open(CMAKE_CURRENT_SOURCE_DIR "/events/StartOfMeasurement.asc");
    BOOST_REQUIRE(file.is_open());

    Vector::ASC::Event * event;
    Vector::ASC::StartOfMeasurement * startOfMeasurement;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::StartOfMeasurement);
    startOfMeasurement = static_cast<Vector::ASC::StartOfMeasurement *>(event);
    BOOST_CHECK(isEqual(startOfMeasurement->time, 0.000000));
    BOOST_CHECK(startOfMeasurement->language == Vector::ASC::File::Language::De);
    delete event;

    event = file.read();
    BOOST_REQUIRE(event != nullptr);
    BOOST_REQUIRE(event->eventType == Vector::ASC::Event::EventType::StartOfMeasurement);
    startOfMeasurement = static_cast<Vector::ASC::StartOfMeasurement *>(event);
    BOOST_CHECK(isEqual(startOfMeasurement->time, 1.000000));
    BOOST_CHECK(startOfMeasurement->language == Vector::ASC::File::Language::En);
    delete event;

    file.close();
}
