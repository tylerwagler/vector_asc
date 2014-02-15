#include "Writer.h"

#include <clocale>
#include <ctime>
#include <iomanip>
#include <iostream>

#include "ISO/ISO11898/Message.h"
#include "ISO/ISO11898/Statistics.h"

namespace Vector {
namespace ASC {

static constexpr char endl[] = "\n";

Writer::Writer() :
    std::ofstream(),
    numberBase(NumberBase::Hex),
    timeStampMode(TimeStampMode::Absolute),
    internalEventsLogged(false),
    version(Version::Ver_unknown),  // default: the newest, what else...
    triggerTime(),
    lastEventTime(),
    txDrivers()
{
    std::setlocale(LC_NUMERIC, "C");
    std::setlocale(LC_TIME, "de_DE.utf8");
}

Writer::~Writer()
{
}

void Writer::writeEvent(core::Event * event)
{
    if (ISO::ISO11898::Message * message = dynamic_cast<ISO::ISO11898::Message *>(event)) {
        if (message->isData()) {
            canMessageEvent(message);
            return;
        }

        if (message->isRemote()) {
            canRemoteFrameEvent(message);
            return;
        }

        if (message->type == ISO::ISO11898::Message::Type::Error) {
            canErrorFrame(message);
            return;
        }
    }

    if (ISO::ISO11898::Statistics * statistics = dynamic_cast<ISO::ISO11898::Statistics *>(event)) {
        canBusStatisticsEvent(statistics);
        return;
    }
}

double Writer::getTimeStamp(core::TimePoint & timePoint)
{
    core::Duration tp;

    switch(timeStampMode) {
    case TimeStampMode::Absolute:
        tp = timePoint - triggerTime;
        break;
    case TimeStampMode::Relative:
        tp = timePoint - lastEventTime;
        break;
    }

    lastEventTime = timePoint;

    return tp.count();
}

std::string Writer::getChannel(core::Event * event)
{
    std::string channelName;

    if (auto driver = event->source.lock()) {
        channelName = driver->channelName;
    }

    return channelName;
}

void Writer::fileHeader(core::TimePoint & fileTime)
{
    triggerTime = fileTime;
    lastEventTime = triggerTime;
    std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(fileTime.time_since_epoch());
    time_t t = sec.count(); // core::Clock::to_time_t(sec);

    constexpr char wday_name[7][4] = {
        "Son", "Mon", "Die", "Mit", "Don", "Fre", "Sam"
    };
    constexpr char mon_name[12][4] = {
        "Jan", "Feb", "Mar", "Apr", "Mai", "Jun",
        "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"
    };
    struct tm * tm = localtime(&t);

    static char timeStr[26];
      sprintf(timeStr, "%.3s %.3s%3d %.2d:%.2d:%.2d %d",
        wday_name[tm->tm_wday], mon_name[tm->tm_mon], tm->tm_mday,
        tm->tm_hour, tm->tm_min, tm->tm_sec,
        1900 + tm->tm_year);

    *this << "date " << timeStr << endl;

    *this << "base ";
    switch(numberBase) {
    case NumberBase::Hex:
        *this << "hex";
        break;
    case NumberBase::Dec:
        *this << "dec";
        break;
    }
    *this << "  timestamps ";
    switch(timeStampMode) {
    case TimeStampMode::Absolute:
        *this << "absolute";
        break;
    case TimeStampMode::Relative:
        *this << "relative";
        break;
    }
    *this << endl;

    if (!internalEventsLogged) {
        *this << "no ";
    }
    *this << "internal events logged" << endl;

    if (version != Version::Ver_unknown) {
        unsigned int versionMajor = ((unsigned int) version >> 16) & 0xff;
        unsigned int versionMinor = ((unsigned int) version >>  8) & 0xff;
        unsigned int versionPatch = ((unsigned int) version >>  0) & 0xff;
        *this << "// version " << versionMajor << '.' << versionMinor << '.' << versionPatch << endl;
    }
}

void Writer::fileSplitInformation(core::Duration lastTime, std::string & lastFilename)
{
    // split information
    if (!lastFilename.empty()) {
        *this << "// " << lastTime.count() << " previous log file: " << lastFilename << endl;
    }
}

void Writer::canMessageEvent(ISO::ISO11898::Message * message)
{
    static std::string emptyStr("");

    /* check if drivers are registered as Tx nodes */
    bool txDir = false;
    if (auto drv1 = message->source.lock()) {
        for(auto i = txDrivers.begin(); i!= txDrivers.end(); ++i) {
            if (auto drv2 = i->lock()) {
                txDir = (drv1 == drv2);
            }
        }
    }

    /* get channel */
    std::string channelName = getChannel(message);

    /* send message */
    canMessageEvent(message->time, channelName,
                    message->identifier, message->isExtended(),
                    txDir, message->dataLengthCode, message->data,
                    message->data.size(), message->bitCount,
                    emptyStr);
}

/* CAN Message Event */
/* <Time> <Channel> <ID> <Dir> d <DLC> <D0> <D1>...<D8> <MessageFlags> */
/* <Time> <Channel> <ID> <Dir> d <DLC> <D0> <D1>...<D8> Length = <MessageDuration> BitCount = <MessageLength> <MessageFlags> */
void Writer::canMessageEvent(core::TimePoint & eventTime, std::string & channel, unsigned int id, bool extended, bool dirTx, unsigned short dlc, std::vector<unsigned short> & data, unsigned int length, unsigned int bitCount, std::string & messageFlags)
{
    /* <Time> */
    *this << std::setw(11) << std::setfill(' ');
    *this << std::fixed << getTimeStamp(eventTime);

    /* <Channel> */
    *this << ' ' << channel;

    /* <ID> */
    *this << ' ';
    *this << std::setw(4) << std::setfill(' ') << std::hex << id;
    *this << (extended ? 'x' : ' ');

    /* space */
    *this << "           ";

    /* <Dir> */
    *this << ' ' << (dirTx ? "Tx" : "Rx");

    /* space */
    *this << "  ";

    /* d */
    *this << ' ' << "d";

    /* <DLC> */
    *this << ' ' << std::hex << dlc;

    /* <D0> <D1>...<D8> */
    for(std::vector<unsigned short>::iterator it=data.begin(); it!=data.end(); ++it) {
        *this << ' ';
        *this << std::setw(2) << std::setfill('0') << std::setiosflags(std::ifstream::uppercase | std::ifstream::right);
        *this << *it;
    }
    *this << std::dec << std::setw(0);

    /* Length = <MessageDuration> BitCount = <MessageLength> */
    if (version >= Version::Ver_7_5) {
        *this << " Length = " << length;
        *this << " BitCount = " << bitCount;
    }

    /* <MessageFlags> */
    if (!messageFlags.empty()) {
        *this << ' ' << messageFlags;
    }

    *this << endl;
}

void Writer::canRemoteFrameEvent(ISO::ISO11898::Message * message)
{
    /* get channel */
    std::string channelName = getChannel(message);

    canRemoteFrameEvent(message->time, channelName,
                        message->identifier, message->isExtended(),
                        false);
}

/* CAN Remote Frame Event */
/* <Time> <Channel> <ID> <Dir> r */
void Writer::canRemoteFrameEvent(core::TimePoint & eventTime, std::string & channel, unsigned int id, bool extended, bool dirTx)
{
    *this << getTimeStamp(eventTime);
    *this << ' ' << channel;
    *this << ' ' << std::hex << id << std::dec;
    if (extended) {
        *this << "x";
    }
    *this << ' ' << (dirTx ? "Tx" : "Rx");
    *this << ' ' << "r";
    *this << endl;
}

void Writer::canErrorFrame(ISO::ISO11898::Message * message)
{
    /* get channel */
    std::string channelName = getChannel(message);

    canErrorFrame(message->time, channelName);
}


/* CAN Error Frame */
/* <Time> <Channel> ErrorFrame */
/* <Time> <Channel> ErrorFrame ECC:<ECC> */
/* <Time> <Channel> ErrorFrame Flags = <flags> CodeExt = <codeExt> Code = <code> ID = <ID> DLC = <DLC> Position = <Position> Length = <Length> */
void Writer::canErrorFrame(core::TimePoint & eventTime, std::string & channel, bool sja1000, unsigned short ecc, bool canCore, unsigned int flags, unsigned int codeExt, unsigned int code, unsigned int id, bool extended, unsigned int dlc, unsigned int position, unsigned int length)
{
    *this << getTimeStamp(eventTime);
    *this << ' ' << channel;
    *this << " ErrorFrame";

    if (version >= Version::Ver_7_5) {
        if (sja1000) {
            *this << " ECC:";
            *this << ((ecc >> 7) & 1);
            *this << ((ecc >> 6) & 1);
            *this << ((ecc >> 5) & 1);
            *this << ((ecc >> 4) & 1);
            *this << ((ecc >> 3) & 1);
            *this << ((ecc >> 2) & 1);
            *this << ((ecc >> 1) & 1);
            *this << ((ecc >> 0) & 1);
        }
        if (canCore) {
            *this << " Flags = 0x" << std::hex << flags;
            *this << " CodeExt = 0x" << std::hex << codeExt;
            *this << " Code = 0x" << std::hex << code;
            *this << " ID = " << std::hex << id;
            if (extended) {
                *this << "x";
            }
            *this << " DLC = " << std::hex << dlc << std::dec;
            *this << " Position = " << position;
            *this << " Length = " << length;
        }
    }

    *this << endl;
}

void Writer::canBusStatisticsEvent(ISO::ISO11898::Statistics * statistics)
{
    /* get channel */
    std::string channelName = getChannel(statistics);

    canBusStatisticsEvent(statistics->time, channelName,
                          statistics->standardDataFrameCount,
                          statistics->standardRemoteFrameCount,
                          statistics->extendedDataFrameCount,
                          statistics->extendedRemoteFrameCount,
                          statistics->errorFrameCount,
                          statistics->overloadFrameCount,
                          statistics->busload);
}

/* CAN Bus Statistics Event */
/* <Time> <Channel> Statistic: D <StatNumber> R <StatNumber> XD <StatNumber> XR <StatNumber> E <StatNumber> O <StatNumber> B <StatPercent>% */
void Writer::canBusStatisticsEvent(core::TimePoint & eventTime, std::string & channel, unsigned int d, unsigned int r, unsigned int xd, unsigned int xr, unsigned int e, unsigned int o, double b)
{
    *this << getTimeStamp(eventTime);
    *this << ' ' << channel;
    *this << " Statistics: ";
    *this << " D " << d;
    *this << " R " << r;
    *this << " XD " << xd;
    *this << " XR " << xr;
    *this << " E " << e;
    *this << " O " << o;
    *this << " B " << b << "%";
    *this << endl;
}

/* CAN Error Event */
/* <Time> CAN <Channel> Status:<Error> */
void Writer::canErrorEvent(core::TimePoint & eventTime, std::string & channel, std::string & status)
{
    *this << getTimeStamp(eventTime);
    *this << " CAN";
    *this << ' ' << channel;
    *this << " Status:" << status;
    *this << endl;
}

/* CAN Overload Frame Event */
/* <Time> <Channel> OverloadFrame */
void Writer::canOverloadFrameEvent(core::TimePoint & eventTime, std::string & channel)
{
    *this << getTimeStamp(eventTime);
    *this << ' ' << channel;
    *this << " OverloadFrame";
    *this << endl;
}

/* Log Trigger Event */
/* <Time> log trigger event */
void Writer::logTriggerEvent(core::TimePoint & eventTime)
{
    *this << getTimeStamp(eventTime);
    *this << " log trigger event";
    *this << endl;
}

/* Log Direct Start Event */
/* <Time> log direct start (<PreTrigger>ms) */
void Writer::logDirectStartEvent(core::TimePoint & eventTime, unsigned int preTrigger)
{
    *this << getTimeStamp(eventTime);
    *this << "log direct start";
    *this << " (" << preTrigger << "ms)";
    *this << endl;
}

/* Log Direct Stop Event */
/* <Time> log direct stop (<PostTrigger>ms) */
void Writer::logDirectStopEvent(core::TimePoint & eventTime, unsigned int postTrigger)
{
    *this << getTimeStamp(eventTime);
    *this << " log direct stop";
    *this << " (" << postTrigger << "ms)";
    *this << endl;
}

/* Begin Triggerblock Event */
/* Begin Triggerblock <WeekDay> <Month> <Date> <FullTime> <Year> */
void Writer::beginTriggerblockEvent(core::TimePoint & eventTime)
{
    triggerTime = eventTime;
    std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(eventTime.time_since_epoch());
    time_t t = sec.count(); // core::Clock::to_time_t(eventTime);
    *this << "Begin Triggerblock";
    *this << ' ' << std::ctime(&t) << endl;
    *this << endl;
}

/* End Triggerblock Event */
/* End TriggerBlock */
void Writer::endTriggerblockEvent(void)
{
    *this << "End TriggerBlock";
    *this << endl;
}

/* Environment Variables Event */
/* <Time> <evname> := <value> */
void Writer::environmentVariablesEvent(core::TimePoint & eventTime, std::string & evname, std::string & value)
{
    *this << getTimeStamp(eventTime);
    *this << ' ' << evname;
    *this << " := " << value;
    *this << endl;
}

/* System Variables Event */
/* <Time> SV: <svtype> <flag> <flag> <path> = <value> */
/* <Time> SV: <svtype> <flag> <flag> <path> = <valuetype><count> <value> */
void Writer::systemVariablesEvent(core::TimePoint & eventTime, unsigned int svtype, unsigned int flag1, unsigned int flag2, std::string & path, std::string & value)
{
    *this << getTimeStamp(eventTime);
    *this << " SV:";
    *this << ' ' << svtype;
    *this << ' ' << flag1;
    *this << ' ' << flag2;
    *this << ' ' << path;
    *this << " = " << value;
    *this << endl;
}

/* Macro Signal Event: CAN, LIN and FlexRay */
/* <Time> <bussystem> <channel> <node>::<message>::<signal> = <value> */
void Writer::macroSignalEvent(core::TimePoint & eventTime, std::string & bussystem, std::string & channel, std::string & node, std::string & message, std::string & signal, std::string & value)
{
    *this << getTimeStamp(eventTime);
    *this << ' ' << bussystem << channel;
    *this << ' ' << node << ':' << message << ':' << signal;
    *this << " = " << value;
    *this << endl;
}

/* GPS Event */
/* <Time> GPS device: <channel> La: <latitude> Lo: <longitude> Alt: <altitude> Sp: <speed> Co: <course> */
void Writer::gpsEvent(core::TimePoint & eventTime, std::string & channel, double latitude, double longitude, double altitude, double speed, double course)
{
    *this << getTimeStamp(eventTime);
    *this << " GPS device: " << channel;
    *this << " La: " << latitude;
    *this << " Lo: " << longitude;
    *this << " Alt: " << altitude;
    *this << " Sp: " << speed;
    *this << " Co: " << course;
    *this << endl;
}

/* Comment Event */
/* <Time> Comment: <type> <comment text> */
void Writer::commentEvent(core::TimePoint & eventTime, std::string & type, std::string & commentText)
{
    *this << getTimeStamp(eventTime);
    *this << " Comment:";
    *this << ' ' << type;
    *this << ' ' << commentText;
    *this << endl;
}

/* Ethernet Packet */
/* <Time> ETH <Channel> <Dir> <DataLen>:<Data> */
void Writer::ethernetPacket(core::TimePoint & eventTime, std::string & channel, bool dirTx, unsigned int dataLen, std::vector<unsigned short> & data)
{
    *this << getTimeStamp(eventTime);
    *this << ' ' << channel;
    *this << ' ' << (dirTx ? "Tx" : "Rx");
    *this << ' ' << std::hex << dataLen << std::dec;
    *this << ':' << std::hex << std::setfill('0') << std::setw(2);
    for(std::vector<unsigned short>::iterator it=data.begin(); it!=data.end(); ++it) {
        *this << *it;
    }
    *this << std::dec << std::setw(0);
    *this << endl;
}

// FlexRay Message Event (Old Format)
// FlexRay Start Cycle Event (Old Format)
// FlexRay Message Event ("RMSG/PDU")
// FlexRay Start Cycle Event ("SCE")
// FlexRay Status Event ("SE")
// FlexRay Error Event ("EE")

// K-Line Byte event
// K-Line Message event

// LIN Message

// LIN Transmission Event
// LIN Receive Error
// LIN Sync Error
// LIN Checksum Error
// LIN Spike Error
// LIN Dominant Signal

// LIN Baudrate
// LIN DLC Info
// LIN Checksum Info
// LIN Scheduler Mode Change
// LIN Slave Timeout
// LIN Event Triggered Frame Info
// LIN Statistic Info
// LIN Short or slow response
// LIN Disturbance event

// LIN Sleep Mode
// LIN Wakeup Frame
// LIN Unexpected wakeup

// MOST25 Control Message Node Mode
// MOST25 Control Message Spy Mode
// MOST25 Packet
// MOST Light Lock Event
// MOST Special Register Event
// MOST Common Register Event
// MOST HW Mode Event
// MOST NetState Event
// MOST Data Lost Event
// MOST Trigger Event
// MOST Statistic Event
// MOST Statistic Extended Event (CodingErrors and FrameCounter)
// MOST TxLight
// MOST Stress Event
// MOST25 Alloc Table
// MOST150 Control Message
// MOST50/150 Control Message Fragment
// MOST150 Packet
// MOST50/150 Packet Fragment
// MOST Ethernet Packet
// MOST Ethernet Packet Fragment
// MOST System Event
// MOST50/150 Allocation Table
// MOST50 Control Message
// MOST50 Packet
// MOST ECL

// ISO-TP Prefix
// ISO-TP Single Frame
// ISO-TP First Frame
// ISO-TP Consecutive Frame
// ISO-TP Flow Control Frame
// ISO-TP Event format

}
}
