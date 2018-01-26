#pragma once

#include <string>
#include <vector>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "porter_config.h"

namespace GradsParser
{
    enum class DataEndian
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

    struct Dimension
    {
        DimensionType type_ = DimensionType::Unknown;
        size_t count_ = 0;
        double step_ =0;
        std::vector<double> values_;
    };

    struct TimeDimension
    {
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

    struct Variable
    {
        std::string name_;
        LevelType level_type_ = LevelType::Multi;
        double level_ = -1;
        size_t level_index_ = 0;
        std::string units_;
        std::string description_;
        boost::posix_time::ptime time_;
    };

    struct GradsCtl
    {
        std::string ctl_file_path_;
        std::string data_file_path_;
        std::string title_;
        double undefined_value_ = 9999;

#if defined(PORTER_BIG_ENDIAN)
        DataEndian data_endian_ = DataEndian::BigEndian;
        DataEndian local_endian_ = DataEndian::BigEndian;
#elif defined(PORTER_LITTLE_ENDIAN)
        DataEndian data_endian_ = DataEndian::LittleEndian;
        DataEndian local_endian_ = DataEndian::LittleEndian;
#else
        DataEndian data_endian_ = DataEndian::Unknown;
        DataEndian local_endian_ = DataEndian::Unknown;
#endif

        Dimension x_def_;
        Dimension y_def_;
        Dimension z_def_;
        TimeDimension t_def_;


        std::vector<VariableDefinition> var_defs_;
        std::vector<Variable> vars_;

        // special vars
        boost::posix_time::ptime start_time_;
        boost::posix_time::time_duration forecast_time_;

    };
}

