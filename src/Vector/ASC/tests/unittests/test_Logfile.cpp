#define BOOST_TEST_MODULE Logfile
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

#if 1
BOOST_AUTO_TEST_CASE(LogFile)
{
    Vector::ASC::File filein, fileout;

    /* open input file */
    boost::filesystem::path infile(CMAKE_CURRENT_SOURCE_DIR "/data/logfile.asc");
    filein.openMode = Vector::ASC::File::OpenMode::Read;
    filein.open(infile.string());
    BOOST_REQUIRE(filein.is_open());

    /* open output file */
    boost::filesystem::path outdir(CMAKE_CURRENT_BINARY_DIR "/data/");
    if (!exists(outdir)) {
        BOOST_REQUIRE(create_directory(outdir));
    }
    boost::filesystem::path outfile(CMAKE_CURRENT_BINARY_DIR "/data/logfile.asc");
    fileout.openMode = Vector::ASC::File::OpenMode::Write;
    fileout.open(outfile.string());
    BOOST_REQUIRE(fileout.is_open());

    /* parse log file */
    while(!filein.eof()) {
        Vector::ASC::Event * event;
        event = filein.read();
        BOOST_CHECK(event != nullptr);
        if (event != nullptr) {
            /* these values must be copied to File */
            switch(event->eventType) {
            case Vector::ASC::Event::EventType::FileBaseTimestamps:
                {
                    Vector::ASC::FileBaseTimestamps * fileBaseTimestamps = static_cast<Vector::ASC::FileBaseTimestamps *>(event);
                    fileout.base = (fileBaseTimestamps->base == Vector::ASC::FileBaseTimestamps::Base::Hex) ? 16 : 10;
                }
                break;
            case Vector::ASC::Event::EventType::FileVersion:
                {
                    Vector::ASC::FileVersion * fileVersion = static_cast<Vector::ASC::FileVersion *>(event);
                    fileout.version = (fileVersion->versionMajor << 16) | (fileVersion->versionMinor << 8) | (fileVersion->versionPatch);
                }
                break;
            }

            fileout.write(event);
            delete event;
        }
    }

    /* close files */
    filein.close();
    fileout.close();

    /* compare files */
//    std::ifstream ifs1(infile.c_str());
//    std::ifstream ifs2(outfile.c_str());
//    std::istream_iterator<char> b1(ifs1), e1;
//    std::istream_iterator<char> b2(ifs2), e2;
//    BOOST_CHECK_EQUAL_COLLECTIONS(b1, e1, b2, e2);
}
#endif

#if 0
BOOST_AUTO_TEST_CASE(CAN_Log_Trigger_3_2)
{
    Vector::ASC::File file;

    /* open file */
    file.open(CMAKE_CURRENT_SOURCE_DIR "/data/CAN_Log_Trigger_3_2.asc");
    BOOST_REQUIRE(file.is_open());

    /* parse log file */
    while(!file.eof()) {
        Vector::ASC::Event * event;
        event = file.read();
        BOOST_CHECK(event != nullptr);
        delete event;
    }

    /* close file */
    file.close();
}

BOOST_AUTO_TEST_CASE(Ethernet_AFDX_3_2)
{
    Vector::ASC::File file;

    /* open file */
    file.open(CMAKE_CURRENT_SOURCE_DIR "/data/Ethernet_AFDX_3_2.asc");
    BOOST_REQUIRE(file.is_open());

    /* parse log file */
    while(!file.eof()) {
        Vector::ASC::Event * event;
        event = file.read();
        BOOST_CHECK(event != nullptr);
        delete event;
    }

    /* close file */
    file.close();
}

BOOST_AUTO_TEST_CASE(Ethernet_AFDX_4_2)
{
    Vector::ASC::File file;

    /* open file */
    file.open(CMAKE_CURRENT_SOURCE_DIR "/data/Ethernet_AFDX_4_2.asc");
    BOOST_REQUIRE(file.is_open());

    /* parse log file */
    while(!file.eof()) {
        Vector::ASC::Event * event;
        event = file.read();
        BOOST_CHECK(event != nullptr);
        delete event;
    }

    /* close file */
    file.close();
}

BOOST_AUTO_TEST_CASE(FlexRay_3_2)
{
    Vector::ASC::File file;

    /* open file */
    file.open(CMAKE_CURRENT_SOURCE_DIR "/data/FlexRay_3_2.asc");
    BOOST_REQUIRE(file.is_open());

    /* parse log file */
    while(!file.eof()) {
        Vector::ASC::Event * event;
        event = file.read();
        BOOST_CHECK(event != nullptr);
        delete event;
    }

    /* close file */
    file.close();
}

BOOST_AUTO_TEST_CASE(FlexRay_4_9)
{
    Vector::ASC::File file;

    /* open file */
    file.open(CMAKE_CURRENT_SOURCE_DIR "/data/FlexRay_4_9.asc");
    BOOST_REQUIRE(file.is_open());

    /* parse log file */
    while(!file.eof()) {
        Vector::ASC::Event * event;
        event = file.read();
        BOOST_CHECK(event != nullptr);
        delete event;
    }

    /* close file */
    file.close();
}

BOOST_AUTO_TEST_CASE(KLine_3_2)
{
    Vector::ASC::File file;

    /* open file */
    file.open(CMAKE_CURRENT_SOURCE_DIR "/data/KLine_3_2.asc");
    BOOST_REQUIRE(file.is_open());

    /* parse log file */
    while(!file.eof()) {
        Vector::ASC::Event * event;
        event = file.read();
        BOOST_CHECK(event != nullptr);
        delete event;
    }

    /* close file */
    file.close();
}

// LIN has no whole file example

BOOST_AUTO_TEST_CASE(Most_3_2)
{
    Vector::ASC::File file;

    /* open file */
    file.open(CMAKE_CURRENT_SOURCE_DIR "/data/Most_3_2.asc");
    BOOST_REQUIRE(file.is_open());

    /* parse log file */
    while(!file.eof()) {
        Vector::ASC::Event * event;
        event = file.read();
        BOOST_CHECK(event != nullptr);
        delete event;
    }

    /* close file */
    file.close();
}

BOOST_AUTO_TEST_CASE(TpDiag_3_2)
{
    Vector::ASC::File file;

    /* open file */
    file.open(CMAKE_CURRENT_SOURCE_DIR "/data/TpDiag_3_2.asc");
    BOOST_REQUIRE(file.is_open());

    /* parse log file */
    while(!file.eof()) {
        Vector::ASC::Event * event;
        event = file.read();
        BOOST_CHECK(event != nullptr);
        delete event;
    }

    /* close file */
    file.close();
}
#endif
