#pragma once

#include <string>
#include <vector>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "porter_config.h"

namespace GradsParser
{
    enum class GradsDataEndian
    {
        Unknown,
        BigEndian,
        LittleEndian,
    };

    enum class DimensionType
    {
        Unknown,
        Linear,
        Level
    };

    class Dimension
    {
    public:
        DimensionType type_ = DimensionType::Unknown;
        size_t count_ = 0;
        std::vector<double> values_;
    };

    class TimeDimension
    {
    public:
        DimensionType type_ = DimensionType::Unknown;
        size_t count_ = 0;
        std::vector<boost::posix_time::ptime> values_;
    };

    enum class LevelType
    {
        Single,
        Multi,
    };

    class VariableDefinition
    {
    public:
        std::string name_;
        int levels_;
        std::string units_;
        std::string description_;
    };

    class Variable
    {
    public:
        std::string name_;
        LevelType level_type_ = LevelType::Multi;
        double level_ = -1;
        size_t level_index_ = 0;
        std::string units_;
        std::string description_;
        boost::posix_time::ptime time_;
    };

    class GradsCtl
    {
    public:
        std::string data_file_path_;
        std::string title_;
        double undefined_value_ = 9999;

#if defined(PORTER_BIG_ENDIAN)
        GradsDataEndian data_endian_ = GradsDataEndian::BigEndian;
        GradsDataEndian local_endian_ = GradsDataEndian::BigEndian;
#elif defined(PORTER_LITTLE_ENDIAN)
        GradsDataEndian data_endian_ = GradsDataEndian::LittleEndian;
        GradsDataEndian local_endian_ = GradsDataEndian::LittleEndian;
#else
        GradsDataEndian data_endian_ = GradsDataEndian::Unknown;
        GradsDataEndian local_endian_ = GradsDataEndian::Unknown;
#endif

        Dimension x_def_;
        Dimension y_def_;
        Dimension z_def_;
        TimeDimension t_def_;

        std::vector<Variable> vars_;

        std::vector<VariableDefinition> var_defs_;
    };
}

