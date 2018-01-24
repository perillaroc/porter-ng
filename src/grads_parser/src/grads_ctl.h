#pragma once

#include <string>
#include <vector>

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

    enum class LevelType
    {
        Single,
        Multi,
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
    };

    class GradsCtl
    {
    public:
        std::string data_file_path_;
        std::string title_;
        double undefined_value_ = 9999;
        GradsDataEndian data_endian_ = GradsDataEndian::Unknown;

        Dimension x_def_;
        Dimension y_def_;
        Dimension z_def_;

        std::vector<Variable> vars_;
    };
}

