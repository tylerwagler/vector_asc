#define BOOST_TEST_MODULE AllLogfiles
#if !defined(WIN32)
#define BOOST_TEST_DYN_LINK
#endif
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>

#include <fstream>
#include <iterator>
#include <string>

#include <Vector/ASC.h>

BOOST_AUTO_TEST_CASE(AllLogfiles) {
    /* input directory */
    boost::filesystem::path indir(CMAKE_CURRENT_SOURCE_DIR "/data/");

    /* output directory */
    boost::filesystem::path outdir(CMAKE_CURRENT_BINARY_DIR "/data/");
    if (!exists(outdir))
        BOOST_REQUIRE(create_directory(outdir));

    for (boost::filesystem::directory_entry & x : boost::filesystem::directory_iterator(indir)) {
        std::string eventFile = x.path().filename().string();
        std::cout << eventFile << std::endl;

        /* open input file */
        Vector::ASC::File filein;
        boost::filesystem::path infile(CMAKE_CURRENT_SOURCE_DIR "/data/" + eventFile);
        filein.open(infile.string(), Vector::ASC::File::OpenMode::Read);
        BOOST_REQUIRE(filein.is_open());

        /* open output file */
        Vector::ASC::File fileout;
        boost::filesystem::path outfile(CMAKE_CURRENT_BINARY_DIR "/data/" + eventFile);
        fileout.open(outfile.string(), Vector::ASC::File::OpenMode::Write);
        BOOST_REQUIRE(fileout.is_open());

        /* parse log file */
        while (!filein.eof()) {
            Vector::ASC::Event * event;
            event = filein.read();
            BOOST_CHECK((event != nullptr) || filein.eof());
            if (event != nullptr) {
                /* these values must be copied to File */
                switch (event->eventType) {
                case Vector::ASC::Event::EventType::FileDate:
                    fileout.date = filein.date;
                    fileout.language = filein.language;
                    break;
                case Vector::ASC::Event::EventType::FileBaseTimestamps:
                    fileout.base = filein.base;
                    fileout.timestamps = filein.timestamps;
                    break;
                case Vector::ASC::Event::EventType::FileInternalEventsLogged:
                    fileout.internalEventsLogged = filein.internalEventsLogged;
                    break;
                case Vector::ASC::Event::EventType::FileVersion:
                    fileout.version = filein.version;
                    break;
                case Vector::ASC::Event::EventType::BeginTriggerblock:
                    fileout.language = filein.language;
                    break;
                case Vector::ASC::Event::EventType::StartOfMeasurement:
                    fileout.language = filein.language;
                    break;
                default:
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
        std::ifstream ifs1(infile.c_str());
        std::ifstream ifs2(outfile.c_str());
        std::istream_iterator<char> b1(ifs1), e1;
        std::istream_iterator<char> b2(ifs2), e2;
        BOOST_CHECK_EQUAL_COLLECTIONS(b1, e1, b2, e2);
    }
}
