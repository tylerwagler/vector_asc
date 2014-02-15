#include "Reader.h"

#include <clocale>
#include <exception>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

namespace Vector {
namespace ASC {

static void chomp(std::string & line)
{
    for(;;) {
        char back = line.back();
        if ((back == '\r') || (back == '\n')) {
            line.pop_back();
        } else {
            return;
        }
    }
}

Reader::Reader() :
    std::ifstream(),
    fileHeader(),
    triggerTime(),
    lastEventTime(),
    drivers(),
    line(),
    elements()
{
    std::setlocale(LC_NUMERIC, "C");
    std::setlocale(LC_TIME, "de_DE");
}

Reader::~Reader()
{
}

core::Event * Reader::readEvent()
{
    core::Event * event;

    /* read line */
    std::getline(*this, line);
    chomp(line);
    if (line.empty()) {
        return nullptr;
    }

    /* decode line */
    elements.clear();
    std::istringstream iss(line);
    while(iss.good()) {
        std::string element;
        iss >> element;
        elements.push_back(element);
    }
    if (elements.empty()) {
        return nullptr;
    }

    if (readFileHeader()) {
        return nullptr;
    }

    /* CAN Events */
    event = canMessageEvent();
    if (event) {
        return event;
    }
    event = canRemoteFrameEvent();
    if (event) {
        return event;
    }
    event = canErrorFrame();
    if (event) {
        return event;
    }
    event = canBusStatisticsEvent();
    if (event) {
        return event;
    }
#if 0
    if (canErrorEvent()) {
        return nullptr;
    }
    if (canOverloadFrameEvent) {
        return nullptr;
    }

    /* Log and Trigger Events */
    if (logTriggerEvent) {
        return nullptr;
    }
    if (logDirectStartEvent) {
        return nullptr;
    }
    if (logDirectStopEvent) {
        return nullptr;
    }
    if (beginTriggerblockEvent) {
        return nullptr;
    }
    if (endTriggerblockEvent) {
        return nullptr;
    }
#endif

    std::cerr << "Unknown element in ASC log file: " << line << std::endl;
    return nullptr;
}

bool Reader::readFileHeader()
{
    if (elements[0] == "date") {
        Symbol::WeekDay weekDay = calcWeekDay(elements[1]);
        Symbol::Month month = calcMonth(elements[2]);
        Symbol::Date date = stoul(elements[3]);
        Symbol::FullTime fullTime;
        std::istringstream iss(elements[4]);
        std::string s;
        std::getline(iss, s, ':');
        fullTime.h = stoul(s);
        std::getline(iss, s, ':');
        fullTime.m = stoul(s);
        std::getline(iss, s, ':');
        fullTime.s = stoul(s);
        bool hasAmPm = false;
        if (elements[5] == "am") {
            hasAmPm = true;
        } else
        if (elements[5] == "pm") {
            hasAmPm = true;
            fullTime.h += 12;
        };
        Symbol::Year year;
        if (hasAmPm) {
            year = stoul(elements[6]);
        } else {
            year = stoul(elements[5]);
        }

        fileHeader.date = getTimePoint(weekDay, month, date, fullTime, year);
        triggerTime = fileHeader.date;
        lastEventTime = fileHeader.date;
        return true;
    } else

    if (elements[0] == "base") {
        if (elements[1] == "hex") {
            fileHeader.numberBase = NumberBase::Hex;
        } else
        if (elements[1] == "dec") {
            fileHeader.numberBase = NumberBase::Dec;
        } else {
            return false;
        }

        if (elements[2] != "timestamps") {
            return false;
        }
        if (elements[3] == "absolute") {
            fileHeader.timeStampMode = TimeStampMode::Absolute;
        } else
        if (elements[3] == "relative") {
            fileHeader.timeStampMode = TimeStampMode::Relative;
        } else {
            return false;
        }

        return true;
    } else

    if (line == "internal events logged") {
        fileHeader.internalEventsLogged = true;
        return true;
    } else

    if (line == "no internal events logged") {
        fileHeader.internalEventsLogged = false;
        return true;
    } else

    if (elements[0] == "//") {
        if (elements[1] == "version") {
            std::istringstream iss(elements[2]);
            std::string s;
            std::getline(iss, s, '.');
            iss >> s;
            unsigned int major;
            try {
                major = stoul(s);
            } catch (std::exception & e) {
                return false;
            }

            iss >> s;
            unsigned int minor;
            try {
                minor = stoul(s);
            } catch (std::exception & e) {
                return false;
            }

            iss >> s;
            unsigned int patch;
            try {
                patch = stoul(s);
            } catch (std::exception & e) {
                return false;
            }
            fileHeader.version = (Vector::Version) ((major << 16) | (minor << 8) | (patch));
            return true;
        } else

        if ((elements[2] != "previous") || (elements[3] != "log") || (elements[3] != "file:")) {
            std::string & time = elements[1];
            std::string fileName = line.substr(line.find("previous log file: ") + 19);

            /** @todo do something with it */
            return true;
        }

        return false;
    }

    return false;
}

Symbol::WeekDay Reader::calcWeekDay(std::string & str)
{
    if ((str == "Sun") || (str == "Son")) {
        return Symbol::WeekDay::Sun;
    } else
    if ((str == "Mon") || (str == "Mon")) {
        return Symbol::WeekDay::Mon;
    } else
    if ((str == "Tue") || (str == "Die")) {
        return Symbol::WeekDay::Tue;
    } else
    if ((str == "Wed") || (str == "Mit")) {
        return Symbol::WeekDay::Wed;
    } else
    if ((str == "Thu") || (str == "Don")) {
        return Symbol::WeekDay::Thu;
    } else
    if ((str == "Fri") || (str == "Fre")) {
        return Symbol::WeekDay::Fri;
    } else
    if ((str == "Sat") || (str == "Sam")) {
        return Symbol::WeekDay::Sat;
    } else {
        std::cerr << str << std::endl;
        return Symbol::WeekDay::Unknown;
    }
}

Symbol::Month Reader::calcMonth(std::string & str)
{
    if ((str == "Jan") || (str == "Jan")) {
        return Symbol::Month::Jan;
    } else
    if ((str == "Feb") || (str == "Feb")) {
        return Symbol::Month::Feb;
    } else
    if ((str == "Mar") || (str == "Mär")) {
        return Symbol::Month::Mar;
    } else
    if ((str == "Apr") || (str == "Apr")) {
        return Symbol::Month::Apr;
    } else
    if ((str == "May") || (str == "Mai")) {
        return Symbol::Month::May;
    } else
    if ((str == "Jun") || (str == "Jun")) {
        return Symbol::Month::Jun;
    } else
    if ((str == "Jul") || (str == "Jul")) {
        return Symbol::Month::Jul;
    } else
    if ((str == "Aug") || (str == "Aug")) {
        return Symbol::Month::Aug;
    } else
    if ((str == "Sep") || (str == "Sep")) {
        return Symbol::Month::Sep;
    } else
    if ((str == "Oct") || (str == "Okt")) {
        return Symbol::Month::Oct;
    } else
    if ((str == "Nov") || (str == "Nov")) {
        return Symbol::Month::Nov;
    } else
    if ((str == "Dec") || (str == "Dez")) {
        return Symbol::Month::Dec;
    } else {
        std::cerr << str << std::endl;
        return Symbol::Month::Unknown;
    }
}

core::TimePoint Reader::getTimePoint(Symbol::WeekDay & weekDay, Symbol::Month & month, Symbol::Date & date, Symbol::FullTime & fullTime, Symbol::Year & year)
{
    struct tm tm;
    tm.tm_wday = (int) weekDay;
    tm.tm_mon  = (int) month;
    tm.tm_mday = date;
    tm.tm_hour = fullTime.h;
    tm.tm_min  = fullTime.m;
    tm.tm_sec  = fullTime.s;
    tm.tm_year = year - 1900;

    std::time_t t = mktime(&tm);
    core::TimePoint tp;
    tp = std::chrono::system_clock::from_time_t(t);
    return tp;
}

core::TimePoint Reader::getTimePoint(double & timeStamp)
{
    core::TimePoint tp;
    switch(fileHeader.timeStampMode) {
    case TimeStampMode::Absolute:
        tp = triggerTime;
        break;
    case TimeStampMode::Relative:
        tp = lastEventTime;
        break;
    }

    core::Duration d(timeStamp);
    tp += d;

    lastEventTime = tp;

    return tp;
}

/* CAN Message Event */
/* <Time> <Channel> <ID> <Dir> d <DLC> <D0> <D1>...<D8> <MessageFlags> */
/* <Time> <Channel> <ID> <Dir> d <DLC> <D0> <D1>...<D8> Length = <MessageDuration> BitCount = <MessageLength> <MessageFlags> */
ISO::ISO11898::Message * Reader::canMessageEvent()
{
    CanMessageEvent ev;

    try {
        /* <Time> */
        ev.time = stod(elements[0]);

        /* <Channel> */
        ev.channel = elements[1];

        /* <ID> */
        if (elements[2].back() == 'x') {
            ev.id.extended = true;
            elements[2].pop_back();
        } else {
            ev.id.extended = false;
        }
        ev.id.id = stoul(elements[2], nullptr, 16);

        /* <Dir> */
        if (elements[3] == "Rx") {
            ev.dir = Symbol::Dir::Rx;
        } else
        if (elements[3] == "Tx") {
            ev.dir = Symbol::Dir::Tx;
        } else
        if (elements[3] == "TxRq") {
            ev.dir = Symbol::Dir::TxRq;
        } else {
            return nullptr;
        }

        /* d */
        if (elements[4] != "d") {
            return nullptr;
        }

        /* <DLC> */
        ev.dlc = stoul(elements[5], nullptr, 16);
        unsigned int dlc8;
        dlc8 = ev.dlc;
        if (dlc8 > 8) {
            dlc8 = 8;
        }

        /* <D0> <D1>...<D8> */
        ev.data.resize(dlc8);
        for (unsigned int i = 0; i < dlc8; i++) {
            ev.data[i] = stoul(elements[6+i], nullptr, 16);
        }

        if (elements.size() == (6 + dlc8)) {
            // do nothing
        } else
        if (elements.size() == (6 + dlc8 + 1)) {
            /* <MessageFlags> */
            if (elements[6+dlc8] == "TE") {
                ev.messageFlags = Symbol::MessageFlags::TE;
            } else
            if (elements[6+dlc8] == "WU") {
                ev.messageFlags = Symbol::MessageFlags::WU;
            } else
            if (elements[6+dlc8] == "XX") {
                ev.messageFlags = Symbol::MessageFlags::XX;
            }
        } else
        if (elements.size() > (6 + dlc8 + 1)) {
            /* Length = <MessageDuration> */
            if ((elements[6+dlc8] != "Length") || (elements[6+dlc8+1] != "=")) {
                return nullptr;
            }
            ev.messageDuration = stoul(elements[6+dlc8+2]);

            /* BitCount = <MessageLength> */
            if ((elements[6+dlc8+3] != "BitCount") || (elements[6+dlc8+4] != "=")) {
                return nullptr;
            }
            ev.messageLength = stoul(elements[6+dlc8+5]);

            /* <MessageFlags> */
            if (elements[6+dlc8+6] == "TE") {
                ev.messageFlags = Symbol::MessageFlags::TE;
            } else
            if (elements[6+dlc8+6] == "WU") {
                ev.messageFlags = Symbol::MessageFlags::WU;
            } else
            if (elements[6+dlc8+6] == "XX") {
                ev.messageFlags = Symbol::MessageFlags::XX;
            }
        }
    } catch (std::exception & e) {
        return nullptr;
    }

    /* create message */
    ISO::ISO11898::Message * m = new ISO::ISO11898::Message();
    m->time = getTimePoint(ev.time);
    m->source = getDriver(ev.channel);
    if (ev.id.extended) {
        m->type = ISO::ISO11898::Message::Type::DataExtended;
    } else {
        m->type = ISO::ISO11898::Message::Type::DataStandard;
    }
    m->identifier = ev.id.id;
    m->dataLengthCode = ev.dlc;
    m->data = ev.data;
    return m;
}

/* CAN Remote Frame Event */
/* <Time> <Channel> <ID> <Dir> r */
ISO::ISO11898::Message * Reader::canRemoteFrameEvent()
{
    CanRemoteFrameEvent ev;

    try {
        /* <Time> */
        ev.time = stod(elements[0]);

        /* <Channel> */
        ev.channel = elements[1];

        /* <ID> */
        if (elements[1].back() == 'x') {
            ev.id.extended = true;
            elements[1].pop_back();
        } else {
            ev.id.extended = false;
        }
        ev.id.id = stoul(elements[1], nullptr, 16);

        /* <Dir> */
        if (elements[2] == "Rx") {
            ev.dir = Symbol::Dir::Rx;
        } else
        if (elements[2] == "Tx") {
            ev.dir = Symbol::Dir::Tx;
        } else
        if (elements[2] == "TxRq") {
            ev.dir = Symbol::Dir::TxRq;
        } else {
            return nullptr;
        }

        /* r */
        if (elements[3] != "r") {
            return nullptr;
        }
    } catch (std::exception & e) {
        return nullptr;
    }

    /* create message */
    ISO::ISO11898::Message * m = new ISO::ISO11898::Message();
    m->time = getTimePoint(ev.time);
    m->source = getDriver(ev.channel);
    if (ev.id.extended) {
        m->type = ISO::ISO11898::Message::Type::RemoteExtended;
    } else {
        m->type = ISO::ISO11898::Message::Type::RemoteStandard;
    }
    m->identifier = ev.id.id;
    return m;
}

/* CAN Error Frame */
/* <Time> <Channel> ErrorFrame */
/* <Time> <Channel> ErrorFrame ECC:<ECC> */
/* <Time> <Channel> ErrorFrame Flags = <flags> CodeExt = <codeExt> Code = <code> ID = <ID> DLC = <DLC> Position = <Position> Length = <Length> */
ISO::ISO11898::Message * Reader::canErrorFrame()
{
    CanErrorFrame ev;

    try {
        /* <Time> */
        ev.time = stod(elements[0]);

        /* <Channel> */
        ev.channel = elements[1];

        /* ErrorFrame */
        if (elements[2] != "ErrorFrame") {
            return nullptr;
        }

        if (elements.size() == 4) {
            /* ECC:<ECC> */
            if (elements[3].find("ECC:") == 0) {
                elements[3].erase(0, 4);
                ev.ecc = stoul(elements[3], nullptr, 2);

                /* this was an error from a sja1000 can controller. */
                ev.sja1000 = true;
            }
        } else
        if (elements.size() > 4) {
            /* Flags = <flags> */
            if ((elements[3] != "Flags") || (elements[4] != "=")) {
                return nullptr;
            }
            if (elements[5].find("0x") != 0) {
                return nullptr;
            }
            elements[5].erase(0, 2);
            ev.flags = stoul(elements[5], nullptr, 16);

            /* CodeExt = <codeExt> */
            if ((elements[6] != "CodeExt") || (elements[7] != "=")) {
                return nullptr;
            }
            if (elements[8].find("0x") != 0) {
                return nullptr;
            }
            elements[8].erase(0, 2);
            ev.codeExt = stoul(elements[8], nullptr, 16);

            /* Code = <code> */
            if ((elements[9] != "Code") || (elements[10] != "=")) {
                return nullptr;
            }
            if (elements[11].find("0x") != 0) {
                return nullptr;
            }
            elements[11].erase(0, 2);
            ev.code = stoul(elements[11], nullptr, 16);

            /* ID = <ID> */
            if ((elements[12] != "ID") || (elements[13] != "=")) {
                return nullptr;
            }
            if (elements[14].back() == 'x') {
                ev.id.extended = true;
                elements[14].pop_back();
            } else {
                ev.id.extended = false;
            }
            ev.id.id = stoul(elements[14], nullptr, 16);

            /* DLC = <DLC> */
            if ((elements[15] != "DLC") || (elements[16] != "=")) {
                return nullptr;
            }
            ev.dlc = stoul(elements[17], nullptr, 16);

            /* Position = <Position> */
            if ((elements[18] != "Position") || (elements[19] != "=")) {
                return nullptr;
            }
            ev.position = stoul(elements[20]);

            /* Length = <Length> */
            if ((elements[21] != "Length") || (elements[22] != "=")) {
                return nullptr;
            }
            ev.length = stoul(elements[23]);

            /* this was an error from a can core controller. */
            ev.canCore = true;
        }
    } catch (std::exception & e) {
        return nullptr;
    }

    /* create message */
    ISO::ISO11898::Message * m = new ISO::ISO11898::Message();
    m->time = getTimePoint(ev.time);
    m->source = getDriver(ev.channel);
    m->type = ISO::ISO11898::Message::Type::Error;
    return m;
}

/* CAN Bus Statistics Event */
/* <Time> <Channel> Statistic: D <StatNumber> R <StatNumber> XD <StatNumber> XR <StatNumber> E <StatNumber> O <StatNumber> B <StatPercent>% */
ISO::ISO11898::Statistics * Reader::canBusStatisticsEvent()
{
    CanBusStatisticsEvent ev;

    try {
        /* <Time> */
        ev.time = stod(elements[0]);

        /* <Channel> */
        ev.channel = elements[1];

        /* Statitic: */
        if (elements[2] != "Statistic:") {
            return nullptr;
        }

        /* D <StatNumber> */
        if (elements[3] != "D") {
            return nullptr;
        }
        ev.d = stoul(elements[4]);

        /* R <StatNumber> */
        if (elements[5] != "R") {
            return nullptr;
        }
        ev.r = stoul(elements[6]);

        /* XD <StatNumber> */
        if (elements[7] != "XD") {
            return nullptr;
        }
        ev.xd = stoul(elements[8]);

        /* XR <StatNumber> */
        if (elements[9] != "XR") {
            return nullptr;
        }
        ev.xr = stoul(elements[10]);

        /* E <StatNumber> */
        if (elements[11] != "E") {
            return nullptr;
        }
        ev.e = stoul(elements[12]);

        /* O <StatNumber> */
        if (elements[13] != "O") {
            return nullptr;
        }
        ev.o = stoul(elements[14]);

        /* B <StatPercent>% */
        if (elements[15] != "B") {
            return nullptr;
        }
        ev.b = stoul(elements[16]);
    } catch (std::exception & e) {
        return nullptr;
    }

    /* create statistics */
    ISO::ISO11898::Statistics * s = new ISO::ISO11898::Statistics();
    s->time = getTimePoint(ev.time);
    s->source = getDriver(ev.channel);
    s->standardDataFrameCount = ev.d;
    s->standardRemoteFrameCount = ev.r;
    s->extendedDataFrameCount = ev.xd;
    s->extendedRemoteFrameCount = ev.xr;
    s->errorFrameCount = ev.e;
    s->overloadFrameCount = ev.o;
    s->busload = ev.b;
    return s;
}

/* CAN Error Event */
/* <Time> CAN <Channel> Status:<Error> */
bool Reader::canErrorEvent()
{
    CanErrorEvent ev;

    try {
        /* <Time> */
        ev.time = stod(elements[0]);

        /* CAN */
        if (elements[1] != "CAN") {
            return false;
        }

        /* <Channel> */
        ev.channel = elements[2];

        /* Status:<Error> */
        if (elements[3].find("Status:") == 0) {
            return false;
        }
        ev.error = elements[3].substr(7);
    } catch (std::exception & e) {
        return false;
    }

    /** @todo do something with it */
    return true;
}

/* CAN Overload Frame Event */
/* <Time> <Channel> OverloadFrame */
bool Reader::canOverloadFrameEvent()
{
    CanOverloadFrameEvent ev;

    try {
        /* <Time> */
        ev.time = stod(elements[0]);

        /* <Channel> */
        ev.channel = elements[1];

        /* OverloadFrame */
        if (elements[2] != "OverloadFrame") {
            return false;
        }
    } catch (std::exception & e) {
        return false;
    }

    /** @todo do something with it */
    return true;
}

/* Log Trigger Event */
/* <Time> log trigger event */
bool Reader::logTriggerEvent()
{
    LogTriggerEvent ev;

    try {
        /* <Time> */
        ev.time = stod(elements[0]);

        /* log trigger event */
        if ((elements[1] != "log") || (elements[2] != "trigger") || (elements[3] != "event")) {
            return false;
        }
    } catch (std::exception & e) {
        return false;
    }

    /** @todo do something with it */
    return true;
}

/* Log Direct Start Event */
/* <Time> log direct start (<PreTrigger>ms) */
bool Reader::logDirectStartEvent()
{
    LogDirectStartEvent ev;

    try {
        /* <Time> */
        ev.time = stod(elements[0]);

        /* log trigger event */
        if ((elements[1] != "log") || (elements[2] != "direct") || (elements[3] != "start")) {
            return false;
        }

        /* (<PreTrigger>ms) */
        if ((elements[4].front() != '(') || (elements[4].rfind("ms") != elements[4].size()-2)) {
            return false;
        }
        elements[4].erase(0, 1);
        elements[4].erase(elements[4].size()-3);
        ev.preTrigger = stoul(elements[4]);
    } catch (std::exception & e) {
        return false;
    }

    /** @todo do something with it */
    return true;
}

/* Log Direct Stop Event */
/* <Time> log direct stop (<PostTrigger>ms) */
bool Reader::logDirectStopEvent()
{
    LogDirectStopEvent ev;

    try {
        /* <Time> */
        ev.time = stod(elements[0]);

        /* log trigger event */
        if ((elements[1] != "log") || (elements[2] != "direct") || (elements[3] != "stop")) {
            return false;
        }

        /* (<PreTrigger>ms) */
        if ((elements[4].front() != '(') || (elements[4].rfind("ms)") == elements[4].size()-3)) {
            return false;
        }
        elements[4].erase(0, 1);
        elements[4].erase(elements[4].size()-3);
        ev.postTrigger = stoul(elements[4]);
    } catch (std::exception & e) {
        return nullptr;
    }

    /** @todo do something with it */
    return true;
}

/* Begin Triggerblock Event */
/* Begin Triggerblock <WeekDay> <Month> <Date> <FullTime> <Year> */
bool Reader::beginTriggerblockEvent()
{
    BeginTriggerblockEvent ev;

    /* probe */
    if (line.find("Begin Triggerblock") != 0) {
        return false;
    }

    ev.weekDay = calcWeekDay(elements[2]);
    ev.month = calcMonth(elements[3]);
    ev.date = stoul(elements[4]);
    std::istringstream iss(elements[5]);
    std::string s;
    std::getline(iss, s, ':');
    ev.fullTime.h = stoul(s);
    std::getline(iss, s, ':');
    ev.fullTime.m = stoul(s);
    std::getline(iss, s, ':');
    ev.fullTime.s = stoul(s);
    bool hasAmPm = false;
    if (elements[6] == "am") {
        hasAmPm = true;
    } else
    if (elements[6] == "pm") {
        hasAmPm = true;
        ev.fullTime.h += 12;
    };
    if (hasAmPm) {
        ev.year = stoul(elements[7]);
    } else {
        ev.year = stoul(elements[6]);
    }

    triggerTime = getTimePoint(ev.weekDay, ev.month, ev.date, ev.fullTime, ev.year);
    lastEventTime = triggerTime;
    return true;
}

/* End Triggerblock Event */
/* End TriggerBlock */
bool Reader::endTriggerblockEvent(void)
{
    EndTriggerblockEvent ev;

    /* probe */
    if (line != "End TriggerBlock") {
        return false;
    }

    /** @todo do something with it */
    return true;
}

std::shared_ptr<core::Driver> Reader::getDriver(Symbol::Channel & channel)
{
    auto it = drivers.find(channel);

    /* new driver */
    if (it == drivers.end()) {
        core::Driver * driver = new core::Driver();
        driver->channelName = channel;
        drivers[channel] = std::shared_ptr<core::Driver>(driver);
    }

    return it->second;
}

}
}
